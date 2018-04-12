/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:44:27 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/10 17:44:29 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_sres(t_pf *pf, char *count, int slen, size_t strlen)
{
	if (*count == '\0')
		return (pf->flags.width ? pf->flags.width : 0);
	else if (pf->flags.minus && pf->flags.width)
	{
		if (pf->flags.dot == -1)
			return (slen);
		return (slen + write(1, count, strlen - pf->flags.dot));
	}
	else if (pf->flags.dot == -1)
	{
		if (pf->flags.implicit_dot)
		{
			while (pf->flags.width - ft_strlen(count))
			{
				slen += write(1, pf->flags.zero ? "0" : " ", 1);
				pf->flags.width--;
			}
			return (slen);
		}
		return (slen + write(1, count, strlen));
	}
	else
		return (slen + write(1, count, strlen));
}

int		ft_complete_res(t_pf *pf, char *count, int slen, size_t strlen)
{
	if (pf->flags.implicit_dot && !count)
	{
		if (pf->flags.width)
			return (int)(ft_ifwidth(pf, strlen));
		return (int)(strlen);
	}
	if (!count)
		return (int)(slen + write(1, "(null)", 6));
	strlen = ft_strlen(count);
	if (pf->flags.dot != -1 && pf->flags.dot < (int)strlen)
		strlen = (size_t)pf->flags.dot;
	if (pf->flags.width && pf->flags.width > strlen)
		slen = ft_ifdiffer(pf, count, slen, strlen);
	return (ft_sres(pf, count, slen, strlen));
}

int		ft_whole_work1(t_pf *pf, char *count, int slen, unsigned int *str)
{
	int				onelen;
	size_t			strlen;

	strlen = 0;
	if (!str)
		return (int)(slen + write(1, "(null)", 6));
	count = ft_uni_code(count, str);
	onelen = ft_uni_code1(str);
	strlen = ft_strch(pf, count, onelen, strlen);
	if (pf->flags.implicit_dot && pf->flags.width)
	{
		if ((int)pf->flags.width != onelen)
		{
			strlen = 0;
			return (int)(ft_ifwidth(pf, strlen));
		}
		else
			strlen = pf->flags.width;
	}
	if (pf->flags.width && pf->flags.width > strlen)
		slen = ft_ifdiffer(pf, count, slen, strlen);
	if (pf->flags.minus)
		return (slen);
	return (int)(slen + write(1, count, strlen) + f((void **)&count));
}

int		ft_whole_work(t_pf *pf, char *count, int slen)
{
	size_t			strlen;

	strlen = 0;
	return (ft_complete_res(pf, count, slen, strlen));
}

int		ft_handle_str(t_pf *pf, va_list args)
{
	int				slen;
	char			*count;
	unsigned int	(*str);

	slen = 0;
	count = 0;
	if (pf->type == 's' && !pf->flags.len)
		count = va_arg(args, char *);
	else if (pf->type == 'S' || pf->flags.len)
	{
		str = va_arg(args, unsigned int *);
		return (ft_whole_work1(pf, count, slen, str));
	}
	return (ft_whole_work(pf, count, slen));
}
