/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <dpyrozho@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 13:13:07 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/09/23 20:03:30 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void					ft_free_command(t_my *inf)
{
	t_comm				*p_c;
	int					i;

	while (inf->command_s)
	{
		p_c = inf->command_s;
		inf->command_s = inf->command_s->next;
		i = 0;
		while (i < 3 && p_c->arg[i])
			free(p_c->arg[i++]);
		free(p_c->name);
		free(p_c);
	}
}

void					ft_free_label(t_my *inf)
{
	t_use_label			*p_use_l;

	while (inf->use_label)
	{
		p_use_l = inf->use_label;
		inf->use_label = inf->use_label->next;
		free(p_use_l->label);
		free(p_use_l);
	}
}

void					ft_free(t_my *inf)
{
	t_label				*p_l;
	t_text				*p_t;

	while (inf->head)
	{
		p_t = inf->head;
		inf->head = inf->head->next;
		free(p_t->line);
		free(p_t);
	}
	while (inf->label_s)
	{
		p_l = inf->label_s;
		inf->label_s = inf->label_s->next;
		free(p_l->name);
		free(p_l);
	}
	if (inf->command_s)
		ft_free_command(inf);
	if (inf->use_label)
		ft_free_label(inf);
	free(inf->name2);
	free(inf->comment);
	free(inf->file_name);
}

int						ft_check_format(char *name)
{
	char				*format;

	format = ft_strchr(name, '.');
	if (format && ft_strcmp(format, ".s") == 0)
		return (1);
	else
		return (0);
}

char					*ft_get_name(char *name)
{
	char				*get;
	unsigned int		i;
	char				*tmp;

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
