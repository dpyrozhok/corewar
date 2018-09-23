/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opcode_1_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 20:29:31 by popanase          #+#    #+#             */
/*   Updated: 2018/09/24 00:53:19 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/ft_visual.h"

void	ft_01_opcode(t_core *core, t_car *car)
{
	int		id;
	t_champ	*champ;

	id = ft_read_4(core, car->pos % MEM_SIZE);
	champ = ft_get_champ(core, id);
	if (champ)
	{
		champ->last_live = core->cycle;
		champ->s_live++;
		champ->all_live++;
		if (!core->vis && core->dump == -1)
			ft_printf("\nA process shows that player %i (%s) is alive", \
				champ->id, champ->name);
		core->winner_id = champ->id;
	}
	else
	{
		champ = ft_get_champ(core, car->id);
		champ->all_live++;
	}
	car->live = 1;
	car->pos += 4;
}

void	ft_02_opcode(t_core *core, t_car *car)
{
	int		*arg;
	int		pc;
	int		*codage;

	pc = car->pos % MEM_SIZE;
	codage = ft_get_codage(core, car);
	arg = ft_get_args(core, car, codage);
	if (codage[0] == 3)
		arg[0] = ft_read_4(core, (arg[0] % IDX_MOD + pc - 1) % MEM_SIZE);
	if (ft_check_cod_and_arg(car, codage, arg))
	{
		car->reg[arg[1] - 1] = (unsigned int)arg[0];
		if (arg[0] == 0)
			car->carry = 1;
		else
			car->carry = 0;
	}
	free(arg);
	free(codage);
}

void	ft_03_opcode(t_core *core, t_car *car)
{
	int		pc;
	int		*arg;
	int		*codage;

	pc = car->pos % MEM_SIZE;
	codage = ft_get_codage(core, car);
	arg = ft_get_args(core, car, codage);
	if (ft_check_cod_and_arg(car, codage, arg))
	{
		if (codage[1] != IND_CODE)
			car->reg[arg[1] - 1] = car->reg[arg[0] - 1];
		else
		{
			ft_put_4(core, car->reg[arg[0] - 1], \
				(arg[1] % IDX_MOD + pc) % MEM_SIZE);
			if (core->vis)
				ft_vcars_on(core, car, car->reg[arg[0] - 1], \
					(arg[1] % IDX_MOD + pc) % MEM_SIZE);
		}
	}
	free(arg);
	free(codage);
}

void	ft_04_opcode(t_core *core, t_car *car)
{
	int		*arg;
	int		*codage;

	codage = ft_get_codage(core, car);
	arg = ft_get_args(core, car, codage);
	if (ft_check_cod_and_arg(car, codage, arg))
	{
		car->reg[arg[2] - 1] = car->reg[arg[0] - 1] + car->reg[arg[1] - 1];
		if (car->reg[arg[2] - 1] == 0)
			car->carry = 1;
		else
			car->carry = 0;
	}
	free(arg);
	free(codage);
}

void	ft_05_opcode(t_core *core, t_car *car)
{
	int		*arg;
	int		*codage;

	codage = ft_get_codage(core, car);
	arg = ft_get_args(core, car, codage);
	if (ft_check_cod_and_arg(car, codage, arg))
	{
		car->reg[arg[2] - 1] = car->reg[arg[0] - 1] - car->reg[arg[1] - 1];
		if (car->reg[arg[2] - 1] == 0)
			car->carry = 1;
		else
			car->carry = 0;
	}
	free(arg);
	free(codage);
}
