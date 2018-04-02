/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fF.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 16:58:38 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/01 16:58:43 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	get_fF(t_pf *pf, va_list args)
{
    int lenf = 0;
    int j = 0;
    signed long int decipart;
    signed long int intpart;
    char *expanded = 0;
    double f = va_arg(args, double);
    if (f < 0)
    {
        f *= -1;
        lenf += write(1, "-", 1);
    }
    intpart = (signed long int)f;
    lenf += write(1, ft_itoa_long(intpart), ft_strlen(ft_itoa_long(intpart)));
    lenf += write(1, ".", 1);
    f -= intpart;
    f *= 1000000;
    decipart = (signed long int)(f + 0.5);
    f = intpart + decipart;
    expanded = ft_itoa_long(decipart);
    char *check_sign = ft_itoa(f);
    if ((check_sign[0] == '-' && !pf->flags.plus && pf->flags.dot != -1)
        || (check_sign[0] == '-' && pf->flags.plus && pf->flags.zero))
        lenf += write(1, "-", 1);
    if (pf->spec[j + 1] == '.' && pf->flags.width && f == 0)
    {
        int zero_arg = (int) pf->flags.width;
        while (zero_arg--)
            lenf += write(1, " ", 1);
        return (lenf);
    }
    if (pf->flags.width && pf->flags.width > (lenf + ft_strlen(expanded)))
    {
        int difference = (int) (pf->flags.width - ft_strlen(expanded));
        if (pf->flags.minus)
        {
            if (pf->flags.plus)
                lenf += write(1, "+", 1);
            lenf += write(1, expanded, ft_strlen(expanded));
        }
        if (pf->flags.plus && check_sign[0] != '-')
            difference = difference - 1;
        if (pf->flags.plus && expanded[0] != '-' && pf->flags.dot == -1)
            lenf += write(1, "+", 1);
        if (pf->flags.dot != -1 && expanded[0] != '-')
            pf->flags.zero = 0;
        if (expanded[0] == '-' && !pf->flags.plus && pf->flags.zero)
            lenf += write(1, "-", 1);
        while (difference--)
            lenf += write(1, pf->flags.zero ? "0" : " ", 1);
    }
    if ((f == 0 && pf->flags.dot != -1) || (f == 0 && pf->flags.dot == -1))
    {
        if (pf->spec[j] == '.')
            return (lenf + free_deluxe((void **)&expanded));
    }
    if (expanded[0] == '-' && !pf->flags.plus && pf->flags.zero && !pf->flags.width)
        lenf += write(1, "-", 1);
    if ((pf->flags.plus && expanded[0] != '-' && !pf->flags.width && !pf->flags.minus)
        || (pf->flags.plus && expanded[0] != '-' && pf->flags.dot != -1 && !pf->flags.minus))
        lenf += write(1, "+", 1);
    if (pf->flags.space && !pf->flags.plus && !pf->flags.width)
    {
        if (expanded[0] == '-')
            expanded[0] = '-';
        else
            lenf += write(1, " ", 1);
    }
    if (pf->flags.minus)
        return (lenf + free_deluxe((void **)&expanded) + free_deluxe((void **)&check_sign));
    if ((expanded[0] == '-' && !pf->flags.plus && pf->flags.zero)
        || (check_sign[0] == '-' && pf->flags.plus && pf->flags.zero && pf->flags.width))
        return (int) (lenf + write(1, expanded + 1, ft_strlen(expanded + 1)) + free_deluxe((void **)&expanded) + free_deluxe((void **)&check_sign));
    if (decipart < 6 && pf->flags.dot == -1)
    {
        lenf += write(1, "00000", 5);
        return (int) (lenf + write(1, expanded, ft_strlen(expanded)) + free_deluxe((void **)&expanded) + free_deluxe((void **)&check_sign));
    }
    if (pf->flags.dot != -1)
    {
        int if_dot = pf->flags.dot;
        return (int) (lenf + write(1, expanded, (size_t) if_dot) + free_deluxe((void **)&expanded) + free_deluxe((void **)&check_sign));
    }
    return (int) (lenf + write(1, expanded, ft_strlen(expanded)) + free_deluxe((void **)&expanded) + free_deluxe((void **)&check_sign));
}
