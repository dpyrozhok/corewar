#include "corewar.h"
#include "ncurs.h"

void	ft_get_n_car_value(t_core *core, t_car *car)
{
	t_champ	*champ;
	int		r;
	int		c;

	if (core->arena[car->pos % MEM_SIZE] > 0 && core->arena[car->pos % MEM_SIZE] < 17)
	{
		car->opcode = core->arena[car->pos % MEM_SIZE];
		car->cycle = op_tab[car->opcode - 1].cycle;
	}
	else
		car->opcode = 0;
	if (core->v)
	{
		pthread_mutex_lock(&core->m);
		champ = ft_get_champ(core, car->id);
		r = 3 + ((car->pos % MEM_SIZE) / 64) % 64;
		c = 3 + (3 * ((car->pos % MEM_SIZE) % 64)) % 192;
		if (car->opcode == 1 && car->id == ft_read_4(core, car->pos % MEM_SIZE)) // champ_id == opcode_id
			attron(A_BOLD | COLOR_PAIR(champ->cc));
		else
			attron(A_REVERSE | COLOR_PAIR(core->a[car->pos%MEM_SIZE]));
		mvprintw(r, c, "%02x", core->arena[car->pos % MEM_SIZE]);
		if (car->opcode == 1 && car->id == ft_read_4(core, car->pos % MEM_SIZE)) // champ_id == opcode_id
			attroff(A_BOLD | COLOR_PAIR(champ->cc));
		else
			attroff(A_REVERSE | COLOR_PAIR(core->a[car->pos % MEM_SIZE]));
		pthread_mutex_unlock(&core->m);
	}
}

void	ft_touch_car(t_core *core, t_car *car)
{
	if (car->cycle == -1)
		ft_get_n_car_value(core, car);
	if (car->cycle < 2)
	{
		if (core->v)
			ft_vcars_norev(core, car);
		if (car->opcode > 0 && car->opcode < 17)
		{
			if (core->v && car->sw)
				ft_vcars_off(core, car);
			ft_opcode_switcher(core, car);
		}
		car->cycle = -1;
		car->pos++;
		if (core->v)
			ft_vcars_rev(core, car);
	}
	else
		car->cycle--;
}

void	ft_key_pause(t_core *p, int ch)
{
	if (ch == ' ')
	{
		pthread_mutex_lock(&(p)->m);
		if (!(p)->p && (p)->t)
			(p)->p = 1;
		else if ((p)->p && (p)->t)
			(p)->p = 0;
		pthread_mutex_unlock(&(p)->m);
	}
}

void	ft_key_speedup(t_core *p)
{
	pthread_mutex_lock(&(p)->m);
	if (!(p)->p && (p)->t)
	{
		if ((p)->t  > 1000)
			(p)->t /= 10;
		else
		{
			(p)->t = 0;
			pthread_mutex_unlock(&(p)->m);
			pthread_exit(NULL);
		}
	}
	pthread_mutex_unlock(&(p)->m);
}

void	ft_key_speeddown(t_core *p)
{
	pthread_mutex_lock(&(p)->m);
	if (!(p)->p && (p)->t && (p)->t < 1000000)
		(p)->t *= 10;
	pthread_mutex_unlock(&(p)->m);
}

void	ft_key_reset(t_core *p)
{
	pthread_mutex_lock(&(p)->m);
	if (!(p)->p)
		(p)->t = 100000;
	pthread_mutex_unlock(&(p)->m);
}

void	ft_key_finish(t_core *p)
{
	pthread_mutex_lock(&(p)->m);
	if ((p)->t == -1)
	{
		(p)->t = -2;
		pthread_exit(NULL);
	}	
	pthread_mutex_unlock(&(p)->m);
}

void	ft_key_terminate(t_core *p)
{
	pthread_mutex_lock(&(p)->m);
	if ((p)->t)
	{
		endwin();
		exit(121);
	}
	pthread_mutex_unlock(&(p)->m);
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
		SDL_Quit();
		ft_play_sound("Track1.wav");
	}
	pthread_exit(NULL);
	return (NULL);
}

void	ft_is_paused(t_core *core)
{
	while (core->p)
	{
		pthread_mutex_lock(&core->m);
		attron(A_BOLD);
		mvprintw(3, 200, "** PAUSED ** ");
		attroff(A_BOLD);
		refresh();
		pthread_mutex_unlock(&core->m);
		usleep(100000);
	}
}

void	ft_vfight_run(t_core *core, t_car *tmp)
{
	while (core->qt_car > 0)
	{
		tmp = core->cars;
		core->cycle++;
		while (tmp->next)
			tmp = tmp->next;
		while (tmp)
		{
			if (tmp->state)
				ft_touch_car(core, tmp);
			tmp = tmp->prev;
		}
		ft_draw(core);
		if (core->t)
			usleep(core->t);
		ft_is_paused(core);
		if (core->cycle == core->c_to_die + core->last_check \
			|| core->c_to_die <= 0)
		{
			ft_make_check(core);
			core->last_check = core->cycle;
		}
	}
}

void	ft_fight_visual(t_core *core)
{
	int			ch;
	pthread_t	thread_id;
	pthread_t	thread_id2;

	pthread_create(&thread_id, NULL, ft_fight_key, (void*)core);
	pthread_detach(thread_id);
	pthread_create(&thread_id2, NULL, ft_fight_audio, NULL);
	pthread_detach(thread_id2);
	ft_vfight_run(core, NULL);
	core->f = 1;
	ft_draw(core);
	ft_breakdown(core);
	if (core->t)
		core->t = -1;
	if (core->t)
		while (core->t > -2)
			continue ;
	else
		while ((ch = getch()) != 27)
			continue ;
	endwin();
}

void	ft_fight(t_core *core, t_car *tmp)
{
	while (core->qt_car > 0)
	{
		tmp = core->cars;
		core->cycle++;
		while (tmp->next)
			tmp = tmp->next;
		while (tmp)
		{
			if (tmp->state)
				ft_touch_car(core, tmp);
			tmp = tmp->prev;
		}
		if (core->dump != -1 && core->dump == core->cycle)
		{
			ft_dump(core);
			//ft_free(core); // нужно ли?
			exit(0);
		}
		if (core->cycle == core->c_to_die + core->last_check \
			|| core->c_to_die <= 0)
		{
			ft_make_check(core);
			core->last_check = core->cycle;
		}
	}
}

void	ft_start_fight(t_core *core)
{
	if (core->v)
		ft_fight_visual(core);
	else
		ft_fight(core, NULL);
}
