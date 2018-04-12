/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_b_for_binary.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:43:19 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/07 14:43:21 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_two_casesb(t_pf *pf, int leno)
{
	int					wtf;

	wtf = (int)pf->flags.width;
	while (wtf--)
		leno += write(1, " ", 1);
	return (leno);
}

int		ft_handleb(t_pf *pf, int b, int lenb, char *ex)
{
	int					dt;
	size_t				len_ex;

	len_ex = ft_strlen(ex);
	dt = (int)(pf->flags.width - len_ex);
	if (pf->flags.minus)
	{
		if (pf->flags.dot == -1)
		{
			if (pf->flags.hash && b != 0 && pf->flags.minus)
			{
				lenb += write(1, "0", 1);
				lenb += write(1, ex, ft_strlen(ex));
			}
			else
				lenb += write(1, ex, ft_strlen(ex));
		}
	}
	dt = pf->flags.hash ? dt - 1 : dt;
	if (pf->flags.dot == -1)
	{
		while (dt--)
			lenb += write(1, pf->flags.zero ? "0" : " ", 1);
	}
	return (lenb);
}

int		ft_handle_b(t_pf *pf, va_list args)
{
	int		lenb;
	int		i;
	int		b;
	char	*ex;
	size_t	len_ex;

	i = 0;
	b = va_arg(args, int);
	ex = ft_itoa_base(b, 2);
	len_ex = ft_strlen(ex);
	lenb = ft_h_o(pf, len_ex, b);
	if (b == 0 && pf->flags.dot != -1)
	{
		if (pf->flags.width && pf->spec[1] == '.')
			return (ft_two_casesb(pf, lenb));
	}
	if (pf->flags.width && pf->flags.width > len_ex && b != 0)
		lenb = ft_handleb(pf, b, lenb, ex);
	if (b == 0 && pf->flags.dot == -1)
		return (ft_res1(pf, lenb));
	if (b == 0 && pf->flags.hash)
		return (int)(write(1, "0", 1));
	else
		return (res(pf, lenb, b, ex));
}
