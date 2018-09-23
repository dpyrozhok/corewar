/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_champ_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 11:49:23 by popanase          #+#    #+#             */
/*   Updated: 2018/09/24 00:50:28 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/ft_check.h"

void		ft_place_champ(t_core *core)
{
	t_champ	*tmp;
	int		shift;

	shift = 0;
	tmp = core->champs;
	if (core->vis)
	{
		ft_init_screen(core, 0, 3, 3);
		ft_draw(core);
	}
	while (tmp)
	{
		if (core->vis)
			ft_champ_visual(core, tmp, shift);
		ft_memcpy(core->arena + shift, tmp->code, tmp->size);
		ft_create_car(core, tmp, shift, NULL);
		shift += MEM_SIZE / core->qt_champ;
		core->winner_id = tmp->id;
		tmp = tmp->next;
	}
}

static void	ft_init_champ(t_core *core, t_champ *champ, int n)
{
	t_champ	*tmp;
	int		flag;

	flag = 0;
	while (!flag)
	{
		flag = 1;
		tmp = core->champs;
		while (tmp)
		{
			if (n == tmp->id)
			{
				n++;
				flag = 0;
				break ;
			}
			tmp = tmp->next;
		}
	}
	champ->id = n;
	champ->col = 20 + core->col_mod++;
	core->col_mod = core->col_mod % 4;
	champ->col_live = champ->col + 10;
	champ->s_live = 0;
	champ->all_live = 0;
}

static void	ft_append_champ(t_core *core, t_champ *champ)
{
	t_champ	*tmp;

	if (!core->champs)
		core->champs = champ;
	else
	{
		tmp = core->champs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = champ;
	}
}

void		ft_parse_champion(t_core *core, int fd, int n)
{
	char			buf[4];
	unsigned int	size;
	t_champ			*champ;

	champ = (t_champ *)ft_memalloc(sizeof(t_champ));
	read(fd, &buf, 4);
	ft_memset(&champ->name, '\0', PROG_NAME_LENGTH + 1);
	read(fd, &champ->name, PROG_NAME_LENGTH);
	champ->name[PROG_NAME_LENGTH] = '\0';
	read(fd, &buf, 4);
	read(fd, &buf, 4);
	size = (unsigned int)((unsigned char)buf[0] << 24 \
		| (unsigned char)buf[1] << 16 | (unsigned char)buf[2] << 8 \
		| (unsigned char)buf[3]);
	champ->size = size;
	ft_memset(&champ->comment, '\0', COMMENT_LENGTH + 1);
	read(fd, &champ->comment, COMMENT_LENGTH);
	champ->comment[COMMENT_LENGTH] = '\0';
	read(fd, &buf, 4);
	champ->code = (unsigned char *)ft_memalloc(sizeof(unsigned char) * \
		champ->size);
	read(fd, champ->code, champ->size);
	core->qt_champ++;
	ft_init_champ(core, champ, n);
	ft_append_champ(core, champ);
}

t_champ		*ft_get_champ(t_core *core, int id)
{
	t_champ	*tmp;

	tmp = core->champs;
	while (tmp)
	{
		if (tmp->id == id)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
