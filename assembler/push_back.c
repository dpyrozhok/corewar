/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 12:39:23 by amalkevy          #+#    #+#             */
/*   Updated: 2018/09/24 12:39:24 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				ft_push_u_front(t_use_label **begin_list,
	t_use_label *elem)
{
	if (!*begin_list)
		elem->next = NULL;
	else
		elem->next = *begin_list;
	*begin_list = elem;
}

void				ft_push_l_back(t_my *my, t_label *new)
{
	t_label			*p_l;

	p_l = my->label_s;
	if (my->label_e)
		my->label_e->next = new;
	else
	{
		while (p_l && p_l->next)
		{
			p_l = p_l->next;
		}
		if (p_l)
			p_l->next = new;
		else
			my->label_s = new;
	}
	my->label_e = new;
}

void				ft_push_t_back(t_my *my, t_text *new, int i)
{
	t_text			*p_t;

	p_t = my->head;
	if (!p_t)
	{
		my->head = new;
		return ;
	}
	new->i = i;
	while (p_t->next)
	{
		p_t = p_t->next;
	}
	if (p_t->line)
		p_t->next = new;
	else
		my->head = new;
}

void				ft_push_c_back(t_my *my, t_comm *new)
{
	t_comm			*p_c;

	p_c = my->command_s;
	if (my->command_e)
		my->command_e->next = new;
	else
	{
		while (p_c && p_c->next)
		{
			p_c = p_c->next;
		}
		if (p_c)
			p_c->next = new;
		else
			my->command_s = new;
	}
	my->command_e = new;
}
