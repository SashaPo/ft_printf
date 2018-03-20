/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:13:36 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/16 19:05:17 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	without_c_len(char const *str, char c)
{
	size_t	without_c;

	without_c = 0;
	if (!str)
		return (0);
	while (*str != '\0')
	{
		if (*str != c)
			without_c++;
		if (*str == '\0')
			break ;
		str++;
	}
	return (without_c);
}

static	size_t	word_len(char const *s, char c)
{
	size_t	w_len;

	w_len = 0;
	while (*s != c && *s)
	{
		w_len++;
		s++;
	}
	return (w_len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	wlen;

	i = 0;
	if (!s)
		return (NULL);
	if (!(res = (char**)malloc(sizeof(char *) * (without_c_len(s, c) + 1))))
		return (NULL);
	while (*s != '\0')
	{
		if (*s != c)
		{
			wlen = word_len(s, c);
			res[i] = ft_strnew(wlen);
			ft_strncpy(res[i++], s, wlen);
			s = s + wlen;
		}
		if (*s == '\0')
			break ;
		s++;
	}
	res[i] = NULL;
	return (res);
}
