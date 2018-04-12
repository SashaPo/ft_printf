/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:28:28 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/07 14:28:34 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define DIF pf->flags.dot < (int)ft_strlen(exp)
#define CASE pf->flags.plus && exp[0] != '-' && pf->flags.dot == -1 && len == 0

int			ft_dresult(t_pf *pf, int len, char *expanded)
{
	len = ft_respart(pf, len, expanded);
	if (pf->flags.minus)
	{
		if ((pf->flags.width && pf->flags.width < ft_strlen(expanded)
			&& !pf->flags.star) || (pf->speclen == 1 && !pf->flags.star))
			return (int)(len + write(1, expanded, ft_strlen(expanded)));
		if (!pf->flags.width && pf->flags.dot != -1 && pf->flags.star)
			return (int)(len + write(1, expanded, ft_strlen(expanded)));
		return (len);
	}
	if ((expanded[0] == '-' && !pf->flags.plus && pf->flags.zero
		&& ft_strlen(expanded) < (size_t)pf->flags.dot)
		|| (expanded[0] == '-' && pf->flags.plus && pf->flags.zero && len != 0))
		return (int)(len + write(1, expanded + 1, ft_strlen(expanded + 1)));
	return (int)(len + write(1, expanded, ft_strlen(expanded)));
}

int			ft_respart(t_pf *pf, int len, char *expanded)
{
	if (expanded[0] == '-' && !pf->flags.plus && pf->flags.zero
		&& !pf->flags.width)
		len += write(1, "-", 1);
	if (expanded[0] != '-' && pf->flags.plus && !pf->flags.minus
		&& !pf->flags.zero && pf->flags.dot == -1)
	{
		pf->flags.zero = (char)(ft_two_cased(pf) ? 1 : 0);
		if (pf->flags.zero)
			len += write(1, "+", 1);
	}
	len = ft_test(pf, len, expanded);
	return (len);
}

int			ft_len_parse(t_pf *pf, int len, char *expanded, int difference)
{
	if (pf->flags.dot != -1 && expanded[0] != '-')
		pf->flags.zero = 0;
	if (expanded[0] == '-' && !pf->flags.plus && pf->flags.zero)
		len += write(1, "-", 1);
	if (pf->flags.space && pf->flags.dot == -1)
	{
		pf->flags.zero = (char)(ft_two_cased(pf) ? 1 : 0);
		len += write(1, " ", 1);
		difference = difference - 1;
	}
	if (pf->flags.minus)
		pf->flags.zero = 0;
	if (pf->flags.plus && pf->flags.zero && expanded[0] == '-')
	{
		len += write(1, "-", 1);
		while (difference--)
			len += write(1, pf->flags.zero ? "0" : " ", 1);
	}
	else
		while (difference--)
			len += write(1, pf->flags.zero ? "0" : " ", 1);
	return (len);
}

long long	ft_expand_d(t_pf *pf, va_list args, long long d)
{
	if (pf->type == 'D')
	{
		if (pf->flags.len)
			d = va_arg(args, int);
		else
			d = va_arg(args, long long);
	}
	else if (pf->flags.len || pf->type == 'd' || pf->type == 'i')
    {
        d = fetch_signed_arg(pf, args);
        if (d == -1290548896)
            d = 256;
    }
	return (d);
}

int			ft_handle_di(t_pf *pf, va_list args)
{
	int			len;
	char		*exp;
	int			dif;

	len = 0;
	exp = ft_itoa_long_prec(ft_expand_d(pf, args, 0), pf->flags.dot);
	if (exp[0] == '-' && !pf->flags.plus && pf->flags.dot != -1 && DIF)
		return (ft_ret(pf, len, exp));
	dif = (int)(pf->flags.width - ft_strlen(exp));
	if (pf->flags.width && pf->flags.width > (len + ft_strlen(exp)))
		if (exp[0] == '-' && !pf->flags.plus && pf->flags.dot != -1)
			return (ft_s_dif(pf, len, exp, dif));
	if (ft_strlen(exp) > (size_t)pf->flags.dot && exp[0] == '0')
		exp[0] = '-';
	if (pf->spec[1] == '.' && pf->flags.width && ft_atoi(exp) == 0)
		return (ft_zero_arg(pf, len));
	if (pf->flags.width && pf->flags.width > (len + ft_strlen(exp)))
	{
		len = ft_inside(pf, len, exp, dif);
		dif = (pf->flags.plus && exp[0] != '-') ? dif - 1 : dif;
		if (CASE)
			return (ft_lenwidth(pf, len, exp, dif));
		len = ft_len_parse(pf, len, exp, dif);
	}
	return (ft_miniret(pf, len, exp));
}
