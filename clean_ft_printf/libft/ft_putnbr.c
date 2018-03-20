/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:15:41 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/14 18:25:12 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putnbr(-214748);
		ft_putnbr(3648);
	}
	else
	{
		if (n < 0)
		{
			ft_putchar('-');
			n = n * (-1);
		}
		if (n >= 0 && n <= 9)
			ft_putchar(n + '0');
		else
		{
			ft_putnbr(n / 10);
			ft_putchar((n % 10) + '0');
		}
	}
}
