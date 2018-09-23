/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_isend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 21:32:04 by popanase          #+#    #+#             */
/*   Updated: 2018/09/24 00:52:24 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/ft_visual.h"

static void	ft_check_cars(t_core *core)
{
	t_car	*tmp;

	tmp = core->cars;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->state)
		{
			if (!tmp->live)
			{
				tmp->state = 0;
				core->qt_car--;
				if (core->vis)
					ft_vcars_check(core, tmp);
			}
			else
				tmp->live = 0;
		}
		tmp = tmp->prev;
	}
}

void		ft_make_check(t_core *core)
{
	t_champ	*champ;
	int		a;

	a = 0;
	core->qt_check++;
	champ = core->champs;
	if (core->vis)
		ft_breakdown(core);
	pthread_mutex_lock(&core->mut);
	while (champ)
	{
		a += champ->all_live;
		champ->s_live = 0;
		champ->all_live = 0;
		champ = champ->next;
	}
	if (a >= NBR_LIVE || core->qt_check == MAX_CHECKS)
	{
		core->qt_check = 0;
		core->c_to_die -= CYCLE_DELTA;
	}
	pthread_mutex_unlock(&core->mut);
	ft_check_cars(core);
}
