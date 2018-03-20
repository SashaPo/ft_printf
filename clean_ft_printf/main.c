/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 18:10:36 by opokusyn          #+#    #+#             */
/*   Updated: 2018/03/09 21:40:53 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include <stdio.h>

int  main(void)
{
	long long int a = -1;
	printf("\nret: %d\n",    printf("%+10.5d", 4242));
	printf("\nret: %d\n", ft_printf("%+10.5d", 4242));
 return (0);
}
