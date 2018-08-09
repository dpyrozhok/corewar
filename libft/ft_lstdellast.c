/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdellast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 16:33:28 by popanase          #+#    #+#             */
/*   Updated: 2017/12/07 16:50:12 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdellast(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*cur;
	t_list	*tmp;

	if (alst)
	{
		cur = *alst;
		while (cur->next)
		{
			tmp = cur;
			cur = cur->next;
		}
		tmp->next = NULL;
		ft_lstdelone(&cur, del);
	}
}
