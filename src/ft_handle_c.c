/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 18:44:11 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/01 18:44:15 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_one_char(t_pf *pf, va_list args)
{
	char	ch;
	int		len1;
	size_t	d;

	len1 = 0;
	ch = (char)va_arg(args, int);
	if (pf->flags.width > 1)
	{
		d = pf->flags.width - 1;
		if (pf->flags.minus)
			len1 += ft_putchar(ch);
		while (d--)
			len1 += write(1, pf->flags.zero ? "0" : " ", 1);
	}
	if (pf->flags.minus)
		return (len1);
	else
		return (len1 + ft_putchar(ch));
}

int		ft_case(t_pf *pf, char *str)
{
	size_t	dr;
	int		len;

	len = 0;
	dr = pf->flags.width - 1;
	len += pf->flags.minus ? write(1, str, ft_strlen(str)) : 0;
	while (dr--)
		len += write(1, pf->flags.zero ? "0" : " ", 1);
	return (len);
}

int		ft_handle_c(t_pf *pf, va_list args)
{
	int		len1;
	char	*str;
	int		uni;

	len1 = 0;
	if (pf->type == 'C' || pf->flags.len)
	{
		uni = va_arg(args, unsigned int);
		if (!uni)
			return (len1 + ft_putchar(uni));
		if (MB_CUR_MAX == 1)
			return (len1 + ft_putchar(uni));
		str = ft_unicode(uni);
		if (pf->flags.width > 1)
			len1 = (ft_case(pf, str));
		if (pf->flags.minus)
			return (len1);
		else
			return (int)(len1 + write(1, str, ft_strlen(str))
				+ free_deluxe((void **)&str));
	}
	else
		return (ft_one_char(pf, args));
}
