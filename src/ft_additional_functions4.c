/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional_functions4.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 22:18:26 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/11 22:20:21 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_inside(t_pf *pf, int len, char *expanded, int dif)
{
	dif = (int)(pf->flags.width - ft_strlen(expanded));
	len = ft_lenminus(pf, len, expanded);
	dif = (pf->flags.plus && expanded[0] != '-') ? dif - 1 : dif;
	len = ft_lenplus(pf, len, expanded);
	return (len);
}

int			ft_miniret(t_pf *pf, int len, char *expanded)
{
	if (ft_atoi(expanded) == 0 && pf->spec[0] == '.')
		return (len + f((void **)&expanded));
	return (ft_dresult(pf, len, expanded) + f((void **)&expanded));
}

int			ft_ret(t_pf *pf, int len, char *expanded)
{
	if (pf->flags.width)
		len = ft_first_diff(pf, len, expanded);
	return (int)(len + write(1, expanded, ft_strlen(expanded)));
}
