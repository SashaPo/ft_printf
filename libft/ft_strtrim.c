/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:13:24 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/14 18:25:15 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char		*ft_strtrim(char const *s)
{
	char	*dest;
	size_t	len;

	dest = 0;
	if (!s)
		return (NULL);
	while (is_space(*s))
		s++;
	len = ft_strlen(s);
	while (is_space(s[len - 1]) && len != '\0')
		len--;
	if (!(dest = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	ft_strncpy(dest, s, len);
	dest[len] = '\0';
	return (dest);
}
