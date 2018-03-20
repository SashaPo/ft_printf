/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 19:01:44 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/20 19:01:47 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lst_size(t_list *begin_list)
{
	int		i;
	t_list	*head;

	i = 0;
	head = begin_list;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}
