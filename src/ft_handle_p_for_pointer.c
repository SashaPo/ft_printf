/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_p_for_pointer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:43:38 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/07 14:43:40 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_check_more(t_pf *pf, size_t lenp, char *exp)
{
	int					pi;

	pi = (int)(pf->flags.dot - ft_strlen(exp));
	while (pi--)
		lenp += write(1, "0", 1);
	lenp += write(1, exp, ft_strlen(exp));
	return (int)(lenp);
}

size_t	ft_check(t_pf *pf, char *exp, unsigned long long test)
{
	size_t				lenn;

	lenn = 2;
	if ((pf->flags.dot != -1 && test == 0))
	{
		lenn += write(1, exp, ft_strlen(exp));
		pf->flags.dot = (int)(pf->flags.dot - ft_strlen(exp));
		while (pf->flags.dot != 0)
		{
			lenn += write(1, "0", 1);
			pf->flags.dot--;
		}
	}
	else
		lenn += write(1, exp, ft_strlen(exp));
	return (lenn);
}

size_t	ft_cases(t_pf *pf, char *exp, size_t lenp)
{
	int					pi;

	pi = (int)(lenp > 0 ? pf->flags.width - lenp
						: pf->flags.width - (ft_strlen(exp) + 2));
	while (pi--)
		lenp += write(1, pf->flags.zero ? "0" : " ", 1);
	lenp += write(1, "0x", 2);
	lenp += write(1, exp, ft_strlen(exp));
	return (int)(lenp);
}

size_t	ft_cas(t_pf *pf, char *exp)
{
	size_t				len;
	size_t				pi;

	len = 0;
	if (pf->flags.minus || (!pf->flags.minus && pf->flags.zero
							&& pf->flags.width))
	{
		len += write(1, "0x", 2);
		len += write(1, exp, ft_strlen(exp));
	}
	if (pf->flags.width > 1 && exp)
	{
		if (pf->flags.dot != -1 && pf->flags.dot < (int)len && pf->flags.width)
			len = (size_t)pf->flags.dot;
		if (pf->flags.dot == -1 && pf->flags.width > len)
		{
			pi = len > 0 ? pf->flags.width - len : pf->flags.width - 3;
			while (pi--)
				len += write(1, pf->flags.zero ? "0" : " ", 1);
		}
	}
	return (len);
}

int		ft_handle_p(t_pf *pf, va_list args)
{
	size_t				lenp;
	unsigned long long	test;
	char				*exp;

	test = va_arg(args, unsigned long long);
	exp = itoa_u(test, 16, pf->type);
	lenp = ft_cas(pf, exp);
	if (pf->flags.width && test == 0 && !pf->flags.minus && !pf->flags.zero)
		return (int)(ft_exception_case(exp, lenp));
	else if (!pf->flags.minus && !pf->flags.zero)
	{
		if (pf->flags.width && pf->flags.dot != -1
			&& (pf->flags.dot < (int)pf->flags.width) && test != 0)
			return (int)(ft_cases(pf, exp, lenp));
		lenp += write(1, "0x", 2);
		if (pf->flags.dot != -1 && pf->flags.dot
			> (int)pf->flags.width && test != 0)
			return (int)(ft_check_more(pf, lenp, exp));
		if (pf->flags.implicit_dot || (pf->flags.dot == 0 && test == 0))
			return (int)(lenp);
		lenp = ft_check(pf, exp, test);
	}
	return (int)(lenp + free_deluxe((void **)&exp));
}
