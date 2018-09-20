//
// Created by Pavlo OPANASENKO on 8/17/18.
//

#include "corewar.h"
#include "ncurs.h"

void	ft_01_opcode(t_core *core, t_car *car)
{
	t_champ	*champ;

	champ = ft_get_champ(core, car->id);
	if (car->id == ft_read_4(core, car->pos % MEM_SIZE))
	{
		champ->last_live = core->cycle;
		champ->s_live++;
		if (!core->v && core->dump == -1)
			ft_printf("\nPlayer %i (%s) is said to be alive", \
				champ->num, champ->name);
		core->winner_id = champ->id;
	}
	champ->all_live++;
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
		if (codage[1] != 3)
			car->reg[arg[1] - 1] = car->reg[arg[0] - 1];
		else
		{
			ft_put_4(core, car->reg[arg[0] - 1], \
				(arg[1] % IDX_MOD + pc) % MEM_SIZE);
			if (core->v)
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
