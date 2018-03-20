/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:09:47 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/18 13:09:51 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *node;

	if (alst && del)
	{
		while (*alst)
		{
			node = (*alst)->next;
			del((*alst)->content, (*alst)->content_size);
			free(*alst);
			*alst = node;
		}
	}
	*alst = NULL;
}
