/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 18:31:11 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/24 00:52:32 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_visual.h"

static void	ft_fill_new(t_core *core, double stp, int remain, int r)
{
	int		i;
	int		j;
	int		col;
	int		ttl;
	t_champ	*cur;

	i = 0;
	col = 0;
	ttl = 0;
	cur = core->champs;
	while (i++ < core->qt_champ)
	{
		ttl = (cur->s_live && (stp * cur->s_live < 1)) ? 1 : stp * cur->s_live;
		if (ttl && remain-- > 0)
			ttl++;
		j = 0;
		attron(A_BOLD | COLOR_PAIR(cur->col));
		while (j++ < ttl)
		{
			mvprintw(r, 201 + col, "-");
			col = (col < 50) ? col + 1 : 50;
		}
		attroff(A_BOLD | COLOR_PAIR(cur->col));
		cur = cur->next;
	}
}

static void	ft_new_score(t_core *core, t_champ *curr, double step, int r)
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
	ft_fill_new(core, step, 50 - total, r);
	attron(COLOR_PAIR(4));
	mvprintw(core->last_break, 251, "]");
	attroff(COLOR_PAIR(4));
}

static void	ft_scoring(t_core *core, int r)
{
	int		i;
	double	sum;
	t_champ	*curr;

	i = 0;
	sum = 0.0;
	curr = core->champs;
	while (i++ < core->qt_champ)
	{
		sum += (double)curr->s_live;
		curr = curr->next;
	}
	if (sum)
		ft_new_score(core, core->champs, 50.0 / sum, r);
}

static void	ft_breaking(t_core *core, int *r, int i, t_champ *curr)
{
	attron(COLOR_PAIR(4) | A_BOLD);
	mvprintw(3, 200, "%s", (core->fin) ? "** FINISH ** " : "** RUNNING **");
	if (core->microsec)
		mvprintw(5, 222, "%-10d", 1000000 / core->microsec);
	else
		mvprintw(5, 222, "Stealth");
	mvprintw(8, 200, "Cycle : %d", core->cycle);
	mvprintw(10, 200, "Processes : %-10d", core->qt_car);
	if (core->microsec != 1000000 && core->microsec)
		mvprintw(12, 200, "Speed: %dx     ", 100000 / core->microsec);
	else if (core->microsec)
		mvprintw(12, 200, "Speed: 0.1x        ");
	else
		mvprintw(12, 200, "Speed: Stealth     ");
	curr = core->champs;
	while (i++ < core->qt_champ)
	{
		(*r)++;
		mvprintw((*r)++, 214, "%21d", curr->last_live);
		mvprintw(*r, 228, "%7d", curr->s_live);
		*r += 2;
		curr = curr->next;
	}
	(*r)++;
	attroff(COLOR_PAIR(4) | A_BOLD);
}

void		ft_draw(t_core *core)
{
	int		r;
	t_champ	*curr;

	ft_resize(core);
	pthread_mutex_lock(&core->mut);
	r = 14;
	ft_breaking(core, &r, 0, NULL);
	ft_scoring(core, r);
	r += 4;
	attron(COLOR_PAIR(4) | A_BOLD);
	mvprintw(++r, 215, "%-10d", core->c_to_die);
	if (core->fin)
	{
		curr = ft_get_champ(core, core->winner_id);
		r += 8;
		mvprintw(r, 200, "The winner is : ");
		attron(COLOR_PAIR(curr->col));
		mvprintw(r++, 216, "%s", curr->name);
		attroff(COLOR_PAIR(curr->col));
		mvprintw(++r, 200, "Press %s %s", (core->microsec) ? "any key" : \
		"ESC", "to exit");
	}
	attroff(COLOR_PAIR(4) | A_BOLD);
	refresh();
	pthread_mutex_unlock(&core->mut);
}
