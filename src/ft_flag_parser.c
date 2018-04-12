/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 13:17:28 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/03 13:17:31 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_flags(t_pf *pf)
{
	size_t	i;

	i = 0;
	while (i < pf->speclen)
	{
		if (pf->spec[i] == '*')
			pf->flags.star = TRUE;
		if (pf->spec[i] == '-')
			pf->flags.minus = TRUE;
		if (pf->spec[i] == '#')
			pf->flags.hash = TRUE;
		if ((pf->spec[i] == '0'
			&& (i - 1 > 0 && !((pf->spec[i - 1] >= '0'
			&& pf->spec[i - 1] <= '9') || pf->spec[i - 1] == '.')))
			|| (pf->spec[i] == '0' && pf->flags.hash))
			pf->flags.zero = TRUE;
		if (pf->spec[i] == '+')
			pf->flags.plus = TRUE;
		if (pf->spec[i] == ' ')
			pf->flags.space = TRUE;
		i++;
	}
}

size_t	ft_check_dot(t_pf *pf, size_t i)
{
	while (i + 1)
	{
		if (ft_isdigit(pf->spec[i + 1]))
			i++;
		else
		{
			i++;
			break ;
		}
	}
	return (i);
}

void	parse_width(t_pf *pf)
{
	size_t	i;
	int		width;

	i = 0;
	width = 0;
	while (i < pf->speclen)
	{
		if (pf->spec[i] == '.')
			i = ft_check_dot(pf, i);
		else if (pf->spec[i] >= '0' && pf->spec[i] <= '9' && width == 0)
			while (i < pf->speclen && ft_isdigit(pf->spec[i]))
				width = width * 10 + (pf->spec[i++] - '0');
		else if (ft_isdigit(i) && !pf->flags.zero && pf->spec[i - 1] != '.')
		{
			width = 0;
			while (i < pf->speclen && ft_isdigit(pf->spec[i]))
				width = width * 10 + (pf->spec[i++] - '0');
		}
		else
			i++;
	}
	pf->flags.width = (size_t)width;
}

void	parse_prec(t_pf *pf)
{
	int		dot;
	size_t	i;

	dot = -1;
	i = 0;
	while (i < pf->speclen)
	{
		if (i > 0 && pf->spec[i - 1] == '.')
		{
			dot = 0;
			while (pf->spec[i] && pf->spec[i] >= '0' && pf->spec[i] <= '9')
				dot = dot * 10 + (pf->spec[i++] - '0');
		}
		i++;
		pf->flags.dot = TRUE;
	}
	pf->flags.dot = dot;
}

void	parse_implicit_dot(t_pf *pf)
{
	int		idot;
	size_t	i;

	idot = 0;
	i = 0;
	while (i < pf->speclen)
	{
		if ((i > 0 || i == 0) && pf->spec[i] == '.'
			&& !ft_isdigit(pf->spec[i + 1]))
			idot = 1;
		i++;
		pf->flags.implicit_dot = TRUE;
	}
	pf->flags.implicit_dot = idot;
}
