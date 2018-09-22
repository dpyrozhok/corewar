/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_ft_init_win.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 18:28:45 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/22 18:29:38 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurs.h"

static void	ft_init_colorset(void)
{
	init_pair(1, TITLE_FG, TITLE_BG);
	init_pair(2, BORDER_L_FG, BORDER_L_BG);
	init_pair(3, BORDER_R_FG, BORDER_R_BG);
	init_pair(4, DEFAULT_FG, DEFAULT_BG);
	init_pair(20, BOT_A_FG, BOT_BG);
	init_pair(21, BOT_B_FG, BOT_BG);
	init_pair(22, BOT_C_FG, BOT_BG);
	init_pair(23, BOT_D_FG, BOT_BG);
	init_pair(30, CAR_FG, BOT_A_FG);
	init_pair(31, CAR_FG, BOT_B_FG);
	init_pair(32, CAR_FG, BOT_C_FG);
	init_pair(33, CAR_FG, BOT_D_FG);
}

static void	*ft_promo_audio(void *ptr)
{
	if (!ptr)
		ft_play_sound("Track.wav");
	pthread_exit(NULL);
	return (NULL);
}

void	ft_init_win(t_core *core)
{
	pthread_t	thread_promo;

	initscr();
	if (LINES < 69 || COLS < 254)
	{
		endwin();
		ft_printf("Resize window to min %d cols and %d rows. Currently %d cols "
			"and %d rows\n", 254, 69, COLS, LINES);
		exit(0);
	}
	if (has_colors() == FALSE)
	{
		endwin();
		ft_printf("Your terminal does not support color\n");
		exit(0);
	}
	start_color();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	pthread_create(&thread_promo, NULL, ft_promo_audio, NULL);
	pthread_detach(thread_promo);
	ft_init_colorset();
	ft_fill_screen(core);
}
