/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 12:39:40 by amalkevy          #+#    #+#             */
/*   Updated: 2018/09/24 12:39:41 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					ft_write_num(char *arg, unsigned int size)
{
	unsigned int	ch;

	ch = (unsigned int)ft_atoi(arg);
	if (size == 2)
	{
		ch = convert_end(ch, 2);
		write(g_fd, &ch, size);
		return (0);
	}
	ch = convert_end(ch, 4);
	write(g_fd, &ch, size);
	return (0);
}

void				ft_write_reg(char *arg)
{
	int				ch;

	ch = ft_atoi(arg);
	write(g_fd, &ch, 1);
}

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

int					ft_pliz_write_to_file(t_my *inf)
{
	char nulek[4];

	ft_bzero(nulek, 4);
	if ((g_fd = open(inf->file_name, O_WRONLY | O_CREAT | O_TRUNC,
S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		ft_printf("error: open\n");
	}
	write(g_fd, &inf->magic_num, sizeof(inf->magic_num));
	write(g_fd, inf->name2, 128);
	write(g_fd, &nulek, 4);
	write(g_fd, &(nulek), 4);
	write(g_fd, inf->comment, 2048);
	write(g_fd, &nulek, 4);
	return (0);
}
