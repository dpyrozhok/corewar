/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 13:13:07 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/09/23 21:18:39 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int						codage(int j)
{
	return ((j == 0 || j == 8 || j == 11 || j == 14) ? 0 : 1);
}

void					ft_eror_code_n2(void *le, t_my *inf)
{
	le = NULL;
	ft_free(inf);
	exit(1);
}

int						ft_gogogogo(t_my *inf, t_text **p_t)
{
	*p_t = inf->head;
	inf->head = inf->head->next;
	free((*p_t)->line);
	free(*p_t);
	inf->y++;
	return (1);
}

void					ft_help_read_body1(t_my *inf, int j)
{
	inf->command_e->comm_id = (char)j;
	inf->command_e->t_dir_size = size_dira(j);
	inf->command_e->codage = (char)codage(j);
	inf->command_e->size += (int)inf->command_e->codage;
}

int						ft_find_command(t_my *inf, char *command_name)
{
	int					j;

	j = 0;
	while (j < 16)
	{
		if (ft_strcmp(command_name, OP(j).op) == 0)
		{
			ft_command(j, inf);
			break ;
		}
		j++;
	}
	if (j >= 16)
	{
		LE7;
		ft_eror_code_n2(0, inf);
	}
	return (j);
}
