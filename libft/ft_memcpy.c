/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 08:47:03 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/09 16:49:26 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *a;
	unsigned char *b;

	a = (unsigned char*)dest;
	b = (unsigned char*)src;
	while (n)
	{
		*a++ = *b++;
		n--;
	}
	return (dest);
}
