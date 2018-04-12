/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_o.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:41:24 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/07 14:41:26 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_two_cases(t_pf *pf, int leno)
{
	int					wtf;

	wtf = (int)pf->flags.width;
	while (wtf--)
		leno += write(1, " ", 1);
	return (leno);
}

int		ft_handle(t_pf *pf, unsigned long long octal, int leno, char *ex)
{
	int					dt;
	size_t				len_ex;

	len_ex = ft_strlen(ex);
	dt = (int)(pf->flags.width - len_ex);
	if (pf->flags.minus)
	{
		if (pf->flags.dot == -1)
		{
			if (pf->flags.hash && octal != 0 && pf->flags.minus)
			{
				leno += write(1, "0", 1);
				leno += write(1, ex, ft_strlen(ex));
			}
			else
				leno += write(1, ex, ft_strlen(ex));
		}
	}
	dt = pf->flags.hash ? dt - 1 : dt;
	if (pf->flags.dot == -1)
	{
		while (dt--)
			leno += write(1, pf->flags.zero ? "0" : " ", 1);
	}
	return (leno);
}

int		ft_handle_o(t_pf *pf, va_list args)
{
	int					leno;
	char				*ex;
	unsigned long long	octal;
	size_t				len_ex;

	octal = pf->type == 'O' ? va_arg(args, unsigned long long)
	: fetch_unsigned_arg(pf, args);
	ex = itoa_u(octal, 8, pf->type);
	len_ex = ft_strlen(ex);
	leno = ft_h_o(pf, len_ex, octal);
	if (octal == 0 && pf->flags.dot != -1)
	{
		if (pf->flags.width && pf->spec[1] == '.')
			return (ft_two_cases(pf, leno));
	}
	if (pf->flags.width && pf->flags.width > len_ex && octal != 0)
		leno = ft_handle(pf, octal, leno, ex);
	if (octal == 0 && pf->flags.dot == -1)
		return (ft_res1(pf, leno));
	if (octal == 0 && pf->flags.hash)
		return (int)(write(1, "0", 1));
	else
		return (res(pf, leno, octal, ex));
}
