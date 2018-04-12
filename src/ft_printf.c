/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:54:57 by opokusyn          #+#    #+#             */
/*   Updated: 2018/03/09 21:34:58 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		free_deluxe(void **ad)
{
	free(*ad);
	return (0);
}

int		ft_format_check(const char *format, va_list args, t_pf *spec, int res)
{
	int		len;
	size_t	ret;

	while (*format)
	{
		len = 0;
		if (*format && *format == '%')
		{
			if (*format && !*(format + 1))
				return (res);
			if (*format && *(format + 1) != '\0')
				format++;
			ret = cut_specifier(format, spec);
			parse_specifier(spec);
			res += map_specifier(spec, args);
			format += ret + 1;
		}
		while ((*format && *format != '%'))
		{
			len++;
			format++;
		}
		len ? res += write(1, format - len, len) : res;
	}
	return (res);
}

int		ft_printf(const char *format, ...)
{
	va_list	args;
	t_pf	*spec;
	int		res;

	res = 0;
	va_start(args, format);
	spec = malloc(sizeof(t_pf));
	ft_init(spec);
	res = ft_format_check(format, args, spec, res);
	ft_memdel((void **)&spec);
	va_end(args);
	return (res);
}
