/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vcars_check_on.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 18:32:42 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/24 00:53:54 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_visual.h"

static void	ft_set_rc(int *r, int *c, int pos)
{
	*r = 3 + ((pos % MEM_SIZE) / 64) % 64;
	*c = 3 + (3 * ((pos % MEM_SIZE) % 64)) % 192;
}

void		ft_vcars_on(t_core *core, t_car *car, int ag, int pos)
{
	int		r;
	int		c;
	t_champ	*champ;

	pthread_mutex_lock(&core->mut);
	champ = ft_get_champ(core, car->id);
	if (pos < 0)
		pos = MEM_SIZE + pos;
	car->pos_res = pos;
	car->sw = 1;
	attron(COLOR_PAIR(champ->col) | A_BOLD);
	ft_set_rc(&r, &c, pos);
	mvprintw(r, c, "%02x", (unsigned char)(ag >> 24));
	ft_memset(core->a_col + (pos % MEM_SIZE), champ->col, 1);
	ft_set_rc(&r, &c, ++pos);
	mvprintw(r, c, "%02x", (unsigned char)(ag >> 16 & 255));
	ft_memset(core->a_col + (pos % MEM_SIZE), champ->col, 1);
	ft_set_rc(&r, &c, ++pos);
	mvprintw(r, c, "%02x", (unsigned char)(ag >> 8 & 255));
	ft_memset(core->a_col + (pos % MEM_SIZE), champ->col, 1);
	ft_set_rc(&r, &c, ++pos);
	mvprintw(r, c, "%02x", (unsigned char)(ag & 255));
	ft_memset(core->a_col + (pos % MEM_SIZE), champ->col, 1);
	attroff(COLOR_PAIR(champ->col) | A_BOLD);
	pthread_mutex_unlock(&core->mut);
}

void		ft_vcars_off(t_core *core, t_car *tmp)
{
	int		pos;
	int		r;
	int		c;

	pthread_mutex_lock(&core->mut);
	tmp->sw = 0;
	pos = tmp->pos_res;
	ft_set_rc(&r, &c, pos);
	attron(COLOR_PAIR(core->a_col[pos % MEM_SIZE]));
	mvprintw(r, c, "%02x", (unsigned char)(core->arena[pos % MEM_SIZE]));
	attroff(COLOR_PAIR(core->a_col[pos % MEM_SIZE]));
	ft_set_rc(&r, &c, ++pos);
	attron(COLOR_PAIR(core->a_col[pos % MEM_SIZE]));
	mvprintw(r, c, "%02x", (unsigned char)(core->arena[pos % MEM_SIZE]));
	attroff(COLOR_PAIR(core->a_col[pos % MEM_SIZE]));
	ft_set_rc(&r, &c, ++pos);
	attron(COLOR_PAIR(core->a_col[pos % MEM_SIZE]));
	mvprintw(r, c, "%02x", (unsigned char)(core->arena[pos % MEM_SIZE]));
	attroff(COLOR_PAIR(core->a_col[pos % MEM_SIZE]));
	ft_set_rc(&r, &c, ++pos);
	attron(COLOR_PAIR(core->a_col[pos % MEM_SIZE]));
	mvprintw(r, c, "%02x", (unsigned char)(core->arena[pos % MEM_SIZE]));
	attroff(COLOR_PAIR(core->a_col[pos % MEM_SIZE]));
	pthread_mutex_unlock(&core->mut);
}

void		ft_vcars_check(t_core *core, t_car *tmp)
{
	int		r;
	int		c;

	if (tmp->sw)
		ft_vcars_off(core, tmp);
	pthread_mutex_lock(&core->mut);
	ft_set_rc(&r, &c, tmp->pos);
	attron(COLOR_PAIR(core->a_col[tmp->pos % MEM_SIZE]));
	mvprintw(r, c, "%02x", core->arena[tmp->pos % MEM_SIZE]);
	attroff(COLOR_PAIR(core->a_col[tmp->pos % MEM_SIZE]));
	pthread_mutex_unlock(&core->mut);
}

void		ft_vcars_opcode(t_core *core, t_car *car)
{
	t_champ	*champ;
	int		r;
	int		c;

	pthread_mutex_lock(&core->mut);
	champ = ft_get_champ(core, car->id);
	ft_set_rc(&r, &c, car->pos);
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
