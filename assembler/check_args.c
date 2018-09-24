/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 12:37:55 by amalkevy          #+#    #+#             */
/*   Updated: 2018/09/24 12:37:57 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					ft_dir(const char *line,
	t_my *inf, int is_end)
{
	unsigned int	m;
	int				arg_i;

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

int					ft_ind(const char *line, t_my *inf, int is_end)
{
	unsigned int	m;
	int				arg_i;

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

int					ft_reg(const char *line, t_my *inf, int is_end)
{
	unsigned int	m;
	int				z;
	int				arg_i;

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

int					ft_check_args(t_my *inf, char *line,
	int num_command)
{
	int				z;
	int				i;

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

void				ft_function(t_my *inf, int j, char *line, t_text **p_t)
{
	ft_help_read_body1(inf, j);
	if (ft_check_args(inf, line, j) == 0)
	{
		LE8;
		ft_eror_code_n2(0, inf);
	}
	ft_gogogogo(inf, p_t);
}
