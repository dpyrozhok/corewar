/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 11:50:26 by popanase          #+#    #+#             */
/*   Updated: 2018/09/24 00:51:01 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/ft_check.h"

static void	ft_init_core(t_core *core, int ac, char **av)
{
	core->dump = -1;
	core->col_mod = 0;
	core->last_break = 0;
	core->microsec = 100000;
	core->pas = 0;
	core->fin = 0;
	core->resz = 0;
	ft_check_args(ac, av, core, 0);
	core->arena = (unsigned char *)ft_memalloc(sizeof(unsigned char) * \
		MEM_SIZE);
	core->a_col = (unsigned char *)ft_memalloc(sizeof(unsigned char) * \
		MEM_SIZE);
	core->init_nub = 0;
	core->c_to_die = CYCLE_TO_DIE;
}

static void	ft_read_champ(t_core *core, int ac, char **av)
{
	int	i;
	int flag;
	int	fd;
	int	n;

	i = 1;
	flag = 0;
	n = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			flag = 1;
			n = ft_atoi(av[++i]);
		}
		fd = open(av[i], O_RDONLY);
		if (fd != -1)
		{
			if (!flag)
				n = ++core->init_nub;
			flag = 0;
			ft_parse_champion(core, fd, n);
		}
		i++;
	}
}

static void	ft_free(t_core *core)
{
	t_champ	*champ;
	t_car	*car;

	while (core->champs)
	{
		free(core->champs->code);
		champ = core->champs->next;
		free(core->champs);
		core->champs = champ;
	}
	while (core->cars)
	{
		car = core->cars->next;
		free(core->cars);
		core->cars = car;
	}
	free(core->arena);
	free(core->a_col);
	free(core);
}

int			main(int ac, char **av)
{
	t_core	*core;

	core = (t_core *)ft_memalloc(sizeof(t_core));
	ft_init_core(core, ac, av);
	ft_read_champ(core, ac, av);
	if (!core->vis)
		ft_introduce(core);
	ft_place_champ(core);
	ft_start_fight(core);
	if (!core->vis)
		ft_winner_is(core);
	ft_free(core);
	return (0);
}
