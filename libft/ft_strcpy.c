/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 10:45:44 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/12 18:37:21 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	char	*i;

	i = dst;
	while (*src != '\0')
	{
		*i++ = *src++;
	}
	*i = '\0';
	return (dst);
}
