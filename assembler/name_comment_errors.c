/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 12:39:11 by amalkevy          #+#    #+#             */
/*   Updated: 2018/09/24 12:39:15 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			ft_error_code(char *le, t_my *inf, char *define)
{
	ft_printf(le, inf->y, inf->x, define + 1);
	exit(1);
}

void			ft_eror_code_n2(void *le, t_my *inf)
{
	le = NULL;
	ft_free(inf);
	exit(1);
}

void			ft_check_end(t_my *inf)
{
	char		c;

	lseek(inf->fd, -1, SEEK_END);
	read(inf->fd, &c, 1);
	if (c != '\n')
	{
		LE9;
		ft_eror_code_n2(0, inf);
	}
}

void			ft_write_name_comment(char **buf, char *line,
	char *define, t_my inf)
{
	int			i;
	int			max_i;

	i = 0;
	max_i = (*(define + 1) == 'n') ? PROG_NAME_LENGTH - 1 : COMMENT_LENGTH - 1;
	while (line[i] && line[i] != '"')
	{
		if (i >= max_i)
			ft_error_code(LE1, &inf, define);
		(*buf)[i] = line[i];
		if (line[i] == '\\')
		{
			i++;
			inf.x++;
			(*buf)[i] = line[i];
		}
		inf.x++;
		i++;
	}
	if (line[i] != '"')
		ft_error_code(LE2, &inf, define);
	inf.x++;
	ft_go_space(inf.head->line, &(inf.x));
	if (inf.head->line[inf.x] != '\0')
		ft_error_code(LE3, &inf, define);
}

void			ft_name_comment(t_my inf, char *define, char **buf)
{
	inf.x = 0;
	if (!inf.head || !inf.head->next)
	{
		ft_printf(LE4, inf.y, 0);
		exit(1);
	}
	ft_go_space(inf.head->line, &(inf.x));
	if (inf.head->line + inf.x != ft_strstr(inf.head->line + inf.x, define))
	{
		ft_printf(LE5, inf.y, inf.x, define);
		exit(1);
	}
	inf.x += ft_strlen(define);
	ft_go_space(inf.head->line, &(inf.x));
	if (inf.head->line[inf.x] != '"')
	{
		ft_printf(LE6, inf.y, inf.x, define + 1);
		exit(1);
	}
	inf.x++;
	ft_write_name_comment(buf, inf.head->line + inf.x, define, inf);
}
