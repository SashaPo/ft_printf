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

t_bool is_valid_type(char c)
{
	return (t_bool) (c == 'd' || c == 'i' || c == 'o' || c == 'x' || c == 'p' || c == 's'
                     || c == 'O' || c == 'u' || c == 'U' || c == 'D' || c == 'X' || c == 'c'
                     || c == '%' || c == 'S' || c == 'C');
}

size_t	specifier_len(const char *format)
{
	size_t len;

	len = 0;
	while (*format)
	{
		if (is_valid_type(*format))
			return (len);
		len++;
		format++;
	}
	return (len);
}

size_t	cut_specifier(const char *format, t_pf *pf)
{
	pf->speclen = specifier_len(format);
	pf->spec = (char *) format;
	pf->type = format[pf->speclen];
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
		if (pf->spec[i] >= '0' && pf->spec[i] <= '9' && pf->spec[i - 2] != '.')
			width = width * 10 + (pf->spec[i] - '0');
		i++;
		if (pf->spec[i] >= '0' && pf->spec[i] <= '9' && pf->spec[i - 1] == '.')
			i++;
		if ((pf->spec[i] >= '0' && pf->spec[i] <= '9') && (pf->spec[i + 1] >= '0' && pf->spec[i + 1] <= '9') && pf->spec[i - 1] != '.')
		{
			if (width != 0)
			{
				width = 0;
			}
			width = width * 10 + (pf->spec[i] - '0');
			i++;
		}
		pf->flags.width = TRUE;
	}
    pf->flags.width = width;
}

void	parse_length(t_pf *pf)
{
	size_t i = 0;
	while (i < pf->speclen)
	{
		if (pf->spec[i] == 'h' && pf->spec[i + 1] == 'h')
		{
			pf->flags.len = hh;
			i++;
		}
		else if (pf->spec[i] == 'h')
			pf->flags.len = h;
		else if (pf->spec[i] == 'l' && pf->spec[i + 1] == 'l')
			pf->flags.len = ll;
		else if (pf->spec[i] == 'l')
			pf->flags.len = l;
		else if (pf->spec[i] == 't')
			pf->flags.len = t;
		else if (pf->spec[i] == 'j')
			pf->flags.len = j;
		else if (pf->spec[i] == 'z')
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
		res = (long long)va_arg(args, int);
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
	else if (pf->flags.len == l || pf->flags.len == none)
		unres = va_arg(args, unsigned long);
	else if (pf->flags.len == j)
		unres = (uintmax_t)va_arg(args, uintmax_t);
	else if (pf->flags.len == z)
		unres = (size_t)va_arg(args, size_t);
	else if (pf->flags.len == ll)
		unres = (unsigned long long)va_arg(args, int);
	else if (pf->flags.len == hh)
		unres = (unsigned char)va_arg(args, int);
	return (unres);
}

int	get_dDi(t_pf *pf, va_list args)
{
	int len = 0;
    char *expanded = 0;
	long long int d = fetch_signed_arg(pf, args);

    expanded = ft_itoa_long_prec(d, pf->flags.dot);
	if (pf->flags.width && pf->flags.width > (len + ft_strlen(expanded)))
	{
		int difference = (int) (pf->flags.width - ft_strlen(expanded));
		if (pf->flags.minus)
			len += write(1, expanded, ft_strlen(expanded));
        if (pf->flags.plus)
            difference = difference - 1;
		if (pf->flags.dot != -1 && expanded[0] != '-')
			pf->flags.zero = 0;
        if (expanded[0] == '-' && !pf->flags.plus && pf->flags.zero)
            len += write(1, "-", 1);
		while (difference--)
            len += write(1, pf->flags.zero ? "0" : " ", 1);
	}
    if (expanded[0] == '-' && !pf->flags.plus && pf->flags.zero && !pf->flags.width)
        len += write(1, "-", 1);
	if (pf->flags.plus && expanded[0] != '-')
		len += write(1, "+", 1);
    if (pf->flags.space && !pf->flags.plus && !pf->flags.width)
    {
        if (expanded[0] == '-')
            expanded[0] = '-';
        else
            len += write(1, " ", 1);
    }
	if (pf->flags.minus)
		return (len);
    if (expanded[0] == '-' && !pf->flags.plus && pf->flags.zero)
    {
        while (expanded++)
            return (int) (len + write(1, expanded, ft_strlen(expanded)));

    }
    return (int) (len + write(1, expanded, ft_strlen(expanded)));
}

int	get_uU(t_pf *pf, va_list args)
{
	int ulen = 0;
	unsigned long long iteru = 0;
	unsigned int u = 0;
    unsigned long long int U = 0;
    if (pf->type == 'u')
    {
        if (!pf->flags.len)
            u = va_arg(args, int);
        if (pf->flags.len)
            iteru = fetch_unsigned_arg(pf, args);
        char *expand = ft_itoa_ulong(u);
        if (pf->flags.width > ft_strlen(expand))
        {
            int diff = pf->flags.width - ft_strlen(expand);
            if (pf->flags.minus)
                ulen += write(1, expand, ft_strlen(expand));
            while (diff--)
                ulen += write(1, pf->flags.zero ? "0" : " ", 1);
        }
        if (pf->flags.minus)
            return (ulen);
        else if (pf->flags.len)
            return ( ulen + write(1, ft_itoa_ulong(iteru), ft_strlen(ft_itoa_ulong(iteru))));
        else
            return (int) (ulen + write(1, ft_itoa_long(u), ft_strlen(ft_itoa_long(u))));
    }
    if (pf->type == 'U')
	{
		if (!pf->flags.len)
			U = va_arg(args, long long int);
		if (pf->flags.len) {
			U = va_arg(args, long long int);
			iteru = fetch_unsigned_arg(pf, args);
		}
		char *expand = ft_itoa_ulong(U);
		if (pf->flags.width && pf->flags.width > ft_strlen(expand))
		{
			int diff = pf->flags.width - ft_strlen(expand);
			if (pf->flags.minus)
				ulen += write(1, expand, ft_strlen(expand));
			while (diff--)
				ulen += write(1, pf->flags.zero ? "0" : " ", 1);
		}
	}
	if (pf->flags.minus)
		return (ulen);
	else if (pf->flags.len && U == 4294967296)
		return ( ulen + write(1, "4294967296", 10));
    else if (pf->flags.len)
        return ( ulen + write(1, ft_itoa_ulong(iteru), ft_strlen(ft_itoa_ulong(iteru))));
	else
		return (int) (ulen + write(1, ft_itoa_long(U), ft_strlen(ft_itoa_long(U))));
}

int	get_sS(t_pf *pf, va_list args)
{
	int slen = 0;
    size_t strlen = 0;
	char *count = va_arg(args, char *);
    if (!count)
    {
        slen += write(1, "(null)", 6);
        return (slen);
    }
    strlen = ft_strlen(count);
    if (pf->flags.dot != -1 && pf->flags.dot < (int)strlen)
        strlen = pf->flags.dot;
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
    if (*count == '\0')
        return (pf->flags.width ? pf->flags.width : 0);
    else if (pf->flags.minus && pf->flags.width)
    {
        if (pf->flags.dot == -1)
            return (slen);
        return (int) (slen + write(1, count, strlen - pf->flags.dot));
    }
    else if (pf->flags.dot == -1)
        return (int) (slen + write(1, count, strlen));
    else
        return (int) (slen + write(1, count, strlen));
}

 int	get_cC(t_pf *pf, va_list args)
 {
     int len1 = 0;
     char ch = (char)va_arg(args, int);
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
     ssize_t lenX = 0;
	 size_t big_x_len = 0;
	 size_t little_x_len = 0;
	 unsigned long long iter = 0;
	 unsigned int hexd = 0;
	 if (!pf->flags.len)
		 hexd = va_arg(args, int);
	 if (pf->flags.len)
         iter = fetch_unsigned_arg(pf, args);
	 big_x_len = ft_strlen(ft_itoa_base_long_2(hexd, 16));
	 little_x_len = ft_strlen(ft_itoa_base_long(hexd, 16));
     if (pf->type == 'X')
      {
          if (pf->flags.width > big_x_len)
          {
              size_t d = pf->flags.width - big_x_len;
			  if (pf->flags.hash)
			  {
				  d = d - 2;
				  if (pf->flags.zero)
					  lenX += write(1, "0x", 2);
			  }
			  if (pf->flags.minus)
				  lenX += write(1, ft_itoa_base_long_2(hexd, 16), big_x_len);
              while (d--)
                  lenX += write(1, pf->flags.zero ? "0" : " ", 1);
          }
		  if ((pf->flags.hash && hexd != 0 && !pf->flags.width) || (pf->flags.hash && hexd != 0 && !pf->flags.zero))
			  lenX += write(1, "0X", 2);
		  if (pf->flags.minus)
			  return (lenX);
		  else if (pf->flags.len)
		  {
			  if (pf->flags.hash && iter != '0')
				  lenX += write(1, "0X", 2);
			  return ( lenX + write(1, ft_itoa_base_long_2(iter, 16), ft_strlen(ft_itoa_base_long_2(iter, 16))));
		  }
		  else
      		return ( lenX + write(1, ft_itoa_base_long_2(hexd, 16), big_x_len));
      }
      if (pf->type == 'x')
      {
          if (pf->flags.width > little_x_len)
          {
			  size_t r = pf->flags.width - little_x_len;
			  if (pf->flags.hash)
			  {
				  r = r - 2;
				  if (pf->flags.zero)
				  	lenx += write(1, "0x", 2);
			  }
			  if (pf->flags.minus)
			  lenx += write(1, ft_itoa_base_long(hexd, 16), little_x_len);
              while (r--)
				  lenx += write(1, pf->flags.zero ? "0" : " ", 1);
          }
      }
	 if ((pf->flags.hash && hexd != 0 && !pf->flags.width) || (pf->flags.hash && hexd != 0 && !pf->flags.zero))
			 lenx += write(1, "0x", 2);
	 if (pf->flags.minus)
		 return (lenx);
	 else if (pf->flags.len)
	 {
		 if (pf->flags.hash && iter != '0')
			 lenx += write(1, "0x", 2);
		 return ( lenx + write(1, ft_itoa_base_long(iter, 16), ft_strlen(ft_itoa_base_long(iter, 16))));
	 }
	 else
     	return ( lenx + write(1, ft_itoa_base_long(hexd, 16), little_x_len));
 }

// int	get_p(t_pf *pf, va_list args)
// {
// 	return(0);
// }

 int	get_oO(t_pf *pf, va_list args)
 {
	 int leno = 0;
	 int octal = va_arg(args, int);
	 char *ex = ft_itoa_base(octal, 8);
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
     if (pf->flags.width && pf->flags.width > len_ex)
	 {
		 int dt = pf->flags.width - len_ex;
		 if (pf->flags.minus)
			 leno += write(1, ft_itoa_base(octal, 8), ft_strlen(ft_itoa_base(octal, 8)));
		 if (pf->flags.hash)
			 dt = dt - 2;
		 while (dt--)
			 leno += write(1, pf->flags.zero ? "0" : " ", 1);
	 }
     if (octal == 0)
         return (write(1, "0", 1));
	 if (pf->flags.hash && octal != 0)
		 leno += write(1, "0", 1);
     else if (pf->flags.minus && pf->flags.width)
     {
         if (pf->flags.dot == -1)
             return (leno);
         return (int) (leno + write(1, ft_itoa_base(octal, 8), len_ex));
     }
     else if (pf->flags.dot != -1)
         return (int) (leno + write(1,ft_itoa_base(octal, 8), len_ex));
	 if (pf->flags.minus)
		 return (leno);
	 else
	 	return ( leno + write(1, ft_itoa_base(octal, 8), ft_strlen(ft_itoa_base(octal, 8))));
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
	if (pf->flags.width > 1)
	{
		int di = pf->flags.width - 1;
		while (di--)
			unknownlen += write(1, pf->flags.zero ? "0" : " ", 1);
	}
	return (int) (unknownlen + write(1, &wtf, 1));
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
	else if (pf->type == 'u' || pf->type == 'U')
		return(get_uU(pf, args));
//	 else if (pf->type == 'p')
//	 	return(get_p(pf, args));
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
			if (*format)
				format++;
			size_t ret = cut_specifier(format, spec);
            parse_specifier(spec);
			res += map_specifier(spec, args);
			format += ret + 1;
		}
		while (*format && *format != '%')
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
