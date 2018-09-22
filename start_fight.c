/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_fight.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 21:21:59 by popanase          #+#    #+#             */
/*   Updated: 2018/09/21 21:26:55 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "ncurs.h"

void	ft_get_n_car_value(t_core *core, t_car *car)
{
	t_champ	*champ;
	int		r;
	int		c;

	if (core->arena[car->pos % MEM_SIZE] > 0 &&
		core->arena[car->pos % MEM_SIZE] < 17)
	{
		car->opcode = core->arena[car->pos % MEM_SIZE];
		car->cycle = g_op_tab[car->opcode - 1].cycle;
	}
	else
		car->opcode = 0;
	if (core->vis)
	{
		pthread_mutex_lock(&core->mut);
		champ = ft_get_champ(core, car->id);
		r = 3 + ((car->pos % MEM_SIZE) / 64) % 64;
		c = 3 + (3 * ((car->pos % MEM_SIZE) % 64)) % 192;
		if (car->opcode == 1 && car->id == ft_read_4(core, car->pos % MEM_SIZE))
			attron(A_BOLD | COLOR_PAIR(champ->col_live));
		else
			attron(A_REVERSE | COLOR_PAIR(core->a_col[car->pos % MEM_SIZE]));
		mvprintw(r, c, "%02x", core->arena[car->pos % MEM_SIZE]);
		if (car->opcode == 1 && car->id == ft_read_4(core, car->pos % MEM_SIZE))
			attroff(A_BOLD | COLOR_PAIR(champ->col_live));
		else
			attroff(A_REVERSE | COLOR_PAIR(core->a_col[car->pos % MEM_SIZE]));
		pthread_mutex_unlock(&core->mut);
	}
}

void	ft_touch_car(t_core *core, t_car *car)
{
	if (car->cycle == -1)
		ft_get_n_car_value(core, car);
	if (car->cycle < 2)
	{
		if (core->vis)
			ft_vcars_norev(core, car);
		if (car->opcode > 0 && car->opcode < 17)
		{
			if (core->vis && car->sw)
				ft_vcars_off(core, car);
			ft_opcode_switcher(core, car);
		}
		car->cycle = -1;
		car->pos++;
		if (core->vis)
			ft_vcars_rev(core, car);
	}
	else
		car->cycle--;
}

void	ft_vfight_run(t_core *core, t_car *tmp)
{
	while (core->qt_car > 0)
	{
		tmp = core->cars;
		core->cycle++;
		while (tmp->next)
			tmp = tmp->next;
		while (tmp)
		{
			if (tmp->state)
				ft_touch_car(core, tmp);
			tmp = tmp->prev;
		}
		ft_draw(core);
		if (core->microsec)
			usleep(core->microsec);
		ft_is_paused(core);
		if (core->cycle == core->c_to_die + core->last_check \
			|| core->c_to_die <= 0)
		{
			ft_make_check(core);
			core->last_check = core->cycle;
		}
	}
}

void	ft_fight(t_core *core, t_car *tmp)
{
	while (core->qt_car > 0)
	{
		tmp = core->cars;
		core->cycle++;
		while (tmp->next)
			tmp = tmp->next;
		while (tmp)
		{
			if (tmp->state)
				ft_touch_car(core, tmp);
			tmp = tmp->prev;
		}
		if (core->dump != -1 && core->dump == core->cycle)
		{
			ft_dump(core);
			exit(0);
		}
		if (core->cycle == core->c_to_die + core->last_check \
			|| core->c_to_die <= 0)
		{
			ft_make_check(core);
			core->last_check = core->cycle;
		}
	}
}

void	ft_start_fight(t_core *core)
{
	if (core->vis)
		ft_fight_visual(core);
	else
		ft_fight(core, NULL);
}
