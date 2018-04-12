/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifiers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 13:52:11 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/07 13:52:14 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** 1. Parse flags
** 2. Parse width
** 3. Parse length
** 4. Parse prec.
*/

size_t	cut_specifier(const char *format, t_pf *pf)
{
	pf->speclen = specifier_len(format);
	pf->spec = (char *)format;
	pf->type = format[pf->speclen];
	if (!has_conversion_type(format))
		return (pf->speclen - 1);
	else
		return (pf->speclen);
}

size_t	specifier_len(const char *format)
{
	size_t	len;

	len = 0;
	while (*format)
	{
		if (is_valid_type(*format))
			return (len);
		else if (!(is_flag(*format) || is_length(*format)
			|| ft_isdigit(*format)))
			return (len);
		len++;
		format++;
	}
	return (len);
}

void	parse_specifier(t_pf *pf)
{
	parse_flags(pf);
	parse_width(pf);
	parse_prec(pf);
	parse_length(pf);
	parse_implicit_dot(pf);
}

int		map_specifier(t_pf *pf, va_list args)
{
	if (pf->type == 'd' || pf->type == 'D' || pf->type == 'i')
		return (ft_handle_di(pf, args));
	else if (pf->type == 's' || pf->type == 'S')
		return (ft_handle_str(pf, args));
	else if (pf->type == 'o' || pf->type == 'O')
		return (ft_handle_o(pf, args));
	else if (pf->type == 'x' || pf->type == 'X')
		return (int)(ft_handle_x(pf, args));
	else if (pf->type == 'c' || pf->type == 'C')
		return (ft_handle_c(pf, args));
	else if (pf->type == 'Z')
		return (ft_get_exception(pf));
	else if (pf->type == 'u' || pf->type == 'U')
		return (ft_handle_u(pf, args));
	else if (pf->type == 'b')
		return (ft_handle_b(pf, args));
	else if (pf->type == 'p')
		return (ft_handle_p(pf, args));
	else if (pf->type == '%')
		return (ft_handle_percent(pf, args));
	else
		return (ft_handle_unknown(pf, args));
}
