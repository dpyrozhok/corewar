/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opcode_11_15.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 20:33:19 by popanase          #+#    #+#             */
/*   Updated: 2018/09/24 00:53:13 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/ft_visual.h"

void	ft_11_opcode(t_core *core, t_car *car)
{
	int		pc;
	int		*arg;
	int		*codage;

	pc = car->pos % MEM_SIZE;
	codage = ft_get_codage(core, car);
	arg = ft_get_args(core, car, codage);
	if (codage[1] == IND_CODE)
		arg[1] = ft_read_4(core, (arg[1] % IDX_MOD + pc - 1) % MEM_SIZE);
	if (ft_check_cod_and_arg(car, codage, arg))
	{
		if (codage[1] == REG_CODE)
			arg[1] = (int)car->reg[arg[1] - 1];
		if (codage[2] == REG_CODE)
			arg[2] = (int)car->reg[arg[2] - 1];
		ft_put_4(core, car->reg[arg[0] - 1], \
			((arg[1] + arg[2]) % IDX_MOD + pc) % MEM_SIZE);
		if (core->vis)
			ft_vcars_on(core, car, car->reg[arg[0] - 1], \
				((arg[1] + arg[2]) % IDX_MOD + pc) % MEM_SIZE);
	}
	free(arg);
	free(codage);
}

void	ft_12_opcode(t_core *core, t_car *car)
{
	int		new_pc;

	new_pc = ft_read_2(core, car->pos % MEM_SIZE);
	new_pc = (new_pc % IDX_MOD + car->pos) % MEM_SIZE;
	if (new_pc < 0)
		new_pc = MEM_SIZE + new_pc;
	ft_copy_car(core, car, new_pc);
	car->pos += 2;
}

void	ft_13_opcode(t_core *core, t_car *car)
{
	int		*arg;
	int		pc;
	int		*codage;

	pc = car->pos % MEM_SIZE;
	codage = ft_get_codage(core, car);
	arg = ft_get_args(core, car, codage);
	if (codage[0] == IND_CODE)
		arg[0] = ft_read_4(core, (arg[0] + pc - 1) % MEM_SIZE);
	if (ft_check_cod_and_arg(car, codage, arg))
	{
		car->reg[arg[1] - 1] = (unsigned int)arg[0];
		if (car->reg[arg[1] - 1] == 0)
			car->carry = 1;
		else
			car->carry = 0;
	}
	free(arg);
	free(codage);
}

void	ft_14_opcode(t_core *core, t_car *car)
{
	int		*arg;
	int		pc;
	int		*codage;

	pc = car->pos % MEM_SIZE;
	codage = ft_get_codage(core, car);
	arg = ft_get_args(core, car, codage);
	if (codage[0] == IND_CODE)
		arg[0] = ft_read_4(core, (arg[0] % IDX_MOD + pc - 1) % MEM_SIZE);
	if (ft_check_cod_and_arg(car, codage, arg))
	{
		if (codage[0] == REG_CODE)
			arg[0] = (int)car->reg[arg[0] - 1];
		if (codage[1] == REG_CODE)
			arg[1] = (int)car->reg[arg[1] - 1];
		car->reg[arg[2] - 1] = (unsigned int)ft_read_4(core, \
			((arg[0] + arg[1]) + pc - 1) % MEM_SIZE);
		if (car->reg[arg[2] - 1] == 0)
			car->carry = 1;
		else
			car->carry = 0;
	}
	free(arg);
	free(codage);
}

void	ft_15_opcode(t_core *core, t_car *car)
{
	int		new_pc;

	new_pc = ft_read_2(core, car->pos % MEM_SIZE);
	new_pc = (new_pc + car->pos) % MEM_SIZE;
	if (new_pc < 0)
		new_pc = MEM_SIZE + new_pc;
	ft_copy_car(core, car, new_pc);
	car->pos += 2;
}
