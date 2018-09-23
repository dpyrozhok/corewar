/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 13:13:07 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/09/23 21:18:25 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void						ft_push_l_back(t_my *my, t_label *new)
{
	t_label					*p_l;

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

int							ft_label(char *name, t_my *inf)
{
	t_label					*new;
	int						i;

	ft_go_space(inf->head->line, &inf->x);
	i = inf->x;
	new = (t_label*)malloc(sizeof(t_label));
	if (inf->command_e)
		new->cidr = inf->command_e->cidr + 1;
	else
		new->cidr = 1;
	new->next = NULL;
	new->size = -1;
	while (name[i++] && name[i] != LABEL_CHAR)
		;
	new->name = (char*)malloc(sizeof(char) * (i - inf->x + 1));
	i = 0;
	while (name[inf->x] && name[inf->x] != LABEL_CHAR)
		new->name[i++] = name[inf->x++];
	inf->x++;
	new->name[i] = '\0';
	ft_push_l_back(inf, new);
	return (1);
}

void						ft_push_c_back(t_my *my, t_comm *new)
{
	t_comm					*p_c;

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

void						ft_command(int j, t_my *inf)
{
	t_comm					*new;

	new = (t_comm*)malloc(sizeof(t_comm));
	new->name = ft_strdup(OP(j).op);
	new->next = NULL;
	new->label = inf->label_e;
	new->arg[0] = NULL;
	new->arg[1] = NULL;
	new->arg[2] = NULL;
	new->arg_id[0] = 0;
	new->arg_id[1] = 0;
	new->arg_id[2] = 0;
	new->size = 1;
	new->t_dir_size = 0;
	new->codage = 0;
	if (inf->command_s)
		new->cidr = inf->command_e->cidr + 1;
	else
		new->cidr = 1;
	ft_push_c_back(inf, new);
}

unsigned int				size_dira(int j)
{
	if ((j >= 0 && j <= 7) || j == 12 || j == 15)
		return (4);
	else
		return (2);
}
