/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vcars_champ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 18:33:45 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/24 00:53:49 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_visual.h"

void	ft_vcars_norev(t_core *core, t_car *car)
{
	int		r;
	int		c;

	pthread_mutex_lock(&core->mut);
	r = 3 + ((car->pos % MEM_SIZE) / 64) % 64;
	c = 3 + (3 * ((car->pos % MEM_SIZE) % 64)) % 192;
	attron(COLOR_PAIR(core->a_col[car->pos % MEM_SIZE]));
	mvprintw(r, c, "%02x", core->arena[car->pos % MEM_SIZE]);
	attroff(COLOR_PAIR(core->a_col[car->pos % MEM_SIZE]));
	pthread_mutex_unlock(&core->mut);
}

void	ft_vcars_rev(t_core *core, t_car *car)
{
	int		r;
	int		c;
	t_champ	*champ;

	pthread_mutex_lock(&core->mut);
	champ = ft_get_champ(core, car->id);
	r = 3 + ((car->pos % MEM_SIZE) / 64) % 64;
	c = 3 + (3 * ((car->pos % MEM_SIZE) % 64)) % 192;
	if (core->arena[car->pos % MEM_SIZE] == 1 \
		&& car->id == ft_read_4(core, car->pos % MEM_SIZE))
		attron(A_BOLD | COLOR_PAIR(champ->col_live));
	else
		attron(A_REVERSE | COLOR_PAIR(core->a_col[car->pos % MEM_SIZE]));
	mvprintw(r, c, "%02x", core->arena[car->pos % MEM_SIZE]);
	if (core->arena[car->pos % MEM_SIZE] == 1 \
		&& car->id == ft_read_4(core, car->pos % MEM_SIZE))
		attroff(A_BOLD | COLOR_PAIR(champ->col_live));
	else
		attroff(A_REVERSE | COLOR_PAIR(core->a_col[car->pos % MEM_SIZE]));
	refresh();
	pthread_mutex_unlock(&core->mut);
}

void	ft_champ_visual(t_core *core, t_champ *tmp, int shift)
{
	unsigned int	i;
	unsigned int	r;
	unsigned int	c;

	pthread_mutex_lock(&core->mut);
	attron(COLOR_PAIR(tmp->col));
	i = 0;
	r = 3 + (shift / 64);
	c = 3 + 3 * (shift % 64);
	while (i < tmp->size)
	{
		mvprintw(r, c, "%02x", tmp->code[i]);
		if ((1 + i + shift % 64) % 64 == 0 && !(i == 0 && shift == 0))
		{
			c = 3;
			r++;
		}
		else
			c += 3;
		i++;
	}
	attroff(COLOR_PAIR(tmp->col));
	ft_memset(core->a_col + shift, tmp->col, tmp->size);
	refresh();
	pthread_mutex_unlock(&core->mut);
}

void	ft_vcars_fork(t_core *core, t_car *car, int pos)
{
	t_champ	*champ;
	int		r;
	int		c;

	pthread_mutex_lock(&core->mut);
	champ = ft_get_champ(core, car->id);
	r = 3 + ((pos % MEM_SIZE) / 64) % 64;
	c = 3 + (3 * ((pos % MEM_SIZE) % 64)) % 192;
	attron(COLOR_PAIR(champ->col) | A_REVERSE);
	mvprintw(r, c, "%02x", core->arena[pos]);
	attroff(COLOR_PAIR(champ->col) | A_REVERSE);
	pthread_mutex_unlock(&core->mut);
}
