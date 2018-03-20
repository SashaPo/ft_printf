/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:33:28 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/15 15:33:09 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *app, size_t n)
{
	size_t dlen;

	dlen = ft_strlen(dest);
	while (n-- && *app != '\0')
	{
		dest[dlen++] = *app++;
	}
	dest[dlen] = '\0';
	return (dest);
}
