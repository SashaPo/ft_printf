/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 13:18:35 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/09 16:49:34 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int c, size_t len)
{
	unsigned char *a;

	a = (unsigned char *)ptr;
	while (len)
	{
		if (*a == (unsigned char)c)
			return (a);
		a++;
		len--;
	}
	return (NULL);
}
