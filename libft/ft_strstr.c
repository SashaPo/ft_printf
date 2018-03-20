/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:11:34 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/09 16:47:25 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *where, const char *tofind)
{
	size_t	a;
	size_t	b;

	a = 0;
	if (tofind[0] == '\0')
		return ((char*)&where[0]);
	while (where[a] != '\0')
	{
		b = 0;
		while (where[a + b] == tofind[b] && tofind[b] != '\0')
			b++;
		if (tofind[b] == '\0')
			return ((char*)&where[a]);
		a++;
	}
	return (NULL);
}
