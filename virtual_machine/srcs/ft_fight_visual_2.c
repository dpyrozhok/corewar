/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fight_visual_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 21:28:01 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/24 00:52:47 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/ft_visual.h"

void	ft_key_pause(t_core *p, int ch)
{
	if (ch == ' ')
	{
		pthread_mutex_lock(&(p)->mut);
		if (!(p)->pas && (p)->microsec)
			(p)->pas = 1;
		else if ((p)->pas && (p)->microsec)
			(p)->pas = 0;
		pthread_mutex_unlock(&(p)->mut);
	}
}

void	ft_key_speedup(t_core *p)
{
	pthread_mutex_lock(&(p)->mut);
	if (!(p)->pas && (p)->microsec)
	{
		if ((p)->microsec > 1000)
			(p)->microsec /= 10;
		else
		{
			(p)->microsec = 0;
			pthread_mutex_unlock(&(p)->mut);
			pthread_exit(NULL);
		}
	}
	pthread_mutex_unlock(&(p)->mut);
}

void	ft_key_speeddown(t_core *p)
{
	pthread_mutex_lock(&(p)->mut);
	if (!(p)->pas && (p)->microsec && (p)->microsec < 1000000)
		(p)->microsec *= 10;
	pthread_mutex_unlock(&(p)->mut);
}

void	ft_key_reset(t_core *p)
{
	pthread_mutex_lock(&(p)->mut);
	if (!(p)->pas)
		(p)->microsec = 100000;
	pthread_mutex_unlock(&(p)->mut);
}

void	ft_key_finish(t_core *p)
{
	pthread_mutex_lock(&(p)->mut);
	if ((p)->microsec == -1)
	{
		(p)->microsec = -2;
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(&(p)->mut);
}
