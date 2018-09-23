/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 18:30:13 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/24 00:52:53 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_visual.h"

static void	ft_init_border_left(t_border *border)
{
	border->height = 67;
	border->width = 196;
	border->starty = 1;
	border->startx = 0;
}

static void	ft_init_border_right(t_border *border)
{
	border->height = 67;
	border->width = 56;
	border->starty = 1;
	border->startx = 197;
}

static void	ft_create_border(t_border *border, t_core *core)
{
	int		x;
	int		y;
	int		w;
	int		h;

	pthread_mutex_lock(&core->mut);
	x = border->startx;
	y = border->starty;
	w = border->width;
	h = border->height;
	mvaddch(y, x, BORDER_TL);
	mvaddch(y, x + w, BORDER_TR);
	mvaddch(y + h, x, BORDER_BL);
	mvaddch(y + h, x + w, BORDER_BR);
	mvhline(y, x + 1, BORDER_TS, w - 1);
	mvhline(y + h, x + 1, BORDER_BS, w - 1);
	mvvline(y + 1, x, BORDER_LS, h - 1);
	mvvline(y + 1, x + w, BORDER_RS, h - 1);
	pthread_mutex_unlock(&core->mut);
}

void		ft_fill_screen(t_core *core)
{
	t_border	border_left;
	t_border	border_right;

	ft_init_border_left(&border_left);
	ft_init_border_right(&border_right);
	pthread_mutex_lock(&core->mut);
	attron(COLOR_PAIR(1) | A_BOLD);
	mvprintw(0, 120, "C O R E W A R");
	attroff(COLOR_PAIR(1));
	pthread_mutex_unlock(&core->mut);
	attron(COLOR_PAIR(2) | A_REVERSE);
	ft_create_border(&border_left, core);
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(3));
	ft_create_border(&border_right, core);
	attroff(COLOR_PAIR(3) | A_REVERSE);
	pthread_mutex_lock(&core->mut);
	attron(COLOR_PAIR(4));
	mvprintw(32, 89, "MAKE PEACE NOT WAR");
	mvprintw(33, 85, "PRESS ANY KEY TO CONTINUE");
	attroff(COLOR_PAIR(4) | A_BOLD);
	refresh();
	pthread_mutex_unlock(&core->mut);
}
