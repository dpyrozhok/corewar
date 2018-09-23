/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <dpyrozho@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 13:13:07 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/09/23 19:28:02 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void				ft_print_txt(t_text *t)
{
	t_text			*p_t;

	p_t = t;
	while (p_t->next)
	{
		ft_printf("%s\t\n", p_t->line);
		p_t = p_t->next;
	}
	if (p_t)
		ft_printf("%s\t\n", p_t->line);
}

int					ft_gnl_without_com(int fd, char **line)
{
	char			*new;
	unsigned int	i;
	int				r;

	r = get_next_line(fd, line);
	if (ft_strchr(*line, '#') || ft_strchr(*line, ';'))
	{
		i = 0;
		while ((*line)[i] != '#' && (*line)[i] != ';')
			i++;
		new = (char*)malloc(sizeof(char) * (i + 2));
		ft_strncpy(new, *line, i);
		new[i] = '\0';
		ft_memdel((void**)line);
		*line = new;
	}
	return (r);
}

void				ft_check_end(t_my *inf)
{
	char			c;

	lseek(inf->fd, -1, SEEK_END);
	read(inf->fd, &c, 1);
	if (c != '\n')
	{
		LE9;
		ft_eror_code_n2(0, inf);
	}
}

int					ft_pliz_write_to_file(t_my *inf)
{
	char nulek[4];

	ft_bzero(nulek, 4);
	if ((g_fd = open(inf->file_name, O_WRONLY | O_CREAT | O_TRUNC,
S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		ft_printf("error: open\n");
	}
	write(g_fd, &inf->magic_num, sizeof(inf->magic_num));
	write(g_fd, inf->name2, 128);
	write(g_fd, &nulek, 4);
	write(g_fd, &(nulek), 4);
	write(g_fd, inf->comment, 2048);
	write(g_fd, &nulek, 4);
	return (0);
}

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
