/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_breakdown.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 18:30:51 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/24 00:52:15 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_visual.h"

static void	ft_fill_score(t_core *core, t_champ *cur, double stp, int remain)
{
	int		i;
	int		j;
	int		col;
	int		ttl;

	i = 0;
	col = 0;
	ttl = 0;
	while (i++ < core->qt_champ)
	{
		ttl = (cur->s_live && (stp * cur->s_live < 1)) ? 1 : stp * cur->s_live;
		if (ttl && remain-- > 0)
			ttl++;
		j = 0;
		attron(A_BOLD | COLOR_PAIR(cur->col));
		while (j++ < ttl)
		{
			mvprintw(core->last_break, 201 + col, "-");
			col = (col < 50) ? col + 1 : 50;
		}
		attroff(A_BOLD | COLOR_PAIR(cur->col));
		cur = cur->next;
	}
}

static void	ft_break_score(t_core *core, t_champ *curr, double step)
{
	int		i;
	int		total;

	i = 0;
	total = 0;
	while (i++ < core->qt_champ)
	{
		if (curr->s_live && (step * curr->s_live < 1))
			total++;
		else
			total += (step * curr->s_live);
		curr = curr->next;
	}
	ft_fill_score(core, core->champs, step, 50 - total);
	attron(COLOR_PAIR(4));
	mvprintw(core->last_break, 251, "]");
	attroff(COLOR_PAIR(4));
}

static void	ft_break_last(t_core *core)
{
	attron(COLOR_PAIR(4));
	mvprintw(core->last_break, 201, \
		"--------------------------------------------------]");
	attroff(COLOR_PAIR(4));
	if (core->last_break)
	{
		attron(COLOR_PAIR(4));
		mvprintw(core->last_break - 3, 201, \
			"--------------------------------------------------]");
		attroff(COLOR_PAIR(4));
	}
}

void		ft_breakdown(t_core *core)
{
	int		i;
	double	sum;
	t_champ	*curr;

	pthread_mutex_lock(&core->mut);
	i = 0;
	sum = 0.0;
	curr = core->champs;
	while (i++ < core->qt_champ)
	{
		sum += (double)curr->s_live;
		curr = curr->next;
	}
	if (sum)
		ft_break_score(core, core->champs, 50.0 / sum);
	else
		ft_break_last(core);
	pthread_mutex_unlock(&core->mut);
}
