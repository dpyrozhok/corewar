/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <dpyrozho@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 13:13:07 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/09/23 20:03:36 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned int			convert_end(unsigned int ch, char bytes)
{
	unsigned char		*new_ptr;
	unsigned char		*ch_ptr;
	unsigned int		new;

	new_ptr = (unsigned char *)&new;
	ch_ptr = (unsigned char *)&ch;
	if (bytes == 4)
	{
		new_ptr[0] = ch_ptr[3];
		new_ptr[1] = ch_ptr[2];
		new_ptr[2] = ch_ptr[1];
		new_ptr[3] = ch_ptr[0];
	}
	if (bytes == 2)
	{
		new_ptr[0] = ch_ptr[1];
		new_ptr[1] = ch_ptr[0];
	}
	return (new);
}

int						ft_go_space(char *line, unsigned int *x)
{
	while (line[*x] && (line[*x] == ' ' || line[*x] == '\t'))
	{
		(*x)++;
	}
	return (1);
}

void					ft_error_code(char *le, t_my *inf, char *define)
{
	ft_printf(le, inf->y, inf->x, define + 1);
	exit(1);
}

void					ft_write_name_comment(char **buf, char *line,
	char *define, t_my inf)
{
	int					i;
	int					max_i;

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

void					ft_name_comment(t_my inf, char *define, char **buf)
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
