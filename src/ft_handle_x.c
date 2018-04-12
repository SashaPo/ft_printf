/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:37:44 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/07 14:37:46 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_lenx(t_pf *pf, size_t blen, char *uiter)
{
	size_t				d;
	int					len;

	len = 0;
	d = 0;
	if (pf->flags.dot != -1 && pf->flags.dot > (int)blen)
	{
		(pf->flags.dot > (int)pf->flags.width) ? (pf->flags.zero = 1)
		: (d = pf->flags.width - (size_t)pf->flags.dot);
	}
	else
		d = pf->flags.width - blen;
	if (pf->flags.hash)
	{
		d = d - 2;
		if (pf->flags.zero)
			len += pf->type == 'X' ? write(1, "0X", 2) : write(1, "0x", 2);
	}
	if (pf->flags.zero && pf->flags.hash && pf->flags.minus)
		pf->flags.zero = 0;
	if (pf->flags.minus)
		len += write(1, uiter, blen);
	while (d--)
		len += write(1, pf->flags.zero ? "0" : " ", 1);
	return (len);
}

int		little_case(t_pf *pf)
{
	int					wtf;
	int					len;

	len = 0;
	wtf = (int)pf->flags.width;
	while (wtf--)
		len += write(1, " ", 1);
	return (len);
}

int		ft_handle_case(t_pf *pf, size_t big_x_len, int lenx)
{
	if (pf->flags.hash
		|| (pf->flags.dot != -1 && pf->flags.dot > (int)big_x_len))
		pf->flags.zero = 1;
	while (pf->flags.dot - big_x_len != 0)
	{
		lenx += write(1, pf->flags.zero ? "0" : " ", 1);
		pf->flags.dot--;
	}
	return (lenx);
}

int		ft_result(t_pf *pf, char *uiter, int lenx, unsigned long long it)
{
	int				b;

	b = (int)ft_strlen(uiter);
	if (pf->flags.minus)
		return (lenx);
	else if (pf->flags.dot != -1)
	{
		if ((pf->flags.dot > b && !pf->flags.width)
			|| (pf->flags.dot > b && pf->flags.width
				&& (pf->flags.width > (size_t)pf->flags.dot)))
			pf->flags.zero = 1;
		if (pf->flags.dot > b)
		{
			lenx = ft_handle_case(pf, (size_t)b, lenx);
			return (int)(lenx + write(1, uiter, ft_strlen(uiter)));
		}
		return (int)(lenx + write(1, uiter, ft_strlen(uiter)));
	}
	else if (pf->flags.len)
	{
		if (pf->flags.hash && it != '0')
			lenx += pf->type == 'X' ? write(1, "0X", 2) : 0;
		return (int)(lenx + write(1, uiter, ft_strlen(uiter)));
	}
	return (int)(lenx + write(1, uiter, (size_t)b));
}

ssize_t	ft_handle_x(t_pf *pf, va_list args)
{
	ssize_t				lenx;
	size_t				blen;
	unsigned long long	it;
	char				*uiter;

	lenx = 0;
	it = fetch_unsigned_arg(pf, args);
	uiter = itoa_u(it, 16, pf->type);
	blen = ft_strlen(uiter);
	if (pf->flags.dot == 0 && it == 0 && !pf->flags.width)
		return (lenx);
	if ((pf->flags.dot == -1 && it == 0) || (pf->flags.dot != -1 && it == 0))
	{
		if (pf->spec[0] == '.' || (pf->spec[1] == '.' && !pf->flags.width))
			return (lenx);
		if (pf->flags.width && pf->spec[1] == '.')
			return (little_case(pf));
	}
	lenx = (pf->flags.width > blen) ? ft_lenx(pf, blen, uiter) : lenx;
	if (!pf->flags.zero && pf->flags.hash && pf->flags.minus)
		pf->flags.zero = 1;
	if ((pf->flags.hash && it != 0 && !pf->flags.width)
		|| (pf->flags.hash && it != 0 && !pf->flags.zero))
		lenx += pf->type == 'X' ? write(1, "0X", 2) : write(1, "0x", 2);
	return (ft_result(pf, uiter, lenx, it) + free_deluxe((void **)&uiter));
}
