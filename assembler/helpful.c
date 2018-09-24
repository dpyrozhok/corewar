/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpful.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <dpyrozho@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 12:38:27 by amalkevy          #+#    #+#             */
/*   Updated: 2018/09/24 14:39:43 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					codage(int j)
{
	return ((j == 0 || j == 8 || j == 11 || j == 14) ? 0 : 1);
}

unsigned int		size_dira(int j)
{
	if ((j >= 0 && j <= 7) || j == 12 || j == 15)
		return (4);
	else
		return (2);
}

void				ft_help_read_body1(t_my *inf, int j)
{
	inf->command_e->comm_id = (char)j;
	inf->command_e->t_dir_size = size_dira(j);
	inf->command_e->codage = (char)codage(j);
	inf->command_e->size += (int)inf->command_e->codage;
}

int					ft_gnl_without_com(int fd, char **line)
{
	char			*new;
	unsigned int	i;
	int				r;

	if ((r = get_next_line(fd, line)) == -1)
		return (-2);
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

unsigned int		convert_end(unsigned int ch, char bytes)
{
	unsigned char	*new_ptr;
	unsigned char	*ch_ptr;
	unsigned int	new;

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
