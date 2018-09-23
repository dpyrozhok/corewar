/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <dpyrozho@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 13:13:07 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/09/23 20:03:50 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char				*ft_nastenka(char command_name[6], t_my *inf, int *j)
{
	ft_bzero(command_name, 6);
	inf->x = 0;
	*j = 0;
	return (inf->head->line);
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

void				ft_read_body(t_my *inf,
char command_name[6], char *line)
{
	int				j;
	t_text			*p_t;

	while (inf->head)
	{
		if ((ft_throu_empt_lines(inf)) && !inf->head)
			return ;
		if (ft_is_label_name(line = ft_nastenka(command_name, inf, &j)))
		{
			if (HUYAIN)
			{
				if (HUYAIN2)
					return ;
				line = inf->head->line;
			}
			if (ft_is_label_name(line + inf->x))
				continue ;
		}
		ft_go_space(line, (&inf->x));
		while (ft_isalpha(line[inf->x]) && j < 5)
			command_name[j++] = line[inf->x++];
		ft_function(inf, j = ft_find_command(inf, command_name), line, &p_t);
	}
}

void				ft_obnul(t_my *inf, char *name)
{
	inf->fd = open(name, O_RDONLY);
	inf->head = NULL;
	inf->label_s = NULL;
	inf->label_e = NULL;
	inf->command_s = NULL;
	inf->command_e = NULL;
	inf->use_label = NULL;
	inf->x = 1;
	inf->y = 1;
	inf->botsize = 0;
}

void				ft_push_t_back(t_my *my, t_text *new, int i)
{
	t_text			*p_t;

	p_t = my->head;
	if (!p_t)
	{
		my->head = new;
		return ;
	}
	new->i = i;
	while (p_t->next)
	{
		p_t = p_t->next;
	}
	if (p_t->line)
		p_t->next = new;
	else
		my->head = new;
}
