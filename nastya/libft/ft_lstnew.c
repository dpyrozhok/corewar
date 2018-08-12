/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:40:49 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/10 17:41:07 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;
	size_t	size;

	new = (t_list*)malloc(sizeof(t_list));
	if (!new)
		return (0);
	size = content_size;
	if (!content)
	{
		new->content = NULL;
		new->content_size = 0;
		new->next = NULL;
		return (new);
	}
	new->content = malloc(content_size);
	if (!new->content)
	{
		free(new);
		new = NULL;
		return (0);
	}
	ft_memcpy(new->content, (void*)content, size);
	new->content_size = size;
	new->next = NULL;
	return (new);
}
