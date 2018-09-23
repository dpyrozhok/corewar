/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 13:13:07 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/09/23 21:17:57 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int							ft_dir(const char *line,
	t_my *inf, int is_end)
{
	unsigned int			m;
	int						arg_i;

	arg_i = 0;
	if (line[inf->x] != '%')
		return (0);
	m = inf->x;
	m++;
	while (inf->command_e->arg[arg_i] != NULL)
		arg_i++;
	inf->command_e->arg_id[arg_i] = 2;
	inf->command_e->size += inf->command_e->t_dir_size;
	if (line[m] == ':')
		return (ft_lable(inf, arg_i));
	else
		return (ft_num(inf, arg_i, m, is_end));
}

int							ft_ind(const char *line, t_my *inf, int is_end)
{
	unsigned int			m;
	int						arg_i;

	m = inf->x;
	arg_i = 0;
	while (inf->command_e->arg[arg_i] != NULL)
		arg_i++;
	inf->command_e->arg_id[arg_i] = 3;
	inf->command_e->size += 2;
	if (line[m] == ':')
		return (ft_lable(inf, arg_i));
	else
		return (ft_num(inf, arg_i, m, is_end));
}

int							ft_reg(const char *line, t_my *inf, int is_end)
{
	unsigned int			m;
	int						z;
	int						arg_i;

	arg_i = 0;
	if (line[inf->x] == 'r')
	{
		while (inf->command_e->arg[arg_i] != NULL)
			arg_i++;
		inf->command_e->arg_id[arg_i] = 1;
		inf->command_e->size += 1;
		m = inf->x;
		m++;
		if (line[m] >= '0' && line[m] <= '9' &&
			((z = ft_atoi(line + inf->x + 1)) < 100) && z >= 0)
			return (ft_num(inf, arg_i, m, is_end));
		else
			return (0);
	}
	else
		return (0);
}

int							ft_check_args(t_my *inf, char *line,
	int num_command)
{
	int						z;
	int						i;

	i = 0;
	ft_go_space(inf->head->line, &(inf->x));
	while (i < 3 && (z = OP(num_command).arg[i]) != 0)
	{
		i++;
		ft_go_space(line, &(inf->x));
		if ((z == 1 || z == 3 || z == 5 || z == 7) &&
(ft_reg(line, inf, (i == 3) ? 0 : OP(num_command).arg[i])))
			continue;
		if ((z == 2 || z == 3 || z == 6 || z == 7) &&
(ft_dir(line, inf, (i == 3) ? 0 : OP(num_command).arg[i])))
			continue;
		if ((z == 4 || z == 5 || z == 6 || z == 7) &&
(ft_ind(line, inf, (i == 3) ? 0 : OP(num_command).arg[i])))
			continue;
		else
			return (0);
	}
	return (1);
}

int							ft_is_label_name(char *name)
{
	unsigned int			i;

	i = 0;
	ft_go_space(name, &i);
	while (name[i] && name[i] != LABEL_CHAR &&
		(ft_isdigit(name[i]) || ft_isalpha(name[i]) || name[i] == '_'))
		i++;
	return ((name[i] == LABEL_CHAR) ? 1 : 0);
}
