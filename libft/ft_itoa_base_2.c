/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 12:48:24 by opokusyn          #+#    #+#             */
/*   Updated: 2018/03/06 12:48:44 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define ABS(v) ((v) < 0 ? -(v) : (v))

void	aux_2(int n, int b, char *ans, int *p)
{
	char	*base;
	int		i;

	i = 0;
	base = "0123456789abcdef";
	if (n <= -b || b <= n)
		aux_2(n / b, b, ans, p);
	base[i] = ABS(n % b);
	ans[(*p)++] = base[i];
}

char	*ft_itoa_base_2(int value, int base)
{
	char	*ans;
	int		p;

	if (base < 2 || 16 < base
		|| !(ans = (char *)malloc(sizeof(char) * 35)))
		return (NULL);
	p = 0;
	if (base == 10 && value < 0)
		ans[p++] = '-';
	aux_2(value, base, ans, &p);
	ans[p] = '\0';
	return (ans);
}
