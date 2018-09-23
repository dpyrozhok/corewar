/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight_visual_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 21:27:48 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/23 11:30:43 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "ncurs.h"

void	ft_key_terminate(t_core *p)
{
	pthread_mutex_lock(&(p)->mut);
	if ((p)->microsec)
	{
		endwin();
		exit(0);
	}
	pthread_mutex_unlock(&(p)->mut);
}

void	*ft_fight_key(void *ptr)
{
	int		ch;
	t_core	*p;

	p = (t_core*)ptr;
	while ((ch = getch()))
	{
		ft_key_finish(p);
		if (ch == 27)
			ft_key_terminate(p);
		else if (ch == KEY_F(1))
			ft_key_reset(p);
		else if (ch == KEY_UP)
			ft_key_speedup(p);
		else if (ch == KEY_DOWN)
			ft_key_speeddown(p);
		else
			ft_key_pause(p, ch);
	}
	return (NULL);
}

void	*ft_fight_audio(void *ptr)
{
	if (!ptr)
	{
		// SDL_Quit();
		ft_play_sound("Track1.wav");
	}
	pthread_exit(NULL);
	return (NULL);
}

void	ft_is_paused(t_core *core)
{
	while (core->pas)
	{
	ft_resize(core);
		pthread_mutex_lock(&core->mut);
		attron(A_BOLD);
		mvprintw(3, 200, "** PAUSED ** ");
		attroff(A_BOLD);
		refresh();
		pthread_mutex_unlock(&core->mut);
		usleep(100000);
	}
}

void	ft_fight_visual(t_core *core)
{
	int			ch;
	pthread_t	thread_id;
	pthread_t	thread_id2;

	// if (LINES < 69 || COLS < 254)
		// while (true)
			// continue ;
	// ft_play_sound("Track1.wav");
	pthread_create(&thread_id, NULL, ft_fight_key, (void*)core);
	pthread_detach(thread_id);
	pthread_create(&thread_id2, NULL, ft_fight_audio, NULL);
	pthread_detach(thread_id2);
	ft_vfight_run(core, NULL);
	core->fin = 1;
	ft_draw(core);
	ft_breakdown(core);
	if (core->microsec)
		core->microsec = -1;
	if (core->microsec)
		while (core->microsec > -2)
			continue ;
	else
		while ((ch = getch()) != 27)
			continue ;
	endwin();
}
