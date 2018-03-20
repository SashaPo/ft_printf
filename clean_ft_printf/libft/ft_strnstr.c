/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:12:06 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/09 16:47:51 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t a;
	size_t b;

	a = -1;
	b = 0;
	if (little[0] == '\0')
		return ((char*)&big[0]);
	while (big[++a] != '\0' && a < n)
	{
		while (big[a + b] == little[b] && little[b] != '\0' && a + b < n)
			b++;
		if (little[b] == '\0')
			return ((char*)&big[a]);
	}
	return (NULL);
}
