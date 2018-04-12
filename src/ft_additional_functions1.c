/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional_functions1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:06:50 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/10 15:07:02 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_two_cased(t_pf *pf)
{
	int			j;

	j = 0;
	while (pf->spec[j])
	{
		if (pf->spec[j] != '0')
			j++;
		else
		{
			pf->flags.zero = 1;
			return (1);
		}
	}
	return (0);
}

int			ft_first_diff(t_pf *pf, int len, char *expanded)
{
	int			difference;

	if (pf->flags.width > ft_strlen(expanded))
	{
		difference = (int)(pf->flags.width - ft_strlen(expanded));
		if (expanded[0] == '-' && !pf->flags.plus && pf->flags.dot != -1)
		{
			len = 0;
			while (difference--)
				len += write(1, pf->flags.zero ? "0" : " ", 1);
		}
	}
	return (len);
}

int			ft_s_dif(t_pf *pf, int len, char *expanded, int difference)
{
	difference = difference - 1;
	len = 0;
	while (difference--)
		len += write(1, pf->flags.zero ? "0" : " ", 1);
	len += write(1, "-", 1);
	return (int)(len + write(1, expanded, ft_strlen(expanded)));
}

int			ft_test(t_pf *pf, int len, char *expanded)
{
	if ((pf->flags.plus && expanded[0] != '-'
		&& !pf->flags.width && !pf->flags.minus)
		|| (pf->flags.plus && expanded[0] != '-'
			&& pf->flags.dot != -1 && !pf->flags.minus))
		len += write(1, "+", 1);
	if ((pf->flags.space && !pf->flags.plus && !pf->flags.width)
		|| (pf->flags.space && !pf->flags.plus && pf->flags.width
			&& pf->flags.dot != -1
			&& (pf->flags.width < (size_t)pf->flags.dot)))
	{
		if (expanded[0] == '-')
			expanded[0] = '-';
		else
			len += write(1, " ", 1);
	}
	return (len);
}

int			ft_zero_arg(t_pf *pf, int len)
{
	int			zero_arg;

	zero_arg = (int)pf->flags.width;
	while (zero_arg--)
		len += write(1, " ", 1);
	return (len);
}
