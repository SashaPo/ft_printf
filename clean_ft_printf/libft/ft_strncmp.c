/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:10:26 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/16 16:16:30 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *str1, const char *str2, size_t n)
{
	while (n && *str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
		n--;
	}
	return (n == 0 ? 0 : (unsigned char)*str1 - (unsigned char)*str2);
}
