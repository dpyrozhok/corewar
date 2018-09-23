/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_car_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 11:49:45 by popanase          #+#    #+#             */
/*   Updated: 2018/09/24 00:50:19 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/ft_check.h"

static void	ft_append_car(t_core *core, t_car *car)
{
	t_car	*tmp;

	tmp = core->cars;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = car;
	car->num = tmp->num + 1;
	car->prev = tmp;
}

void		ft_copy_car(t_core *core, t_car *src, int pos)
{
	t_car	*car;
	int		i;

	i = 0;
	car = (t_car *)ft_memalloc(sizeof(t_car));
	car->pos = pos;
	car->pos_res = 0;
	car->sw = 0;
	car->carry = src->carry;
	car->id = src->id;
	if (core->vis)
		ft_vcars_fork(core, car, pos);
	car->state = src->state;
	car->live = src->live;
	while (i < REG_NUMBER)
	{
		car->reg[i] = src->reg[i];
		i++;
	}
	core->qt_car++;
	car->cycle = -1;
	car->opcode = 0;
	ft_append_car(core, car);
}

void		ft_create_car(t_core *core, t_champ *champ, int pos, t_car *tmp)
{
	t_car	*car;

	car = (t_car *)ft_memalloc(sizeof(t_car));
	car->sw = 0;
	car->pos_res = 0;
	car->pos = pos;
	car->state = 1;
	car->id = champ->id;
	car->reg[0] = (unsigned int)champ->id;
	core->qt_car++;
	car->next = NULL;
	car->prev = NULL;
	car->cycle = -1;
	car->num = 1;
	if (core->cars)
	{
		tmp = core->cars;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = car;
		car->num = tmp->num + 1;
		car->prev = tmp;
	}
	else
		core->cars = car;
}
