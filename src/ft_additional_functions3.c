/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional_functions3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 19:59:35 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/11 20:00:57 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		ft_lencheck(t_pf *pf, int onelen, size_t strlen)
{
	if (pf->flags.dot != -1 && pf->flags.dot < (int)strlen)
	{
		if (pf->flags.dot == onelen)
			strlen = (size_t)pf->flags.dot;
		else if (pf->flags.width && pf->flags.dot > (int)pf->flags.width)
			strlen = (size_t)pf->flags.dot;
		else
			strlen = (size_t)onelen;
	}
	return (strlen);
}

size_t		ft_strch(t_pf *pf, char *count, int onelen, size_t strlen)
{
	if (count)
		strlen = ft_strlen(count);
	strlen = ft_lencheck(pf, onelen, strlen);
	return (strlen);
}

int			ft_lenminus(t_pf *pf, int len, char *expanded)
{
	if (pf->flags.minus)
	{
		if (pf->flags.plus && expanded[0] != '-')
			len += write(1, "+", 1);
		len += write(1, expanded, ft_strlen(expanded));
	}
	return (len);
}

int			ft_lenplus(t_pf *pf, int len, char *expanded)
{
	if (pf->flags.plus && expanded[0] != '-' && pf->flags.dot == -1
		&& len == 0 && pf->flags.zero)
		len += write(1, "+", 1);
	return (len);
}

int			ft_lenwidth(t_pf *pf, int len, char *expanded, int dif)
{
	if (pf->flags.width > ft_strlen(expanded))
	{
		pf->flags.zero = (char)(ft_two_cased(pf) ? 1 : 0);
		if (pf->flags.zero)
			len += write(1, "+", 1);
		while (dif--)
			len += write(1, pf->flags.zero ? "0" : " ", 1);
	}
	len += !pf->flags.zero ? write(1, "+", 1) : 0;
	len += write(1, expanded, ft_strlen(expanded));
	return (len);
}
