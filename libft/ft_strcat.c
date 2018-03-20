/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 12:14:04 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/15 15:33:33 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *app)
{
	char *a;

	a = dest;
	while (*a)
		a++;
	while (*app)
	{
		*a = *app;
		a++;
		app++;
	}
	*a = '\0';
	return (dest);
}
