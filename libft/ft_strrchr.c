/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:11:07 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/15 21:18:12 by opokusyn         ###   ########.fr       */
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
