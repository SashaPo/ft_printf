/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ulong.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:44:29 by opokusyn          #+#    #+#             */
/*   Updated: 2018/03/12 18:54:58 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long long int		nlen(unsigned long long int val)
{
	unsigned long long			len;

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

char								*ft_itoa_ulong(unsigned long long int n)
{
	char						*res;
	unsigned long long int		strsize;

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
		else
			res[--strsize] = '0' - (n % 10);
		n /= 10;
	}
	return (res);
}
