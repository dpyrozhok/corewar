/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 13:13:07 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/08/09 13:13:09 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					g_fd;

void				arguements_to_file(t_my *inf, t_comm *this_command)
{
	int				i;

	i = 0;
	while (i < 3 && this_command->arg[i])
	{
		if (this_command->arg_id[i] == 1)
			ft_write_reg(this_command->arg[i]);
		if (this_command->arg_id[i] == 2 && this_command->arg[i][0] == ':')
			AG1;
		if (this_command->arg_id[i] == 3 && this_command->arg[i][0] == ':')
			ft_write_label(inf, this_command->arg[i], this_command, 2);
		if (this_command->arg_id[i] == 2 && this_command->arg[i][0] != ':')
			ft_write_num(this_command->arg[i], this_command->t_dir_size);
		if (this_command->arg_id[i] == 3 && this_command->arg[i][0] != ':')
			ft_write_num(this_command->arg[i], 2);
		i++;
	}
}

void				ft_write_commands(t_my *inf, int i, int codage)
{
	t_comm			*start;
	int				change_comm_id;

	start = inf->command_s;
	while (start != NULL)
	{
		change_comm_id = start->comm_id + 1;
		write(g_fd, &change_comm_id, 1);
		if (start->codage)
		{
			while (i < 3)
			{
				codage = codage | start->arg_id[i];
				codage = codage << 2;
				i++;
			}
			write(g_fd, &codage, 1);
		}
		arguements_to_file(inf, start);
		start = start->next;
		codage = 0;
		i = 0;
	}
}

t_use_label			*ft_check_correct_labels(t_my *inf)
{
	t_label			*all;
	t_use_label		*to_check;

	all = inf->label_s;
	to_check = inf->use_label;
	while (to_check != NULL)
	{
		while (all != NULL)
		{
			if (ft_strcmp(all->name, to_check->label + 1) == 0)
				break ;
			else
				all = all->next;
		}
		if (all == NULL)
			return (to_check);
		else
			to_check = to_check->next;
		all = inf->label_s;
	}
	return (NULL);
}

void				ft_write_botsize(t_my *inf)
{
	t_comm			*all;

	all = inf->command_s;
	while (all != NULL)
	{
		inf->botsize += all->size;
		all = all->next;
	}
	lseek(g_fd, 136, SEEK_SET);
	inf->botsize = convert_end(inf->botsize, 4);
	write(g_fd, &inf->botsize, 4);
}

void				ft_read_all(t_my *inf)
{
	t_text			*new_t;
	int				i;

	i = 1;
	new_t = (t_text *)malloc(sizeof(t_text));
	new_t->next = NULL;
	while (ft_gnl_without_com(inf->fd, &(new_t->line)) > 0)
	{
		ft_push_t_back(inf, new_t, i++);
		new_t = (t_text *)malloc(sizeof(t_text));
		new_t->next = NULL;
	}
	free(new_t->line);
	free(new_t);
	ft_print_txt(inf->head);
}
