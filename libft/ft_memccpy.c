/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 15:34:40 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/09 16:49:37 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char *a;
	unsigned char *b;

	a = (unsigned char *)dest;
	b = (unsigned char *)src;
	while (n)
	{
		*a++ = *b++;
		if (((unsigned char)c) == *((unsigned char *)b - 1))
		{
			return (a);
		}
		n--;
	}
	return (NULL);
}
