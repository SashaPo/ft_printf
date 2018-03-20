/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 17:58:32 by opokusyn          #+#    #+#             */
/*   Updated: 2018/03/11 18:03:36 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long int		nlen(long long int val)
{
	long long len;

	len = 0;
	if (val <= 0)
		len++;
	while (val != 0)
	{
		len++;
		val /= 10;
	}
	return (len);
}

char			*ft_itoa_long(long long int n)
{
	char	*res;
	long long int		strsize;
	long long int		sign;

	if (n >= 0)
		sign = 0;
	else
		sign = 1;
	strsize = nlen(n);
	if (!(res = (char*)malloc(sizeof(char) * (strsize + 1))))
		return (NULL);
	res[strsize] = '\0';
	if (n == 0)
		res[--strsize] = '0';
	while (n != 0)
	{
		if (n > 0)
			res[--strsize] = n % 10 + '0';
		else if (n < 0)
			res[--strsize] = '0' - (n % 10);
		n /= 10;
	}
	if (sign)
		res[0] = '-';
	return (res);
}

char			*ft_itoa_long_prec(long long int n, int prec)
{
	char	*res;
	long long int		strsize;
	long long int		sign;

	if (n >= 0)
		sign = 0;
	else
		sign = 1;
	strsize = nlen(n);
	if (prec >= 0 && prec > strsize)
		strsize = prec;
	if (!(res = ft_strnew(strsize)))
		return (NULL);
	if (n == 0)
		res[--strsize] = '0';
	while (n != 0)
	{
		if (n > 0)
			res[--strsize] = n % 10 + '0';
		else if (n < 0)
			res[--strsize] = '0' - (n % 10);
		n /= 10;
	}
	if (sign)
		res[0] = '-';
	while (prec >= 0 && strsize)
		res[--strsize] = '0';
	return (res);
}
