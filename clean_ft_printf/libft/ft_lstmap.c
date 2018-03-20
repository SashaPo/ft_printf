/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:10:56 by opokusyn          #+#    #+#             */
/*   Updated: 2017/11/18 13:10:59 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*begin;
	t_list		*lstnew;
	t_list		*cur;

	if (!lst || !f || !(lstnew = f(lst)))
		return (NULL);
	lst = lst->next;
	begin = lstnew;
	while (lst)
	{
		cur = f(lst);
		lstnew->next = cur;
		lst = lst->next;
		lstnew = lstnew->next;
	}
	return (begin);
}
