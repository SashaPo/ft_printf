/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 11:12:27 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/10 11:12:29 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_hc(int ifdot, int len, t_pf *pf)
{
	while (ifdot)
	{
		len += write(1, pf->flags.zero ? "0" : " ", 1);
		ifdot--;
	}
	return (len);
}

int		ft_res1(t_pf *pf, int leno)
{
	if (pf->spec[0] == '.')
		return (leno);
	if (pf->flags.width && pf->spec[1] == '.')
		return (ft_two_cases(pf, leno));
	return (int)(write(1, "0", 1));
}

int		ft_res_part(t_pf *pf, int leno, size_t len_ex, char *ex)
{
	if (pf->flags.dot == -1)
		return (leno);
	if (pf->flags.dot != -1 && pf->flags.width)
	{
		leno += write(1, ex, len_ex);
		while ((int)pf->flags.width-- > pf->flags.dot)
			leno += write(1, " ", 1);
		return (leno);
	}
	return (int)(leno + write(1, ex, len_ex) + free_deluxe((void **)&ex));
}

int		res(t_pf *pf, int leno, unsigned long long octal, char *ex)
{
	size_t				len_ex;

	len_ex = ft_strlen(ex);
	if (pf->flags.hash && octal != 0 && !pf->flags.minus
		&& pf->flags.dot == -1)
		leno += write(1, "0", 1);
	if (pf->flags.minus && pf->flags.width)
		return (ft_res_part(pf, leno, len_ex, ex));
	else if (pf->flags.dot != -1)
	{
		if (octal == 0)
			return (leno);
		return (int)(leno + write(1, ex, len_ex) + free_deluxe((void **)&ex));
	}
	if (pf->flags.minus)
		return (leno);
	return (int)(leno + write(1, ex, ft_strlen(ex))
		+ free_deluxe((void **)&ex));
}

int		ft_h_o(t_pf *pf, size_t len_ex, unsigned long long octal)
{
	int					len;
	int					ifdot;

	len = 0;
	if (pf->flags.width && pf->flags.dot != -1
		&& (int)pf->flags.width > pf->flags.dot && octal != 0
		&& !pf->flags.minus && pf->flags.width > len_ex)
	{
		ifdot = (int)(pf->flags.width - len_ex);
		if ((int)len_ex < pf->flags.dot)
			ifdot = (int)(ifdot - (pf->flags.dot - len_ex));
		len = ft_hc(ifdot, len, pf);
	}
	if (pf->flags.dot != -1)
		pf->flags.zero = 1;
	if (pf->flags.dot != -1 && pf->flags.dot < (int)len_ex && pf->flags.width
		&& (int)pf->flags.width < pf->flags.dot && pf->flags.width > len_ex)
		len_ex = pf->flags.dot;
	if (pf->flags.dot != -1 && pf->flags.dot > (int)len_ex)
	{
		ifdot = pf->flags.dot - (int)len_ex;
		len = ft_hc(ifdot, len, pf);
	}
	return (len);
}
