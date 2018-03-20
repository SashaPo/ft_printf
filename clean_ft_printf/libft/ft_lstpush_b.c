/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 15:25:45 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/20 15:25:55 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush_b(t_list **begin, t_list *new)
{
	t_list *head;

	head = *begin;
	if (head)
	{
		while (head->next)
			head = head->next;
		head->next = new;
	}
	else
		*begin = new;
}
