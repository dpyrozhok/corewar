/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 12:39:50 by amalkevy          #+#    #+#             */
/*   Updated: 2018/09/24 12:39:51 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					ft_empty_label(t_my *inf, char *ssilka)
{
	t_label *all;

	all = inf->label_s;
	while (all != NULL)
	{
		if (ft_strcmp(all->name, ssilka) == 0)
			return (all->cidr);
		all = all->next;
	}
	return (-1);
}

int					ft_find_label(t_comm *all, char *ssilka, t_my *inf)
{
	while (all->label == NULL)
		all = all->next;
	while (all != NULL)
	{
		if (ft_strcmp(all->label->name, ssilka) == 0)
			return (all->cidr);
		all = all->next;
	}
	return (ft_empty_label(inf, ssilka));
}

int					from_ssylk_to_command(int do_ssylk,
	int do_comm, t_comm *all)
{
	int				first;
	int				last;
	int				znak;
	int				size;

	size = 0;
	znak = (do_ssylk > do_comm) ? 1 : -1;
	first = (do_ssylk < do_comm) ? do_ssylk : do_comm;
	last = (do_ssylk > do_comm) ? do_ssylk : do_comm;
	while (all != NULL)
	{
		if (all->cidr == first)
		{
			while (all && all->cidr != last)
			{
				size += all->size;
				all = all->next;
			}
			return (size * znak);
		}
		all = all->next;
	}
	return (-1);
}

int					ft_write_label(t_my *inf, char *ssilka,
	t_comm *this_command, int size_byte)
{
	unsigned int	ch;
	int				do_ssylk;
	int				do_comm;
	t_comm			*all;

	all = inf->command_s;
	do_ssylk = ft_find_label(all, ssilka + 1, inf);
	do_comm = this_command->cidr;
	ch = (unsigned)from_ssylk_to_command(do_ssylk, do_comm, all);
	if (size_byte == 2)
		ch = convert_end(ch, 2);
	else
		ch = convert_end(ch, 4);
	write(g_fd, &ch, (size_t)size_byte);
	return (0);
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
