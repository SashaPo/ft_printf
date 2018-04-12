/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 18:14:35 by opokusyn          #+#    #+#             */
/*   Updated: 2018/03/09 20:29:55 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_pf	*ft_init(t_pf *pf)
{
	pf->flags.hash = 0;
	pf->flags.zero = 0;
	pf->flags.star = 0;
	pf->flags.space = 0;
	pf->flags.minus = 0;
	pf->flags.width = 0;
	pf->flags.plus = 0;
	pf->flags.dot = -1;
	pf->flags.implicit_dot = 0;
	pf->flags.len = none;
	return (pf);
}
