/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:23:41 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/07 14:23:43 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool	is_valid_type(char c)
{
	return (t_bool)(c == 'd' || c == 'i' || c == 'o' || c == 'x' || c == 'p'
		|| c == 's' || c == 'O' || c == 'u' || c == 'U' || c == 'D' || c == 'X'
		|| c == 'c' || c == '%' || c == 'S' || c == 'C' || c == 'Z' || c == 'f'
		|| c == 'F' || c == 'b');
}

t_bool	is_length(char c)
{
	return (t_bool)(c == 'l' || c == 'h' || c == 'z' || c == 'j');
}

t_bool	is_flag(char c)
{
	return (t_bool)(c == '.' || c == '-' || c == '+' || c == '0' || c == '#'
		|| c == ' ' || c == '*');
}

t_bool	has_conversion_type(const char *format)
{
	while (*format)
	{
		if (is_valid_type(*format))
			return (TRUE);
		else if (!(is_flag(*format) || is_length(*format)
			|| ft_isdigit(*format)))
			return (TRUE);
		format++;
	}
	return (FALSE);
}
