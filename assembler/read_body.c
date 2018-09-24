/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_body.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 12:39:32 by amalkevy          #+#    #+#             */
/*   Updated: 2018/09/24 12:39:33 by amalkevy         ###   ########.fr       */
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

int					ft_is_label_name(char *name)
{
	unsigned int	i;

	i = 0;
	ft_go_space(name, &i);
	while (name[i] && name[i] != LABEL_CHAR &&
		(ft_isdigit(name[i]) || ft_isalpha(name[i]) || name[i] == '_'))
		i++;
	return ((name[i] == LABEL_CHAR) ? 1 : 0);
}

void				ft_command(int j, t_my *inf)
{
	t_comm			*new;

	new = (t_comm*)malloc(sizeof(t_comm));
	new->name = ft_strdup(OP(j).op);
	new->next = NULL;
	new->label = inf->label_e;
	new->arg[0] = NULL;
	new->arg[1] = NULL;
	new->arg[2] = NULL;
	new->arg_id[0] = 0;
	new->arg_id[1] = 0;
	new->arg_id[2] = 0;
	new->size = 1;
	new->t_dir_size = 0;
	new->codage = 0;
	if (inf->command_s)
		new->cidr = inf->command_e->cidr + 1;
	else
		new->cidr = 1;
	ft_push_c_back(inf, new);
}

int					ft_find_command(t_my *inf, char *command_name)
{
	int				j;

	j = 0;
	while (j < 16)
	{
		if (ft_strcmp(command_name, OP(j).op) == 0)
		{
			ft_command(j, inf);
			break ;
		}
		j++;
	}
	if (j >= 16)
	{
		LE7;
		ft_eror_code_n2(0, inf);
	}
	return (j);
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
			if (HLP)
			{
				if (HLP2)
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
