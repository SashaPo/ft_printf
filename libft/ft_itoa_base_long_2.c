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

int		get_len(unsigned long long value, int base)
{
	int				len;

	if (value == 0)
		len = 1;
	else
		len = 0;
	while (value != 0)
	{
		value /= base;
		len++;
	}
	return (len);
}

int		get_len2(long long value, int base)
{
	int				len;

	len = 0;
	while (value != 0)
	{
		value /= base;
		len++;
	}
	return (len);
}

char	*itoa_signed(long long int value, int base, char type)
{
	static char		radix[] = "0123456789ABCDEF";
	char			*ans;
	int				p;
	int				i;
	int				last_dig;

	if (base < 2 || 16 < base
		|| !(ans = (char *)malloc(sizeof(char) * (get_len2(value, base) + 2))))
		return (NULL);
	p = 0;
	if (base == 10 && value < 0)
		ans[p++] = '-';
	i = 0;
	while (i < get_len2(value, base))
	{
		last_dig = ABS(value % base);
		value /= base;
		ans[i++] = type == 'x' ? ft_tolower(radix[last_dig]) : radix[last_dig];
	}
	ans[i] = '\0';
	return (ans);
}

char	*itoa_u(unsigned long long value, int base, char type)
{
	static char		radix[] = "0123456789ABCDEF";
	char			*ans;
	int				len;
	unsigned int	last_digit;

	len = get_len(value, base);
	if (base < 2 || 16 < base
		|| !(ans = ft_strnew(len + 2)))
		return (NULL);
	while (len)
	{
		last_digit = value % base;
		value /= base;
		if (type >= 97 && type <= 122)
			ans[len-- - 1] = ft_tolower(radix[last_digit]);
		else
			ans[len-- - 1] = radix[last_digit];
	}
	return (ans);
}
