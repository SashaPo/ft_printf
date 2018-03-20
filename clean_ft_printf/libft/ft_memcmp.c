/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:13:44 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/09 16:49:29 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	unsigned char *a;
	unsigned char *b;

	a = (unsigned char*)arr1;
	b = (unsigned char*)arr2;
	while (n)
	{
		if (*a > *b || *a < *b)
			return (*a - *b);
		a++;
		b++;
		n--;
	}
	return (0);
}
