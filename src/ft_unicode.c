/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 17:00:18 by opokusyn          #+#    #+#             */
/*   Updated: 2018/03/24 17:00:21 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <locale.h>

static char	*ft_get_1byte(unsigned int nbr)
{
	char	*res;

	res = ft_strnew(1);
	res[0] = (char)nbr;
	return (res);
}

static char	*ft_get_2bytes(unsigned int nbr)
{
	char	*res;

	res = ft_strnew(2);
	res[1] = (char)((nbr & 63) | (1 << 7));
	res[0] = (char)(((nbr >> 6) & 63) | 192);
	return (res);
}

static char	*ft_get_3bytes(unsigned int nbr)
{
	char	*res;

	res = ft_strnew(3);
	res[2] = (char)((nbr & 63) | (1 << 7));
	res[1] = (char)(((nbr >> 6) & 63) | (1 << 7));
	res[0] = (char)(((nbr >> 12) & 63) | 224);
	return (res);
}

static char	*ft_get_4bytes(unsigned int nbr)
{
	char	*res;

	res = ft_strnew(4);
	res[3] = (char)((nbr & 63) | (1 << 7));
	res[2] = (char)(((nbr >> 6) & 63) | (1 << 7));
	res[1] = (char)(((nbr >> 12) & 63) | (1 << 7));
	res[0] = (char)(((nbr >> 18)) | 240);
	return (res);
}

char		*ft_unicode(unsigned int uni)
{
	char	*res;

	res = NULL;
	if (uni < (1 << 7))
		res = ft_get_1byte(uni);
	else if (uni < (1 << 11))
		res = ft_get_2bytes(uni);
	else if (uni < (1 << 16))
		res = ft_get_3bytes(uni);
	else
		res = ft_get_4bytes(uni);
	return (res);
}
