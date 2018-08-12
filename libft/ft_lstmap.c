/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:01:53 by dpyrozho          #+#    #+#             */
/*   Updated: 2017/11/22 19:01:54 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *newl;
	t_list *copy;

	if (!lst || !f)
		return (NULL);
	newl = f(lst);
	if (!newl)
		return (NULL);
	lst = lst->next;
	copy = newl;
	while (lst)
	{
		copy->next = f(lst);
		copy = copy->next;
		lst = lst->next;
	}
	return (newl);
}
