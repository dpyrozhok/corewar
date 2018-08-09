/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 18:51:05 by popanase          #+#    #+#             */
/*   Updated: 2017/11/28 16:10:13 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(f)(t_list *elem))
{
	t_list	**begin_map;
	t_list	*tmp_map;
	t_list	*tmp_f;

	tmp_map = ft_lstnew(0, 0);
	begin_map = &tmp_map->next;
	while (lst)
	{
		tmp_f = f(lst);
		tmp_map->next = ft_lstnew(tmp_f->content, tmp_f->content_size);
		tmp_map = tmp_map->next;
		lst = lst->next;
	}
	return (*begin_map);
}
