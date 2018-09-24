/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_through.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <dpyrozho@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 12:38:11 by amalkevy          #+#    #+#             */
/*   Updated: 2018/09/24 15:02:20 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					ft_gogogogo(t_my *inf, t_text **p_t)
{
	*p_t = inf->head;
	inf->head = inf->head->next;
	free((*p_t)->line);
	free(*p_t);
	inf->y++;
	return (1);
}

int					ft_go_space(char *line, unsigned int *x)
{
	while (line[*x] && (line[*x] == ' ' || line[*x] == '\t'))
	{
		(*x)++;
	}
	return (1);
}

int					ft_throu_empt_lines(t_my *inf)
{
	t_text			*p_t;

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

void				ft_read_all(t_my *inf)
{
	t_text			*new_t;
	int				i;
	int				r;

	i = 1;
	new_t = (t_text *)malloc(sizeof(t_text));
	new_t->next = NULL;
	while ((r = ft_gnl_without_com(inf->fd, &(new_t->line))) > 0)
	{
		ft_push_t_back(inf, new_t, i++);
		new_t = (t_text *)malloc(sizeof(t_text));
		new_t->next = NULL;
	}
	if (r == -2)
	{
		free(inf->file_name);
		ft_printf("Invalid file, please put adequate file\n");
		exit(1);
	}
	free(new_t->line);
	free(new_t);
}

void				ft_read_head(t_my *inf)
{
	t_text			*p_t;

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
