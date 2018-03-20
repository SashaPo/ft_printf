/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:47:30 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/09 16:49:16 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char *dst;
	unsigned char *str;

	dst = (unsigned char *)dest;
	str = (unsigned char *)src;
	if (dst < str)
	{
		while (len--)
			*dst++ = *str++;
	}
	else
	{
		while (len--)
			dst[len] = str[len];
	}
	return (dest);
}
