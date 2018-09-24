/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 12:37:43 by amalkevy          #+#    #+#             */
/*   Updated: 2018/09/24 12:37:47 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int							ft_lable(t_my *inf, int arg_i)
{
	unsigned int			start;
	int						end;
	t_use_label				*new;

	new = (t_use_label*)malloc(sizeof(t_use_label));
	if (inf->head->line[inf->x] == '%')
		inf->x++;
	start = inf->x;
	new->x = inf->x;
	new->y = inf->y;
	while (inf->head->line[inf->x] != '\0' && inf->head->line[inf->x] != ',' &&
			inf->head->line[inf->x] != ' ' && inf->head->line[inf->x] != '\t')
		inf->x++;
	end = inf->x;
	inf->command_e->arg[arg_i] = ft_strsub(inf->head->line, start, end - start);
	new->label = ft_strsub(inf->head->line, start, end - start);
	new->next = NULL;
	ft_push_u_front(&(inf->use_label), new);
	inf->x++;
	return (1);
}

int							ft_num(t_my *inf, int arg_i,
	unsigned int m, int is_end)
{
	unsigned int			n_start;
	unsigned int			n_end;
	char					*line;

	line = inf->head->line;
	n_start = m;
	if (line[m] == '-')
		m++;
	while (line[m] >= '0' && line[m] <= '9')
		m++;
	n_end = m;
	ft_go_space(line, &(m));
	if (is_end == 0 && line[m] != '\0')
		return (0);
	if (is_end != 0 && line[m] != ',')
		return (0);
	inf->x = m + 1;
	inf->command_e->arg[arg_i] = ft_strsub(line, n_start, n_end - n_start);
	return (1);
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
