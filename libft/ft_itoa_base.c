/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 18:26:32 by opokusyn          #+#    #+#             */
/*   Updated: 2018/03/04 18:26:35 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define ABS(v) ((v) < 0 ? -(v) : (v))

void	aux(int n, int b, char *ans, int *p)
{
	char	*base;
	int		i;

	i = 0;
	base = "0123456789ABCDEF";
	if (n <= -b || b <= n)
		aux(n / b, b, ans, p);
	base[i] = ABS(n % b);
	ans[(*p)++] = base[i];
}

char	*ft_itoa_base(int value, int base)
{
	char	*ans;
	int		p;

	if (base < 2 || 16 < base
		|| !(ans = (char *)malloc(sizeof(char) * 35)))
		return (NULL);
	p = 0;
	if (base == 10 && value < 0)
		ans[p++] = '-';
	aux(value, base, ans, &p);
	ans[p] = '\0';
	return (ans);
}
