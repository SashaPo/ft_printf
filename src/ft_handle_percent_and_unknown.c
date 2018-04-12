/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_percent_and_unknown.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:44:11 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/07 14:44:13 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_handle_percent(t_pf *pf, va_list args)
{
	int		plen;
	int		diff;

	plen = 0;
	(void)args;
	if (pf->flags.width > 1)
	{
		diff = (int)(pf->flags.width - 1);
		if (pf->flags.minus)
			plen += write(1, "%", 1);
		while (diff--)
			plen += write(1, pf->flags.zero ? "0" : " ", 1);
	}
	if (pf->flags.minus)
		return (plen);
	else
		return (int)(plen + write(1, "%", 1));
}

int		ft_handle_unknown(t_pf *pf, va_list args)
{
	int		unknownlen;
	char	wtf;
	int		di;

	(void)args;
	unknownlen = 0;
	wtf = pf->type;
	if (pf->flags.width > 1 && wtf)
	{
		di = (int)(pf->flags.width - 1);
		while (di--)
			unknownlen += write(1, pf->flags.zero ? "0" : " ", 1);
	}
	if (wtf)
		return (int)(unknownlen + write(1, &wtf, 1));
	else
		return (0);
}

int		ft_get_exception(t_pf *pf)
{
	int		len1;
	char	ch;
	size_t	dr;

	len1 = 0;
	ch = 'Z';
	if (pf->flags.len)
		ch = 'Z';
	if (pf->flags.width > 1)
	{
		dr = pf->flags.width - 1;
		if (pf->flags.minus)
			len1 += ft_putchar(ch);
		while (dr--)
			len1 += write(1, pf->flags.zero ? "0" : " ", 1);
	}
	if (pf->flags.minus)
		return (len1);
	else
		return (len1 + ft_putchar(ch));
}

char	*ft_handle_unistr(unsigned int nbrs)
{
	char	*res;
	char	*tmp;

	if (!nbrs)
		return (ft_strdup("(null)"));
	tmp = ft_unicode(nbrs);
	res = tmp;
	return (res);
}

size_t	ft_exception_case(char *exp, size_t lenp)
{
	lenp += write(1, "0x", 2);
	lenp += write(1, exp, ft_strlen(exp));
	return (int)(lenp);
}
