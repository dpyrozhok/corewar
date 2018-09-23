/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main10.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <dpyrozho@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 13:13:07 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/09/23 20:27:23 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int							g_fd;

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

void						ft_push_u_front(t_use_label **begin_list,
	t_use_label *elem)
{
	if (!*begin_list)
		elem->next = NULL;
	else
		elem->next = *begin_list;
	*begin_list = elem;
}

void						ft_read_head(t_my *inf)
{
	t_text					*p_t;

	inf->name2 = ft_memalloc(PROG_NAME_LENGTH);
	inf->comment = ft_memalloc(COMMENT_LENGTH);
	inf->magic_num = convert_end(COREWAR_EXEC_MAGIC, 4);
	ft_throu_empt_lines(inf);
	ft_name_comment(*inf, NAME_CMD_STRING, &inf->name2);
	if (inf->head->next)
	{
		p_t = inf->head;
		inf->head = inf->head->next;
		free(p_t->line);
		free(p_t);
		inf->y++;
	}
	ft_throu_empt_lines(inf);
	ft_name_comment(*inf, COMMENT_CMD_STRING, &inf->comment);
	if (inf->head->next)
	{
		p_t = inf->head;
		inf->head = inf->head->next;
		free(p_t->line);
		free(p_t);
		inf->y++;
	}
}

int							ft_throu_empt_lines(t_my *inf)
{
	t_text					*p_t;

	inf->x = 0;
	while (inf->head && inf->head->line)
	{
		ft_go_space(inf->head->line, &(inf->x));
		if (inf->head->line[inf->x] == '\0')
		{
			free(inf->head->line);
			p_t = inf->head;
			inf->head = inf->head->next;
			free(p_t);
			inf->y++;
		}
		else
			break ;
	}
	return (1);
}
