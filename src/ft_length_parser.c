/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_length_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:26:19 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/07 14:26:22 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_length			ft_handle_pref(t_pf *pf, size_t i)
{
	if (pf->spec[i] == 'l')
		pf->flags.len = l;
	else
		pf->flags.len = hh;
	return (pf->flags.len);
}

void				parse_length(t_pf *pf)
{
	size_t				i;

	i = 0;
	while (i < pf->speclen)
	{
		if ((pf->spec[i] == 'h' && pf->spec[i + 1] == 'h')
			|| pf->spec[i] == 'l')
			pf->flags.len = ft_handle_pref(pf, i++);
		else if (pf->spec[i] == 'h' && h > pf->flags.len)
			pf->flags.len = h;
		else if (pf->spec[i] == 'l' && pf->spec[i + 1] == 'l'
			&& l > pf->flags.len)
			pf->flags.len = ll;
		else if (pf->spec[i] == 'l' && pf->flags.len == none
			&& ll > pf->flags.len)
			pf->flags.len = l;
		else if (pf->spec[i] == 't' && t > pf->flags.len)
			pf->flags.len = t;
		else if (pf->spec[i] == 'j' && j > pf->flags.len)
			pf->flags.len = j;
		else if (pf->spec[i] == 'z' && z > pf->flags.len)
			pf->flags.len = z;
		i++;
	}
}

long long			fetch_signed_arg(t_pf *pf, va_list args)
{
	long long			res;

	res = 0;
	if (pf->flags.len == none)
		res = va_arg(args, int);
	else if (pf->flags.len == h)
		res = (short)va_arg(args, int);
	else if (pf->flags.len == t)
		res = (ptrdiff_t)va_arg(args, ptrdiff_t);
	else if (pf->flags.len == l)
		res = va_arg(args, long);
	else if (pf->flags.len == j)
		res = (intmax_t)va_arg(args, intmax_t);
	else if (pf->flags.len == z)
		res = (long long)va_arg(args, size_t);
	else if (pf->flags.len == ll)
		res = va_arg(args, long long);
	else if (pf->flags.len == hh)
		res = (signed char)va_arg(args, int);
	return (res);
}

unsigned long long	fetch_unsigned_arg(t_pf *pf, va_list args)
{
	unsigned long long	unres;

	if (pf->flags.len == h)
		unres = (unsigned short)va_arg(args, unsigned int);
	else if (pf->flags.len == t)
		unres = (unsigned long long int)va_arg(args, ptrdiff_t);
	else if (pf->flags.len == l)
		unres = va_arg(args, unsigned long);
	else if (pf->flags.len == j)
		unres = (uintmax_t)va_arg(args, uintmax_t);
	else if (pf->flags.len == z)
		unres = (size_t)va_arg(args, size_t);
	else if (pf->flags.len == ll)
		unres = va_arg(args, unsigned long long);
	else if (pf->flags.len == hh)
		unres = (unsigned char)va_arg(args, int);
	else
		unres = (unsigned long long)va_arg(args, unsigned int);
	return (unres);
}
