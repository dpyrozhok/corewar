/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 12:38:04 by amalkevy          #+#    #+#             */
/*   Updated: 2018/09/24 12:38:06 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void					ft_free_command(t_my *inf)
{
	t_comm				*p_c;
	int					i;

	while (inf->command_s)
	{
		p_c = inf->command_s;
		inf->command_s = inf->command_s->next;
		i = 0;
		while (i < 3 && p_c->arg[i])
			free(p_c->arg[i++]);
		free(p_c->name);
		free(p_c);
	}
}

void					ft_free_label(t_my *inf)
{
	t_use_label			*p_use_l;

	while (inf->use_label)
	{
		p_use_l = inf->use_label;
		inf->use_label = inf->use_label->next;
		free(p_use_l->label);
		free(p_use_l);
	}
}

void					ft_free(t_my *inf)
{
	t_label				*p_l;
	t_text				*p_t;

	while (inf->head)
	{
		p_t = inf->head;
		inf->head = inf->head->next;
		free(p_t->line);
		free(p_t);
	}
	while (inf->label_s)
	{
		p_l = inf->label_s;
		inf->label_s = inf->label_s->next;
		free(p_l->name);
		free(p_l);
	}
	if (inf->command_s)
		ft_free_command(inf);
	if (inf->use_label)
		ft_free_label(inf);
	free(inf->name2);
	free(inf->comment);
	free(inf->file_name);
}
