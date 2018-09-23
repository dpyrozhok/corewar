/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 18:28:03 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/24 00:53:00 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_visual.h"

static int	ft_count_dig(int nbr)
{
	int		cnt;

	if (nbr == INT_MIN)
		return (11);
	cnt = 0;
	if (nbr < 0)
	{
		cnt++;
		nbr = -nbr;
	}
	cnt++;
	while (nbr / 10 > 0)
	{
		nbr /= 10;
		cnt++;
	}
	return (cnt);
}

static void	ft_win_half(t_core *core, t_champ *curr, int i, int *r)
{
	pthread_mutex_lock(&core->mut);
	attron(COLOR_PAIR(4) | A_BOLD);
	mvprintw(32, 89, "%18s", "");
	mvprintw(33, 85, "%25s", "");
	mvprintw(3, 200, "** RUNNING **");
	mvprintw(5, 200, "Cycles/second limit : %d", 10);
	mvprintw(8, 200, "Cycle : %d", core->cycle);
	mvprintw(10, 200, "Processes : %d", core->qt_car);
	mvprintw(12, 200, "Speed: %dx", 100000 / core->microsec);
	while (i++ < core->qt_champ)
	{
		mvprintw(*r, 200, "Player %d : ", curr->id);
		attron(COLOR_PAIR(curr->col));
		mvprintw((*r)++, 210 + ft_count_dig(curr->id), "%s", curr->name);
		attroff(COLOR_PAIR(curr->col));
		mvprintw(*r, 202, "Last live : ");
		mvprintw((*r)++, 214, "%21d", curr->last_live);
		mvprintw(*r, 202, "Lives in current period : ");
		mvprintw(*r, 228, "%7d", curr->s_live);
		*r += 2;
		curr = curr->next;
	}
	attroff(COLOR_PAIR(4) | A_BOLD);
	pthread_mutex_unlock(&core->mut);
}

static void	ft_fill_win(t_core *core, int r)
{
	ft_win_half(core, core->champs, 0, &r);
	attron(COLOR_PAIR(4) | A_BOLD);
	pthread_mutex_lock(&core->mut);
	mvprintw(r++, 200, "Live breakdown for current period :");
	attroff(A_BOLD);
	mvprintw(r++, 200, "[--------------------------------------------------]");
	attron(A_BOLD);
	mvprintw(++r, 200, "Live breakdown for last period :");
	attroff(A_BOLD);
	mvprintw(++r, 200, "[--------------------------------------------------]");
	core->last_break = r;
	attron(A_BOLD);
	r++;
	mvprintw(++r, 200, "CYCLE_TO_DIE : %d", core->c_to_die);
	r++;
	mvprintw(++r, 200, "CYCLE_DELTA : %d", CYCLE_DELTA);
	r++;
	mvprintw(++r, 200, "NBR_LIVE : %d", NBR_LIVE);
	r++;
	mvprintw(++r, 200, "MAX_CHECKS : %d", MAX_CHECKS);
	attroff(COLOR_PAIR(4));
	attroff(A_BOLD);
	pthread_mutex_unlock(&core->mut);
}

void		*ft_resize(void *ptr)
{
	t_core	*p;

	p = (t_core *)ptr;
	if (LINES < 69 || COLS < 254)
	{
		pthread_mutex_lock(&(p)->mut);
		clear();
		refresh();
		endwin();
		system("reset");
		ft_printf("'corewar' shut down. Resize window to min "
			"254 cols and 69 rows. Currently %d cols and %d rows.\n", \
			COLS, LINES);
		exit(27);
		pthread_mutex_unlock(&(p)->mut);
	}
	return (NULL);
}

void		ft_init_screen(t_core *core, int i, int r, int c)
{
	pthread_mutex_init(&core->mut, NULL);
	ft_init_win(core);
	getch();
	ft_resize(core);
	ft_fill_win(core, 14);
	pthread_mutex_lock(&core->mut);
	while (i < MEM_SIZE)
	{
		mvprintw(r, c, "%02x ", core->arena[i]);
		i++;
		if (i % 64 == 0)
		{
			c = 3;
			r++;
		}
		else
			c += 3;
	}
	pthread_mutex_unlock(&core->mut);
}
