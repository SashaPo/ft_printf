/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:15:23 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/10 15:15:25 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nlen(int val)
{
	int len;

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

char			*ft_itoa(int n)
{
	char	*res;
	int		strsize;
	int		sign;

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

static int		dlen(double val)
{
	int len;

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

char			*ft_dtoa(double n)
{
	char	*res;
	int		strsize;
	int		sign;

	if (n >= 0)
		sign = 0;
	else
		sign = 1;
	strsize = dlen(n);
	if (!(res = (char*)malloc(sizeof(char) * (strsize + 1))))
		return (NULL);
	res[strsize] = '\0';
	if (n == 0)
		res[--strsize] = '0';
	while (n != 0)
	{
		if (n > 0)
			res[--strsize] = (char)(n - (n / 10 * 10) + '0');
		else if (n < 0)
			res[--strsize] = (char)('0' - (n - (n / 10 * 10)));
		n /= 10;
	}
	if (sign)
		res[0] = '-';
	return (res);
}
