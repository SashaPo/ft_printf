/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:58:08 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/15 18:59:04 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *app, size_t dstsize)
{
	size_t dlen;
	size_t i;

	i = 0;
	dlen = ft_strlen(dest);
	if (dstsize <= dlen)
		return (dstsize + ft_strlen(app));
	while (dlen + i < dstsize - 1 && app[i])
	{
		dest[dlen + i] = app[i];
		i++;
	}
	dest[dlen + i] = '\0';
	return (dlen + ft_strlen(app));
}
