/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_long_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 19:05:50 by opokusyn          #+#    #+#             */
/*   Updated: 2018/03/11 19:06:34 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define ABS(v) ((v) < 0 ? -(v) : (v))

//void	raux(long long int n, int b, char *ans, int *p)
//{
//	char	base[] = "0123456789ABCDEF";
//
//	if (n <= -b || b <= n)
//		raux(n / b, b, ans, p);
//	ans[(*p)++] = base[ABS(n % b)];
//}

int     get_len(unsigned long long value, int base)
{
    int len;

    if (value == 0)
        len = 1;
    else
        len = 0;
    while (value != 0)
    {
        value /= base;
        len++;
    }
    return(len);
}

int     get_len2(long long value, int base)
{
    int len;

    len = 0;
    while (value != 0)
    {
        value /= base;
        len++;
    }
    return(len);
}

char	*itoa_signed(long long int value, int base, char type)
{
    static char	radix[] = "0123456789ABCDEF";
    char	*ans;
	int		p;

    int len = get_len2(value, base);
    if (base < 2 || 16 < base
		|| !(ans = (char *)malloc(sizeof(char) * (len + 2))))
		return (NULL);
	p = 0;
	if (base == 10 && value < 0)
		ans[p++] = '-';
    int i = 0;
    while (i < len)
    {
        int last_digit = ABS(value % base);
        value /= base;
        ans[i++] = type == 'x' ? ft_tolower(radix[last_digit]) : radix[last_digit];
    }
//	raux(value, base, ans, &p);
	ans[i] = '\0';
	return (ans);
}


char	*itoa_unsigned(unsigned long long value, int base, char type)
{
    static char	radix[] = "0123456789ABCDEF";
    char	*ans;

    int len = get_len(value, base);
    if (base < 2 || 16 < base
        || !(ans = ft_strnew(len + 2)))
        return (NULL);
    while (len)
    {
        unsigned int last_digit = value % base;
        value /= base;
        if (type >= 97 && type <= 122)
            ans[len-- - 1] = ft_tolower(radix[last_digit]);
        else
            ans[len-- - 1] = radix[last_digit];
    }
//	raux(value, base, ans, &p);
    return (ans);
}

