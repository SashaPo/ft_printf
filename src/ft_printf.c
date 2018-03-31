/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:54:57 by opokusyn          #+#    #+#             */
/*   Updated: 2018/03/09 21:34:58 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdarg.h>

int	get_Z(t_pf *pf)
{
	int len1 = 0;
	char ch = 'Z';
	if (pf->flags.len)
		ch = 'Z';
	if (pf->flags.width > 1)
	{
		size_t dr = pf->flags.width - 1;
		if (pf->flags.minus)
			len1 += ft_putchar(ch);
		while (dr--)
			len1 += write(1, pf->flags.zero ? "0" : " ", 1);
	}
	if (pf->flags.minus)
		return (len1);
	else
		return(len1 + ft_putchar(ch));
}

int     free_deluxe(void **ad)
{
    free(*ad);
    return (0);
}

t_bool is_valid_type(char c)
{
	return (t_bool) (c == 'd' || c == 'i' || c == 'o' || c == 'x' || c == 'p' || c == 's'
                     || c == 'O' || c == 'u' || c == 'U' || c == 'D' || c == 'X' || c == 'c'
                     || c == '%' || c == 'S' || c == 'C' || c == 'Z' || c == 'f' || c == 'F' || c == 'b');
}

t_bool	is_length(char c)
{
	return (t_bool) (c == 'l' || c == 'h' || c == 'z' || c == 'j');
}

t_bool	is_flag(char c)
{
	return (t_bool) (c == '.' || c == '-'|| c == '+'|| c == '0'|| c == '#' || c == ' ');
}

size_t	specifier_len(const char *format)
{
	size_t len;

	len = 0;
	while (*format)
	{
		if (is_valid_type(*format))
			return (len);
		else if (!(is_flag(*format) || is_length(*format) || ft_isdigit(*format)))
			return (len);
			len++;
			format++;
	}
	return (len);
}

t_bool	has_conversion_type(const char *format)
{
	while (*format)
	{
		if (is_valid_type(*format))
			return (TRUE);
		else if (!(is_flag(*format) || is_length(*format) || ft_isdigit(*format)))
			return (TRUE);
		format++;
	}
	return (FALSE);
}

size_t	cut_specifier(const char *format, t_pf *pf)
{
	pf->speclen = specifier_len(format);
	pf->spec = (char *) format;
	pf->type = format[pf->speclen];
	if (!has_conversion_type(format))
		return (pf->speclen - 1);
	else
		return (pf->speclen);
}

void	parse_flags(t_pf *pf)
{
	size_t i = 0;
	while (i < pf->speclen)
	{
		if (pf->spec[i] == '-')
			pf->flags.minus = TRUE;
		if (pf->spec[i] == '#')
			pf->flags.hash = TRUE;
		if ((pf->spec[i] == '0'
			&& (i - 1 > 0  && !(pf->spec[i - 1] >= '0' && pf->spec[i - 1] <= '9'))) || (pf->spec[i] == '0' && pf->flags.hash))
			pf->flags.zero = TRUE;
		if (pf->spec[i] == '+')
			pf->flags.plus = TRUE;
		if (pf->spec[i] == ' ')
			pf->flags.space = TRUE;
		i++;
	}
}

void	parse_width(t_pf *pf)
{
	size_t i = 0;
    int width;

    width = 0;
	while (i < pf->speclen)
	{
        if (pf->spec[i] == '.')
            while (i + 1)
            {
                if (ft_isdigit(pf->spec[i + 1]))
                    i++;
                else
                {
                    i++;
                    break ;
                }

            }
        else if (pf->spec[i] >= '0' && pf->spec[i] <= '9' && width == 0)
            while (i < pf->speclen && ft_isdigit(pf->spec[i]))
			    width = width * 10 + (pf->spec[i++] - '0');
        else if (pf->spec[i] >= '0' && pf->spec[i] <= '9' && !pf->flags.zero && pf->spec[i - 1] != '.')
        {
            width = 0;
            while (i < pf->speclen && ft_isdigit(pf->spec[i]))
                width = width * 10 + (pf->spec[i++] - '0');
        }
        else
            i++;
	}
    pf->flags.width = width;
}

void	parse_length(t_pf *pf)
{
	size_t i = 0;
	while (i < pf->speclen)
	{	// lhh
		if ((pf->spec[i] == 'h' && pf->spec[i + 1] == 'h') || pf->spec[i] == 'l')
		{
			if (pf->spec[i] == 'l') //kostyl
				pf->flags.len = l;
			else
				pf->flags.len = hh;
			i++;
		}
		else if (pf->spec[i] == 'h' && h > pf->flags.len) // приоритет
			pf->flags.len = h;
        else if (pf->spec[i] == 'l' && pf->spec[i + 1] == 'l' && l > pf->flags.len)
            pf->flags.len = ll;
        else if (pf->spec[i] == 'l' && pf->flags.len == none && ll > pf->flags.len)
            pf->flags.len = l;
		else if (pf->spec[i] == 't' && t > pf->flags.len)
			pf->flags.len = t;
		else if (pf->spec[i] == 'j' && j > pf->flags.len)
			pf->flags.len = j;
		else if (pf->spec[i] == 'z' && z > pf->flags.len)
			pf->flags.len = z;
		i++;
	}
}

void	parse_prec(t_pf *pf)
{
	int	dot = -1;
	size_t i = 0;
	while (i < pf->speclen)
	{
		if (i > 0 && pf->spec[i - 1] == '.')
		{
			dot = 0;
			while (pf->spec[i] && pf->spec[i] >= '0' && pf->spec[i] <= '9')
				dot = dot * 10 + (pf->spec[i++] - '0');
		}
		i++;
		pf->flags.dot = TRUE;
	}
	pf->flags.dot = dot;
}

void	parse_implicit_dot(t_pf *pf)
{
	int idot = 0;
	size_t i = 0;
	while (i < pf->speclen)
	{
		if ((i > 0 || i == 0) && pf->spec[i] == '.' && !ft_isdigit(pf->spec[i + 1]))
			idot = 1;
		i++;
		pf->flags.implicit_dot = TRUE;
	}
	pf->flags.implicit_dot = idot;
}


long long fetch_signed_arg(t_pf *pf, va_list args)
{
	long long res = 0;

	if (pf->flags.len == none)
		res = va_arg(args, int);
	else if (pf->flags.len == h)
		res = (short)va_arg(args, int);
	else if (pf->flags.len == t)
		res = (ptrdiff_t)va_arg(args, ptrdiff_t);
	else if (pf->flags.len == l)
		res = va_arg(args, long);
	else if (pf->flags.len == j)
		res = (intmax_t)va_arg(args, intmax_t);
	else if (pf->flags.len == z)
		res = (long long)va_arg(args, size_t);
	else if (pf->flags.len == ll)
		res = va_arg(args, long long);
	else if (pf->flags.len == hh)
		res = (signed char) va_arg(args, int);
	return (res);
}

unsigned long long fetch_unsigned_arg(t_pf *pf, va_list args)
{
	unsigned long long unres = 0;

	if (pf->flags.len == h)
		unres = (unsigned short)va_arg(args, unsigned int);
	else if (pf->flags.len == t)
		unres = (unsigned long long int)va_arg(args, ptrdiff_t);
	else if (pf->flags.len == l)
		unres = va_arg(args, unsigned long);
	else if (pf->flags.len == j)
		unres = (uintmax_t)va_arg(args, uintmax_t);
	else if (pf->flags.len == z)
		unres = (size_t)va_arg(args, size_t);
	else if (pf->flags.len == ll)
		unres = va_arg(args, unsigned long long);
	else if (pf->flags.len == hh)
		unres = (unsigned char)va_arg(args, int);
	else
		unres = (unsigned long long)va_arg(args, unsigned int);
	return (unres);
}

int	get_fF(t_pf *pf, va_list args)
{
	int lenf = 0;
	int j = 0;
	signed long int decipart;
	signed long int intpart;
	char *expanded = 0;
	double f = va_arg(args, double);
	if (f < 0)
	{
		f *= -1;
		lenf += write(1, "-", 1);
	}
	intpart = (signed long int)f;
	lenf += write(1, ft_itoa_long(intpart), ft_strlen(ft_itoa_long(intpart)));
	lenf += write(1, ".", 1);
	f -= intpart;
	f *= 1000000;  //upto 6 decimal points
	decipart = (signed long int)(f + 0.5); //+0.5 to round of the value
//	ft_putnbr(decipart);
	f = intpart + decipart;
	expanded = ft_itoa_long_prec(decipart, pf->flags.dot);
	char *check_sign = ft_itoa(f);
	if ((check_sign[0] == '-' && !pf->flags.plus && pf->flags.dot != -1) || (check_sign[0] == '-' && pf->flags.plus && pf->flags.zero))
		lenf += write(1, "-", 1);
	if (pf->spec[j + 1] == '.' && pf->flags.width && f == 0) // fixed 176
	{
		int zero_arg = pf->flags.width;
		while (zero_arg--)
			lenf += write(1, " ", 1);
		return (lenf);
	}
	if (pf->flags.width && pf->flags.width > (lenf + ft_strlen(expanded)))
	{
		int difference = (int) (pf->flags.width - ft_strlen(expanded));
		if (pf->flags.minus)
		{
			if (pf->flags.plus)
				lenf += write(1, "+", 1);
			lenf += write(1, expanded, ft_strlen(expanded));
		}
		if (pf->flags.plus && check_sign[0] != '-')
			difference = difference - 1;
		if (pf->flags.plus && expanded[0] != '-' && pf->flags.dot == -1)
			lenf += write(1, "+", 1);
		if (pf->flags.dot != -1 && expanded[0] != '-')
			pf->flags.zero = 0;
		if (expanded[0] == '-' && !pf->flags.plus && pf->flags.zero)
			lenf += write(1, "-", 1);
		while (difference--)
			lenf += write(1, pf->flags.zero ? "0" : " ", 1);
	}
	if ((f == 0 && pf->flags.dot != -1) || (f == 0 && pf->flags.dot == -1)) //fixed 175
	{
		if (pf->spec[j] == '.')
			return (lenf + free_deluxe((void **)&expanded));
	}
	if (expanded[0] == '-' && !pf->flags.plus && pf->flags.zero && !pf->flags.width)
		lenf += write(1, "-", 1);
	if ((pf->flags.plus && expanded[0] != '-' && !pf->flags.width && !pf->flags.minus) || (pf->flags.plus && expanded[0] != '-' && pf->flags.dot != -1 && !pf->flags.minus))
		lenf += write(1, "+", 1);
	if (pf->flags.space && !pf->flags.plus && !pf->flags.width)
	{
		if (expanded[0] == '-')
			expanded[0] = '-';
		else
			lenf += write(1, " ", 1);
	}
	if (pf->flags.minus)
		return (lenf + free_deluxe((void **)&expanded) + free_deluxe((void **)&check_sign));
	if ((expanded[0] == '-' && !pf->flags.plus && pf->flags.zero) || (check_sign[0] == '-' && pf->flags.plus && pf->flags.zero && pf->flags.width))
	{
		return (int) (lenf + write(1, expanded + 1, ft_strlen(expanded + 1)) + free_deluxe((void **)&expanded) + free_deluxe((void **)&check_sign));
	}
	free(check_sign);
	free(expanded);
	return (int) (lenf + write(1, expanded, ft_strlen(expanded)));
}

int	get_dDi(t_pf *pf, va_list args)
{
	int len = 0;
    int j = 0;
    char *expanded = 0;
	long long d = 0;
    int difference = 0;
	if (pf->type == 'D')
		pf->flags.len ? (d = va_arg(args, int)) : (d = va_arg(args, long long)); //fixed ushort_max
	else if (pf->flags.len || pf->type == 'd' || pf->type == 'i')
		d = fetch_signed_arg(pf, args);
    expanded = ft_itoa_long_prec(d, pf->flags.dot);
	char *check_sign = ft_itoa(d);
	if (check_sign[0] == '-' && !pf->flags.plus && pf->flags.dot != -1 && (pf->flags.dot < (int) ft_strlen(check_sign)))
    {
        if (pf->flags.width)
        {
            if (pf->flags.width > ft_strlen(expanded))
                difference = (int) (pf->flags.width - ft_strlen(expanded));
            if (check_sign[0] == '-' && !pf->flags.plus && pf->flags.dot != -1)
            {
                len = 0;
                while (difference--)
                    len += write(1, pf->flags.zero ? "0" : " ", 1);
            }
        }
        return (int) (len + write(1, check_sign, ft_strlen(check_sign)));
    }
    if (pf->flags.width && pf->flags.width > (len + ft_strlen(expanded)))
    {
        difference = (int) (pf->flags.width - ft_strlen(expanded));
        if (check_sign[0] == '-' && !pf->flags.plus && pf->flags.dot != -1)
        {
            difference = difference - 1;
            len = 0;
            while (difference--)
                len += write(1, pf->flags.zero ? "0" : " ", 1);
            len += write(1, "-", 1);
            return (int) (len + write(1, expanded, ft_strlen(expanded)));
        }
    }
    if ((check_sign[0] == '-' && !pf->flags.plus && pf->flags.dot != -1) || (check_sign[0] == '-' && pf->flags.plus && pf->flags.zero))
            len += write(1, "-", 1);
    if (pf->spec[j + 1] == '.' && pf->flags.width && d == 0) // fixed 176
    {
        int zero_arg = pf->flags.width;
        while (zero_arg--)
            len += write(1, " ", 1);
        return (len);
    }
	if (pf->flags.width && pf->flags.width > (len + ft_strlen(expanded)))
	{
		difference = (int) (pf->flags.width - ft_strlen(expanded));
		if (pf->flags.minus)
        {
            if (pf->flags.plus && check_sign[0] != '-')
                len += write(1, "+", 1);
            len += write(1, expanded, ft_strlen(expanded));
        }
        if (pf->flags.plus && check_sign[0] != '-')
            difference = difference - 1;
		if (pf->flags.plus && expanded[0] != '-' && pf->flags.dot == -1 && len == 0 && pf->flags.zero)
			len += write(1, "+", 1);
		else if (pf->flags.plus && expanded[0] != '-' && pf->flags.dot == -1 && len == 0) //fix plus
		{
			if (pf->flags.width > ft_strlen(expanded))
			{
				while (pf->spec[j])
				{
					if (pf->spec[j] != '0')
						j++;
					else
					{
						pf->flags.zero = 1;
						break;
					}
				}
				if (pf->flags.zero)
					len += write(1, "+", 1);
				while (difference--)
					len += write(1, pf->flags.zero ? "0" : " ", 1);
			}
			if (!pf->flags.zero)
				len += write(1, "+", 1);
			len += write(1, expanded, ft_strlen(expanded));
			return (len);
		}
		if (pf->flags.dot != -1 && expanded[0] != '-')
			pf->flags.zero = 0;
        if (expanded[0] == '-' && !pf->flags.plus && pf->flags.zero)
            len += write(1, "-", 1);
		if (pf->flags.space && pf->flags.dot == -1)
		{
			while (pf->spec[j])
			{
				if (pf->spec[j] != '0')
					j++;
				else
				{
					pf->flags.zero = 1;
					break;
				}
			}
			len += write(1, " ", 1);
			difference = difference - 1;
		}
		if (pf->flags.minus)
			pf->flags.zero = 0;
		while (difference--)
            len += write(1, pf->flags.zero ? "0" : " ", 1);
	}
    if ((d == 0 && pf->flags.dot != -1) || (d == 0 && pf->flags.dot == -1)) //fixed 175
    {
        if (pf->spec[j] == '.')
            return (len + free_deluxe((void **)&expanded));
    }
    if (expanded[0] == '-' && !pf->flags.plus && pf->flags.zero && !pf->flags.width)
        len += write(1, "-", 1);
	if (expanded[0] != '-' && pf->flags.plus && !pf->flags.minus && !pf->flags.zero && pf->flags.dot == -1)
	{
		while (pf->spec[j])
		{
			if (pf->spec[j] != '0')
				j++;
			else
			{
				pf->flags.zero = 1;
				break;
			}
		}
		if (pf->flags.zero)
			len += write(1, "+", 1);
	}
	if ((pf->flags.plus && expanded[0] != '-' && !pf->flags.width && !pf->flags.minus) || (pf->flags.plus && expanded[0] != '-' && pf->flags.dot != -1 && !pf->flags.minus))
		len += write(1, "+", 1);
    if (pf->flags.space && !pf->flags.plus && !pf->flags.width)
    {
        if (expanded[0] == '-')
            expanded[0] = '-';
        else
            len += write(1, " ", 1);
    }
	if (pf->flags.minus)
	{
		if (pf->flags.width && pf->flags.width < ft_strlen(expanded))
			return (int) (len + write(1, expanded, ft_strlen(expanded)) + free_deluxe((void **)&expanded));
		return (len + free_deluxe((void **)&expanded) + free_deluxe((void **)&check_sign));
	}
    if ((expanded[0] == '-' && !pf->flags.plus && pf->flags.zero) || (check_sign[0] == '-' && pf->flags.plus && pf->flags.zero && pf->flags.width))
    {
            return (int) (len + write(1, expanded + 1, ft_strlen(expanded + 1)) + free_deluxe((void **)&expanded) + free_deluxe((void **)&check_sign));
    }
    free(check_sign);
    free(expanded);
    return (int) (len + write(1, expanded, ft_strlen(expanded)));
}

int	get_uU(t_pf *pf, va_list args)
{
	int ulen = 0;
	unsigned long u = 0;
    int i = 0;
	if (!pf->flags.len || pf->type == 'U')
	{
		if (pf->type == 'u')
			u = va_arg(args, unsigned int);
		else
			u = va_arg(args, unsigned long);
	}
	else
		u = fetch_unsigned_arg(pf, args);
	char *expand1 = itoa_unsigned(u, 10, pf->type);
    if ((u == 0 && pf->flags.dot != -1) || (u == 0 && pf->flags.implicit_dot))
    {
        if (pf->spec[i] == '.')
                return (ulen);
    }
	if (pf->flags.width > ft_strlen(expand1) && (pf->flags.dot < (int) pf->flags.width))
	{
        int diff = (int) (pf->flags.width - ft_strlen(expand1));
        if (pf->flags.dot != -1 && pf->flags.dot > (int) ft_strlen(expand1) && (pf->flags.dot < (int) pf->flags.width))
            diff = (int) (diff - (pf->flags.dot - ft_strlen(expand1)));
        if (pf->flags.minus)
            ulen += write(1, expand1, ft_strlen(expand1));
        while (diff--)
            ulen += write(1, pf->flags.zero ? "0" : " ", 1);
    }
    if (pf->flags.dot != -1 && pf->flags.dot > (int) ft_strlen(expand1))
    {
        int udiff = pf->flags.dot - ft_strlen(expand1);
        while (udiff--)
            ulen += write(1, "0", 1);
    }
        if (pf->flags.minus)
            return (ulen);
        else if (pf->flags.len)
            return ( ulen + write(1, expand1, ft_strlen(expand1)) + free_deluxe((void **)&expand1));
        else
            return (int) (ulen + write(1, expand1, ft_strlen(expand1)) + free_deluxe((void **)&expand1));
}

int	get_sS(t_pf *pf, va_list args)
{
	int slen = 0;
	char *count = 0;
    int onelen = 0;

    size_t strlen = 0;
	if (pf->type == 's' && !pf->flags.len)
		count = va_arg(args, char *);
	else if (pf->type == 'S' || pf->flags.len)
	{
		unsigned int (*str) = va_arg(args, unsigned int *);
		if (!str)
		{
			slen += write(1, "(null)", 6);
			return (slen);
		}
		while(*str)
		{
			char *one = ft_get_unistr(*str);
            onelen = ft_strlen(one);
			char *tmp = count;
			count = ft_strjoin(count ? count : "", one);
			ft_memdel((void **)&tmp);
			ft_memdel((void **)&one);
			str++;
		}
		if (count)
            strlen = ft_strlen(count);
		if (pf->flags.dot != -1 && pf->flags.dot < (int)strlen)
        {
            if (pf->flags.dot == onelen)
                strlen = pf->flags.dot;
            else if (pf->flags.width && pf->flags.dot > (int) pf->flags.width)
                strlen = pf->flags.dot;
            else
                strlen = onelen;
        }
		if (pf->flags.implicit_dot && pf->flags.width)
        {
            if ((int) pf->flags.width != onelen)
            {
                strlen = 0;
                while (pf->flags.width)
                {
                    strlen += write(1, pf->flags.zero ? "0" : " ", 1);
                    pf->flags.width--;
                }
                return (int) (strlen);
            }
            else
                strlen = pf->flags.width;
        }
		if (pf->flags.width && pf->flags.width > strlen)
		{
			int differ = pf->flags.width - strlen;
			if (pf->flags.minus)
				slen += write(1, count, strlen);
			while (differ)
			{
				slen += write(1, pf->flags.zero ? "0" : " ", 1);
				differ--;
			}
		}
		if (pf->flags.minus)
			return (slen);
		return (int) (slen + write(1, count, strlen) + free_deluxe((void **)&count));
	}
    if (pf->flags.implicit_dot && !count)
    {
        if (pf->flags.width)
        {
            while (pf->flags.width)
            {
                strlen += write(1, pf->flags.zero ? "0" : " ", 1);
                pf->flags.width--;
            }
            return (int) (strlen);
        }
        return (int) (strlen);
    }
	if (!count)
	{
		slen += write(1, "(null)", 6);
		return (slen);
	}
    	strlen = ft_strlen(count);
    if (pf->flags.dot != -1 && pf->flags.dot < (int)strlen)
        strlen = (size_t) pf->flags.dot;
	if (pf->flags.width && pf->flags.width > strlen)
	{
		int differ = (int) (pf->flags.width - strlen);
        if (pf->flags.minus)
            slen += write(1, count, strlen);
		while (differ)
        {
            slen += write(1, pf->flags.zero ? "0" : " ", 1);
            differ--;
        }
	}
    if (*count == '\0')
        return (int) (pf->flags.width ? pf->flags.width : 0);
    else if (pf->flags.minus && pf->flags.width)
    {
        if (pf->flags.dot == -1)
            return (slen);
        return (int) (slen + write(1, count, strlen - pf->flags.dot));
    }
    else if (pf->flags.dot == -1)
	{
		if (pf->flags.implicit_dot)
		{
			while(pf->flags.width - ft_strlen(count))
			{
				slen += write(1,  pf->flags.zero ? "0" : " ", 1);
				pf->flags.width--;
			}
			return (slen);
		}
		return (int) (slen + write(1, count, strlen));
	}
    else
        return (int) (slen + write(1, count, strlen));
}

 int	get_cC(t_pf *pf, va_list args)
 {
     int len1 = 0;
	 char ch = 0;
	 if (pf->type == 'C' || pf->flags.len)
	 {
		 int uni = va_arg(args, unsigned int);
		 if (!uni)
			 return (len1 + ft_putchar(uni));
		 char *ch = ft_unicode(uni);
		 if (pf->flags.width > 1)
		 {
			 size_t dr = pf->flags.width - 1;
			 if (pf->flags.minus)
				 len1 += write(1, ch, ft_strlen(ch));
			 while (dr--)
				 len1 += write(1, pf->flags.zero ? "0" : " ", 1);
		 }
		 if (pf->flags.minus)
			 return (len1);
		 else
			 return (int) (len1 + write(1, ch, ft_strlen(ch)) + free_deluxe((void **)&ch));
	 }
     ch = (char)va_arg(args, int);
     if (pf->flags.width > 1)
     {
         size_t dr = pf->flags.width - 1;
		 if (pf->flags.minus)
			 len1 += ft_putchar(ch);
         while (dr--)
             len1 += write(1, pf->flags.zero ? "0" : " ", 1);
     }
	 if (pf->flags.minus)
		 return (len1);
	 else
		 return(len1 + ft_putchar(ch));
 }

 ssize_t	get_xX(t_pf *pf, va_list args)
 {
     ssize_t lenx = 0;
     ssize_t i = 0;
     size_t r = 0;
     size_t d = 0;
     ssize_t lenX = 0;
	 size_t big_x_len = 0;
	 size_t little_x_len = 0;
	 unsigned long long iter = 0;
	 iter = fetch_unsigned_arg(pf, args);
     char *uns_iter = itoa_unsigned(iter, 16, pf->type);
	 big_x_len = ft_strlen(uns_iter);
	 little_x_len = ft_strlen(uns_iter);
     if (pf->type == 'X')
     {
         if (pf->flags.dot == 0 && iter == 0)
             return (lenX);
         if (pf->flags.dot == -1 && iter == 0)
         {
             if (pf->spec[i] == '.')
                 return (lenX);
             if (pf->spec[i + 1] == '.' && !pf->flags.width)
                 return (lenX);
             if (pf->flags.width && pf->spec[i + 1] == '.') {
                 int wtf = pf->flags.width;
                 while (wtf--)
                     lenX += write(1, " ", 1);
                 return (lenX);
             }
         }
         if (pf->flags.width > big_x_len) {
             if (pf->flags.dot != -1 && pf->flags.dot > (int) big_x_len) {
                 if (pf->flags.dot > (int) pf->flags.width) {
                     d = 0;
                     pf->flags.zero = 1;
                 } else
                     d = pf->flags.width - (size_t) pf->flags.dot;
             } else
                 d = pf->flags.width - big_x_len;
             if (pf->flags.hash) {
                 d = d - 2;
                 if (pf->flags.zero)
                     lenX += write(1, "0x", 2);
             }
             if (pf->flags.minus)
                 lenX += write(1, uns_iter, big_x_len);
             while (d--)
                 lenX += write(1, pf->flags.zero ? "0" : " ", 1);
         }
         if ((pf->flags.hash && iter != 0 && !pf->flags.width) || (pf->flags.hash && iter != 0 && !pf->flags.zero))
             lenX += write(1, "0X", 2);
         if (pf->flags.minus)
             return (lenX);
         else if (pf->flags.dot != -1)
         {
             if ((pf->flags.dot > (int) big_x_len && !pf->flags.width) || (pf->flags.dot > (int) big_x_len && pf->flags.width && (pf->flags.width > (size_t) pf->flags.dot)))
                 pf->flags.zero = 1;
             if (pf->flags.dot > (int) big_x_len)
             {
                 if (pf->flags.hash || (pf->flags.dot != -1 && pf->flags.dot > (int) big_x_len))
                     pf->flags.zero = 1;
                 while (pf->flags.dot - big_x_len != 0)
                 {
                     lenX += write(1, pf->flags.zero ? "0" : " ", 1);
                     pf->flags.dot--;
                 }
                 return ( lenX + write(1, uns_iter, ft_strlen(uns_iter)) + free_deluxe((void **)&uns_iter));
             }
             else
                 return (lenX + write(1, uns_iter, ft_strlen(uns_iter)) + free_deluxe((void **)&uns_iter));
            }
		  else if (pf->flags.len)
		  {
			  if (pf->flags.hash && iter != '0')
				  lenX += write(1, "0X", 2);
			  return ( lenX + write(1, uns_iter, ft_strlen(uns_iter)) + free_deluxe((void **)&uns_iter));
		  }
		  else
      		return ( lenX + write(1, uns_iter, big_x_len)) + free_deluxe((void **)&uns_iter);
      }
      if (pf->type == 'x')
      {
          if ((pf->flags.dot == -1 && iter == 0) || (pf->flags.dot != -1 && iter == 0))
          {
              if (pf->spec[i] == '.')
                  return (lenx);
			  if (pf->spec[i + 1] == '.' && !pf->flags.width)
				  return (lenx);
			  if (pf->flags.width && pf->spec[i + 1] == '.') // fixed 048 test
			  {
				  int wtf = pf->flags.width;
				  while (wtf--)
				  	lenx += write(1, " ", 1);
				  return (lenx);
			  }
		  }
          if (pf->flags.width > little_x_len)
          {
              if (pf->flags.dot != -1 && pf->flags.dot > (int) little_x_len) {
                  if (pf->flags.dot > (int) pf->flags.width)
                  {
                      r = 0;
                      pf->flags.zero = 1;
                  }
                  else
                    r = pf->flags.width - (size_t) pf->flags.dot;
              }
              else
                  r = pf->flags.width - (int) little_x_len;
			  if (pf->flags.hash)
			  {
				  r = r - 2;
				  if (pf->flags.zero)
				  	lenx += write(1, "0x", 2);
			  }
              if (pf->flags.zero && pf->flags.hash && pf->flags.minus)
                  pf->flags.zero = 0;
			  if (pf->flags.minus)
                  lenx += write(1, uns_iter, little_x_len);
              while (r--)
				  lenx += write(1, pf->flags.zero ? "0" : " ", 1);
          }
      }
     if (!pf->flags.zero && pf->flags.hash && pf->flags.minus)
         pf->flags.zero = 1;
	 if (pf->flags.hash && iter != 0 && (!pf->flags.width || !pf->flags.zero) && !pf->flags.len)
         lenx += write(1, "0x", 2);
	 if (pf->flags.minus)
		 return (lenx);
     if (pf->flags.dot != -1)
     {
         if ((pf->flags.dot > (int) little_x_len && !pf->flags.width) || (pf->flags.dot > (int) little_x_len && pf->flags.width && (pf->flags.width > (size_t) pf->flags.dot)))
             pf->flags.zero = 1;
         if (pf->flags.dot > (int) little_x_len)
         {
             if (pf->flags.hash || (pf->flags.dot != -1 && pf->flags.dot > (int) little_x_len))
                 pf->flags.zero = 1;
             while (pf->flags.dot - little_x_len != 0)
             {
                 lenx += write(1, pf->flags.zero ? "0" : " ", 1);
                 pf->flags.dot--;
             }
             return ( lenx + write(1, uns_iter, ft_strlen(uns_iter)) + free_deluxe((void **)&uns_iter));
         }
         else
            return (lenx + write(1, uns_iter, ft_strlen(uns_iter)) + free_deluxe((void **)&uns_iter));
     }
	 else if (pf->flags.len)
	 {
		 if (pf->flags.hash && iter != '0')
			 lenx += write(1, "0x", 2);
		 return ( lenx + write(1, uns_iter, ft_strlen(uns_iter)) + free_deluxe((void **)&uns_iter));
	 }
	 else
     	return (lenx + write(1, uns_iter, little_x_len) + free_deluxe((void **)&uns_iter));
 }

 int	get_p(t_pf *pf, va_list args)
 {
	 size_t lenp = 0;
	 unsigned long long test = va_arg(args, unsigned long long);
	 char *exp = itoa_unsigned(test, 16, pf->type);
	 if (pf->flags.minus || (!pf->flags.minus && pf->flags.zero && pf->flags.width))
	 {
		 lenp += write(1, "0x", 2);
		 lenp += write(1, exp, ft_strlen(exp));
	 }
	 if (pf->flags.width > 1 && exp)
	 {
		 if (pf->flags.dot != -1 && pf->flags.dot < (int) (lenp) && pf->flags.width)
			 lenp = (size_t) pf->flags.dot;
		 if (pf->flags.dot == -1 && pf->flags.width > lenp)
		 {
		 	int pi = lenp > 0 ? pf->flags.width - lenp : pf->flags.width - 3;
		 	while (pi--)
			 	lenp += write(1, pf->flags.zero ? "0" : " ", 1);
		 }
	 }
	 if (pf->flags.width && test == 0 && !pf->flags.minus && !pf->flags.zero)
	 {
		 lenp += write(1, "0x", 2);
		 lenp += write(1, exp, ft_strlen(exp));
		 return (int) (lenp);
	 }
	 else if (!pf->flags.minus && !pf->flags.zero)
	 {
         if (pf->flags.width && pf->flags.dot != -1 && (pf->flags.dot < (int) pf->flags.width) && test != 0)
         {
             int pi = (int) (lenp > 0 ? pf->flags.width - lenp : pf->flags.width - (ft_strlen(exp) + 2));
             while (pi--)
                 lenp += write(1, pf->flags.zero ? "0" : " ", 1);
             lenp += write(1, "0x", 2);
             lenp += write(1, exp, ft_strlen(exp));
             return(lenp);
         }
         lenp += write(1, "0x", 2);
         if (pf->flags.dot != -1 && pf->flags.dot > (int) pf->flags.width && test != 0)
         {
             int pi = (int) (pf->flags.dot - ft_strlen(exp));
             while (pi--)
                 lenp += write(1, "0", 1);
             lenp += write(1, exp, ft_strlen(exp));
             return(lenp);
         }
         if (pf->flags.implicit_dot || (pf->flags.dot == 0 && test == 0))
             return(lenp);
         if ((pf->flags.dot != -1 && test == 0))
         {
             lenp += write(1, exp, ft_strlen(exp));
             pf->flags.dot = (int) (pf->flags.dot - ft_strlen(exp));
             while (pf->flags.dot != 0)
             {
                 lenp += write(1, "0", 1);
                 pf->flags.dot--;
             }
         }
         else
             lenp += write(1, exp, ft_strlen(exp));
	 }
	 free(exp);
 	return (int) (lenp);
 }

 int	get_oO(t_pf *pf, va_list args)
 {
	 int leno = 0;
     int i = 0;
	 char *ex = 0;
     int ifdot = 0;
	 unsigned long long octal = pf->type == 'O' ? va_arg(args, unsigned long long) : fetch_unsigned_arg(pf, args);
	 ex = itoa_unsigned(octal, 8, pf->type);
     size_t len_ex = ft_strlen(ex);
     if (pf->flags.width && pf->flags.dot != -1 && (int) pf->flags.width > pf->flags.dot && octal != 0 && !pf->flags.minus && pf->flags.width > len_ex)
     {
         ifdot = (int) (pf->flags.width - len_ex);
         if ((int) len_ex < pf->flags.dot)
             ifdot = (int) (ifdot - (pf->flags.dot - len_ex));
         while (ifdot)
         {
             leno += write(1, pf->flags.zero ? "0" : " ", 1);
             ifdot--;
         }
     }
     if (pf->flags.dot != -1)
         pf->flags.zero = 1;
	 if (pf->flags.dot != -1 && pf->flags.dot < (int)len_ex && pf->flags.width && (int) pf->flags.width < pf->flags.dot && pf->flags.width > len_ex)
         len_ex = pf->flags.dot;
     if (pf->flags.dot != -1 && pf->flags.dot > (int)len_ex)
     {
         ifdot = pf->flags.dot - (int)len_ex;
        while (ifdot)
        {
             leno += write(1, pf->flags.zero ? "0" : " ", 1);
            ifdot--;
        }
     }
	 if (octal == 0 && pf->flags.dot != -1)
	 {
		 if (pf->flags.width && pf->spec[i + 1] == '.') // fixed 094 test
		 {
			 int wtf = pf->flags.width;
			 while (wtf--)
				 leno += write(1, " ", 1);
			 return (leno);
		 }
	 }
     if (pf->flags.width && pf->flags.width > len_ex && octal != 0)
	 {
		 int dt = pf->flags.width - len_ex;
		 if (pf->flags.minus)
         {
             if (pf->flags.dot == -1)
             {
                 if (pf->flags.hash && octal != 0  && pf->flags.minus) // fixed 88
                 {
                     leno += write(1, "0", 1);
                     leno += write(1, ex, ft_strlen(ex));
                 }
                 else
                    leno += write(1, ex, ft_strlen(ex));
             }
         }
		 if (pf->flags.hash)
			 dt = dt - 1;
         if (pf->flags.dot == -1)
         {
             while (dt--)
                 leno += write(1, pf->flags.zero ? "0" : " ", 1);
         }
	 }
     if (octal == 0 && pf->flags.dot == -1)
     {
         if (pf->spec[i] == '.')
            return (leno);
		 if (pf->flags.width && pf->spec[i + 1] == '.') // fixed 048 test
		 {
			 int wtf = pf->flags.width;
			 while (wtf--)
				 leno += write(1, " ", 1);
			 return (leno);
		 }
         return (write(1, "0", 1));
     }
     if (octal == 0 && pf->flags.hash)
         return (write(1, "0", 1));
	 if (pf->flags.hash && octal != 0  && !pf->flags.minus && pf->flags.dot == -1)
		 leno += write(1, "0", 1);
     else if (pf->flags.minus && pf->flags.width)
     {
         if (pf->flags.dot == -1)
             return (leno);
         if (pf->flags.dot != -1 && pf->flags.width)
         {
             leno += write(1, ex, len_ex); //fixed 91 test
             while ((int)pf->flags.width-- > pf->flags.dot)
                 leno += write(1, " ", 1);
             return (leno);
         }
         else
            return (int) (leno + write(1, ex, len_ex) + free_deluxe((void **)&ex));
     }
     else if (pf->flags.dot != -1)
	 {
		 if (octal == 0)
			 return (leno);
		 return (int) (leno + write(1, ex, len_ex) + free_deluxe((void **)&ex));
	 }
	 if (pf->flags.minus)
		 return (leno);
	 else
	 	return (leno + write(1, ex, ft_strlen(ex)) + free_deluxe((void **)&ex));
 }

int	get_b(t_pf *pf, va_list args)
{
	int leno = 0;
	int i = 0;
	int b = va_arg(args, int);
	char *ex = ft_itoa_base(b, 2);
	size_t len_ex = ft_strlen(ex);
	if (pf->flags.dot != -1)
		pf->flags.zero = 1;
	if (pf->flags.dot != -1 && pf->flags.dot < (int)len_ex)
		len_ex = pf->flags.dot;
	if (pf->flags.dot != -1 && pf->flags.dot > (int)len_ex)
	{
		int ifdot = pf->flags.dot - (int)len_ex;
		while (ifdot)
		{
			leno += write(1, pf->flags.zero ? "0" : " ", 1);
			ifdot--;
		}
	}
	if (b == 0 && pf->flags.dot != -1)
	{
		if (pf->flags.width && pf->spec[i + 1] == '.') // fixed 094 test
		{
			int wtf = pf->flags.width;
			while (wtf--)
				leno += write(1, " ", 1);
			return (leno);
		}
	}
	if (pf->flags.width && pf->flags.width > len_ex && b != 0)
	{
		int dt = pf->flags.width - len_ex;
		if (pf->flags.minus)
		{
			if (pf->flags.dot == -1)
			{
				if (pf->flags.hash && b != 0  && pf->flags.minus) // fixed 88
				{
					leno += write(1, "0", 1);
					leno += write(1, ex, ft_strlen(ex));
				}
				else
					leno += write(1, ex, ft_strlen(ex));
			}
		}
		if (pf->flags.hash)
			dt = dt - 1;
		if (pf->flags.dot == -1)
		{
			while (dt--)
				leno += write(1, pf->flags.zero ? "0" : " ", 1);
		}
	}
	if (b == 0 && pf->flags.dot == -1)
	{
		if (pf->spec[i] == '.')
			return (leno);
		if (pf->flags.width && pf->spec[i + 1] == '.') // fixed 048 test
		{
			int wtf = pf->flags.width;
			while (wtf--)
				leno += write(1, " ", 1);
			return (leno);
		}
		return (write(1, "0", 1));
	}
	if (b == 0 && pf->flags.hash)
		return (write(1, "0", 1));
	if (pf->flags.hash && b != 0  && !pf->flags.minus)
		leno += write(1, "0", 1);
	else if (pf->flags.minus && pf->flags.width)
	{
		if (pf->flags.dot == -1)
			return (leno);
		if (pf->flags.dot != -1 && pf->flags.width)
		{
			leno += write(1, ex, len_ex); //fixed 91 test
			while ((int)pf->flags.width-- > pf->flags.dot)
				leno += write(1, " ", 1);
			return (leno);
		}
		else
			return (int) (leno + write(1, ex, len_ex) + free_deluxe((void **)&ex));
	}
	else if (pf->flags.dot != -1)
		return (int) (leno + write(1, ex, len_ex) + free_deluxe((void **)&ex));
	if (pf->flags.minus)
		return (leno);
	else
		return (leno + write(1, ex, ft_strlen(ex)) + free_deluxe((void **)&ex));
}

int	get_percent(t_pf *pf, va_list args)
{
	int plen;

	plen = 0;
	(void)args;
	if (pf->flags.width > 1)
	{
		int diff = pf->flags.width - 1;
		if (pf->flags.minus)
			plen += write(1, "%", 1);
		while (diff--)
			plen += write(1, pf->flags.zero ? "0" : " ", 1);
	}
	if (pf->flags.minus)
		return (plen);
	else
		return (int) (plen + write(1, "%", 1));
}

int	get_unknown(t_pf *pf, va_list args)
{
	int unknownlen = 0;
    (void)args;
    char wtf = pf->type;
	if (pf->flags.width > 1 && wtf)
	{
		int di = pf->flags.width - 1;
		while (di--)
			unknownlen += write(1, pf->flags.zero ? "0" : " ", 1);
	}
	if (wtf)
		return (int) (unknownlen + write(1, &wtf, 1));
	else
		return (0);
}

/*
** 1. Parse flags
** 2. Parse width
** 3. Parse length
** 4. Parse prec.
*/

void	parse_specifier(t_pf *pf)
{
	parse_flags(pf);
	parse_width(pf);
	parse_length(pf);
	parse_prec(pf);
	parse_implicit_dot(pf);
}

int		map_specifier(t_pf *pf, va_list args)
{
	// Map convertion type to appropriate function
	if (pf->type == 'd' || pf->type == 'D'|| pf->type == 'i')
		return (get_dDi(pf, args));
	else if (pf->type == 's' || pf->type == 'S')
		return(get_sS(pf, args));
	 else if (pf->type == 'o' || pf->type == 'O')
	 	return(get_oO(pf, args));
	 else if (pf->type == 'x' || pf->type == 'X')
	 	return(get_xX(pf, args));
	 else if (pf->type == 'c' || pf->type == 'C')
		return(get_cC(pf, args));
	else if (pf->type == 'f' || pf->type == 'F')
		return(get_fF(pf, args));
	else if (pf->type == 'Z')
		return(get_Z(pf));
	else if (pf->type == 'u' || pf->type == 'U')
		return(get_uU(pf, args));
	else if (pf->type == 'b')
		return(get_b(pf, args));
	 else if (pf->type == 'p')
	 	return(get_p(pf, args));
	 else if (pf->type == '%')
	 	return(get_percent(pf, args));
	else
		return(get_unknown(pf, args));
}

int		ft_printf(const char *format, ...)
{
	va_list args;
	t_pf 	*spec;
	int		res;

	res = 0;
	va_start(args, format);
    spec = malloc(sizeof(t_pf));
	while (*format)
	{
        int len = 0;
		if (*format && *format == '%')
		{
			ft_init(spec);
			if (*format && !*(format + 1))
				return(res);
			if (*format && *(format + 1) != '\0')
				format++;
			size_t ret = cut_specifier(format, spec);
			if (ret > 0)
            	parse_specifier(spec);
			res += map_specifier(spec, args);
			format += ret + 1;
		}
		while ((*format && *format != '%'))
		{
			len++;
			format++;
		}
		if (len)
			res += write(1, format - len, len);
	}
    ft_memdel((void **)&spec);
	va_end(args);
	return (res);
}
