/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 14:43:26 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/09 16:49:12 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *memory, int ch, size_t n)
{
	unsigned char	*pointer;

	pointer = (unsigned char *)memory;
	while (n != '\0')
	{
		*pointer++ = (unsigned char)ch;
		n--;
	}
	return (memory);
}
