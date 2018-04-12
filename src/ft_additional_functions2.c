/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional_functions2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:25:03 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/11 18:25:05 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_ifwidth(t_pf *pf, size_t strlen)
{
	while (pf->flags.width)
	{
		strlen += write(1, pf->flags.zero ? "0" : " ", 1);
		pf->flags.width--;
	}
	return (strlen);
}

int		ft_ifdiffer(t_pf *pf, char *count, int slen, size_t strlen)
{
	int				differ;

	differ = (int)(pf->flags.width - strlen);
	if (pf->flags.minus)
		slen += write(1, count, strlen);
	while (differ)
	{
		slen += write(1, pf->flags.zero ? "0" : " ", 1);
		differ--;
	}
	return (slen);
}

char	*ft_uni_code(char *count, unsigned int *str)
{
	char *tmp;
	char *one;

	while (*str)
	{
		tmp = ft_handle_unistr(*str);
		one = count;
		count = ft_strjoin(count ? count : "", tmp);
		free(one);
		free(tmp);
		str++;
	}
	return (count);
}

int		ft_uni_code1(unsigned int *str)
{
	int		onelen;
	char	*tmp;

	onelen = 0;
	while (*str)
	{
		tmp = ft_handle_unistr(*str);
		onelen = (int)ft_strlen(tmp);
		free(tmp);
		str++;
	}
	return (onelen);
}

int		f(void **ad)
{
	free(*ad);
	return (0);
}
