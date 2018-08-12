/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:06:36 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/10 18:06:39 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*nw;

	if (!lst || f == NULL)
		return (0);
	new = (*f)(lst);
	nw = new;
	lst = lst->next;
	while (lst)
	{
		nw->next = f(lst);
		nw = nw->next;
		lst = lst->next;
	}
	return (new);
}
