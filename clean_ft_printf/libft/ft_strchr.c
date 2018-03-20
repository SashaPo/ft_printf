/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 17:48:19 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/15 19:32:47 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*a;
	size_t	len;

	a = (char *)str;
	len = ft_strlen(str);
	if ((unsigned char)c == '\0')
		return ((char *)&str[len]);
	else
	{
		while (len)
		{
			if (*a == (unsigned char)c)
				return (a);
			a++;
			len--;
		}
	}
	return (NULL);
}
