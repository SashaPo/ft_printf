/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:43:00 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/07 14:43:02 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_get_diff(t_pf *pf, char *expand1)
{
	int				diff;
	int				len;

	len = 0;
	diff = (int)(pf->flags.width - ft_strlen(expand1));
	if (pf->flags.dot != -1 && pf->flags.dot > (int)ft_strlen(expand1)
		&& (pf->flags.dot < (int)pf->flags.width))
		diff = (int)(diff - (pf->flags.dot - ft_strlen(expand1)));
	if (pf->flags.minus)
		len += write(1, expand1, ft_strlen(expand1));
	while (diff--)
		len += write(1, pf->flags.zero ? "0" : " ", 1);
	return (len);
}

int		ft_get_ulen(t_pf *pf, char *expand1)
{
	int				udiff;
	int				len1;

	len1 = 0;
	if (pf->flags.width > ft_strlen(expand1)
		&& (pf->flags.dot < (int)pf->flags.width))
		len1 = ft_get_diff(pf, expand1);
	if (pf->flags.dot != -1 && pf->flags.dot > (int)ft_strlen(expand1))
	{
		udiff = (int)(pf->flags.dot - ft_strlen(expand1));
		while (udiff--)
			len1 += write(1, "0", 1);
	}
	return (len1);
}

int		ft_handle_u(t_pf *pf, va_list args)
{
	int				ulen;
	unsigned long	u;
	char			*expand1;

	if (!pf->flags.len || pf->type == 'U')
		u = pf->type == 'u' ? va_arg(args, unsigned int)
		: va_arg(args, unsigned long);
	else
		u = fetch_unsigned_arg(pf, args);
	expand1 = itoa_u(u, 10, pf->type);
	ulen = ft_get_ulen(pf, expand1);
	if ((u == 0 && pf->flags.dot != -1) || (u == 0 && pf->flags.implicit_dot))
		return (ulen);
	if (pf->flags.minus)
		return (ulen);
	else if (pf->flags.dot == 0 && u == 0)
		return (int)(ulen + write(1, " ", 1));
	else if (pf->flags.len)
		return (int)(ulen + write(1, expand1, ft_strlen(expand1))
			+ free_deluxe((void **)&expand1));
	else
		return (int)(ulen + write(1, expand1, ft_strlen(expand1))
			+ free_deluxe((void **)&expand1));
}
