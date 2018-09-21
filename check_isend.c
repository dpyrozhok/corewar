#include "corewar.h"
#include "ncurs.h"

void	ft_check_cars(t_core *core)
{
	t_car	*tmp;

	tmp = core->cars;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->state)
		{
			if (!tmp->live)
			{
				tmp->state = 0;
				core->qt_car--;
				if (core->vis)
					ft_vcars_check(core, tmp);
			}
			else
				tmp->live = 0;
		}
		tmp = tmp->prev;
	}
}

void	ft_make_check(t_core *core)
{
	t_champ	*champ;
	int		flag;
	int     a;

	flag = 0;
	a = 0;
	core->qt_check++;
	champ = core->champs;
	if (core->vis)
		ft_breakdown(core);
	pthread_mutex_lock(&core->mut);
	while (champ)
	{
		a += champ->all_live;
		champ->s_live = 0;
		champ->all_live = 0;
		champ = champ->next;
	}
	if (a >= NBR_LIVE)
		flag = 1;
	if (flag || core->qt_check == MAX_CHECKS)
	{
		core->qt_check = 0;
		core->c_to_die -= CYCLE_DELTA;
	}
	pthread_mutex_unlock(&core->mut);
	ft_check_cars(core);
}
