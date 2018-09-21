/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcode_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 21:49:46 by popanase          #+#    #+#             */
/*   Updated: 2018/09/21 21:57:48 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_opcode_switcher(t_core *core, t_car *car)
{
	void (*f[16])(t_core *core, t_car *car) = {
			ft_01_opcode, ft_02_opcode, ft_03_opcode, ft_04_opcode, ft_05_opcode,
			ft_06_opcode, ft_07_opcode, ft_08_opcode, ft_09_opcode, ft_10_opcode,
			ft_11_opcode, ft_12_opcode, ft_13_opcode, ft_14_opcode, ft_15_opcode,
			ft_16_opcode};

    if (car->pos < 0)
        car->pos = MEM_SIZE + car->pos;
    f[car->opcode - 1](core, car);
}

t_champ	*ft_get_champ(t_core *core, int id)
{
	t_champ	*tmp;

	tmp = core->champs;
	while (tmp)
	{
		if (tmp->id == id)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int		ft_check_cod_and_arg(t_car *car, int const *cod, int const *arg)
{
	int		i;
	int		op;
	int		t_val;

	i = 0;
	op = car->opcode - 1;
	while (i < op_tab[op].qt_arg)
	{
		t_val = cod[i];
		if (t_val == IND_CODE)
			t_val = T_IND;
		if (!(t_val & op_tab[op].arg[i]))
			return (0);
		else if (cod[i] == REG_CODE)
		{
			if (!(arg[i] > 0 && arg[i] < 17))
				return (0);
		}
		i++;
	}
	return (1);
}

int		*ft_get_codage(t_core *core, t_car *car)
{
	int		*cod;
	int		op;

	op = car->opcode - 1;
	if (op_tab[op].codage)
	{
		car->pos++;
		cod = (int *)ft_memalloc(sizeof(int) * 4);
		cod[0] = (core->arena[car->pos % MEM_SIZE] & 192) >> 6;
		cod[1] = (core->arena[car->pos % MEM_SIZE] & 48) >> 4;
		cod[2] = (core->arena[car->pos % MEM_SIZE] & 12) >> 2;
		cod[3] = (core->arena[car->pos % MEM_SIZE] & 3);
		return (cod);
	}
	return (NULL);
}

int		*ft_get_args(t_core *core, t_car *car, int const *cod)
{
	int		*arg;
	int		i;

	i = 0;
	arg = (int *)ft_memalloc(sizeof(int) * op_tab[car->opcode - 1].qt_arg);
	while (i < op_tab[car->opcode - 1].qt_arg)
	{
		if (cod[i] == REG_CODE)
			arg[i] = ft_read_1(core, car->pos % MEM_SIZE);
		else if (cod[i] == DIR_CODE && op_tab[car->opcode - 1].lable)
			arg[i] = ft_read_2(core, car->pos % MEM_SIZE);
		else if (cod[i] == DIR_CODE && !op_tab[car->opcode - 1].lable)
			arg[i] = ft_read_4(core, car->pos % MEM_SIZE);
		else if (cod[i] == IND_CODE)
			arg[i] = ft_read_2(core, car->pos % MEM_SIZE);
		if (cod[i] == REG_CODE)
			car->pos += 1;
		else if ((cod[i] == DIR_CODE && op_tab[car->opcode - 1].lable) ||
			cod[i] == IND_CODE)
			car->pos += 2;
		else if (cod[i] == DIR_CODE && !op_tab[car->opcode - 1].lable)
			car->pos += 4;
		i++;
	}
	return (arg);
}
