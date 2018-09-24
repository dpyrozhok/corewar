/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <dpyrozho@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 13:13:07 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/09/24 15:03:58 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					g_fd;

int					ft_check_format(char *name)
{
	char				*format;

	format = ft_strchr(name, '.');
	if (format && ft_strcmp(format, ".s") == 0)
		return (1);
	else
		return (0);
}

char				*ft_get_name(char *name)
{
	char			*get;
	unsigned int	i;
	char			*tmp;

	i = 0;
	while (name[i] != '.')
		i++;
	get = malloc(sizeof(char) * (i + 1));
	ft_strncpy(get, name, i);
	get[i] = '\0';
	tmp = get;
	get = ft_strjoin(get, ".cor");
	get[i + 4] = '\0';
	free(tmp);
	return (get);
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

t_use_label			*ft_check_correct_labels(t_my *inf)
{
	t_label			*all;
	t_use_label		*to_check;

	all = inf->label_s;
	to_check = inf->use_label;
	while (to_check != NULL)
	{
		while (all != NULL)
		{
			if (ft_strcmp(all->name, to_check->label + 1) == 0)
				break ;
			else
				all = all->next;
		}
		if (all == NULL)
			return (to_check);
		else
			to_check = to_check->next;
		all = inf->label_s;
	}
	return (NULL);
}

int					main(int ac, char **av)
{
	t_my			inf;
	t_use_label		*p_use_l;
	char			command_name[6];

	if (ac < 2 || ac > 3 || !ft_check_format(av[1]))
		return (ft_printf("Not valid argument\n"));
	else
		inf.file_name = ft_get_name(av[1]);
	ft_obnul(&inf, av[1]);
	ft_read_all(&inf);
	ft_read_head(&inf);
	ft_read_body(&inf, command_name, 0);
	ft_check_end(&inf);
	if ((p_use_l = ft_check_correct_labels(&inf)) && p_use_l != NULL)
	{
		SE1;
		ft_free(&inf);
		exit(1);
	}
	ft_pliz_write_to_file(&inf);
	ft_write_commands(&inf, 0, 0);
	ft_write_botsize(&inf);
	ft_free(&inf);
	ft_printf("Writing output program to %s\n", inf.file_name);
	return (0);
}
