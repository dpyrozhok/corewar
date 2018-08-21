//
// Created by Pavlo OPANASENKO on 8/15/18.
//

#include "corewar.h"
#include "ncurs.h"

void    ft_06_opcode(t_core *core, t_champ *champ) {
	int *arg;
	int pc;
	int *codage;

	pc = champ->cars->pos % MEM_SIZE;
	codage = ft_get_codage(core, champ);
	arg = ft_get_args(core, champ, codage);
	if (codage[0] == IND_CODE)
		arg[0] = ft_read_4(core, (arg[0] % IDX_MOD + pc - 1) % MEM_SIZE);
	if (codage[1] == IND_CODE)
		arg[1] = ft_read_4(core, (arg[1] % IDX_MOD + pc - 1) % MEM_SIZE);
	if (ft_check_cod_and_arg(champ, codage, arg) && arg[2] < 17 && arg[2] > 0) {
        if (codage[0] == REG_CODE)
            arg[0] = champ->cars->reg[arg[0] - 1];
        if (codage[1] == REG_CODE)
            arg[1] = champ->cars->reg[arg[1] - 1];
		champ->cars->reg[arg[2] - 1] = (unsigned int)(arg[0] & arg[1]);
		champ->cars->carry = 1;
	} else
		champ->cars->carry = 0;
}

void    ft_07_opcode(t_core *core, t_champ *champ) {
	int *arg;
	int pc;
	int *codage;

	pc = champ->cars->pos % MEM_SIZE;
	codage = ft_get_codage(core, champ);
	arg = ft_get_args(core, champ, codage);
	if (codage[0] == IND_CODE)
		arg[0] = ft_read_4(core, (arg[0] % IDX_MOD + pc - 1) % MEM_SIZE);
	if (codage[1] == IND_CODE)
		arg[1] = ft_read_4(core, (arg[1] % IDX_MOD + pc - 1) % MEM_SIZE);
	if (ft_check_cod_and_arg(champ, codage, arg) && arg[2] < 17 && arg[2] > 0) {
        if (codage[0] == REG_CODE)
            arg[0] = champ->cars->reg[arg[0] - 1];
        if (codage[1] == REG_CODE)
            arg[1] = champ->cars->reg[arg[1] - 1];
		champ->cars->reg[arg[2] - 1] = (unsigned int)(arg[0] | arg[1]);
		champ->cars->carry = 1;
	} else
		champ->cars->carry = 0;
}

void    ft_08_opcode(t_core *core, t_champ *champ) {
	int *arg;
	int pc;
	int *codage;

	pc = champ->cars->pos % MEM_SIZE;
	codage = ft_get_codage(core, champ);
	arg = ft_get_args(core, champ, codage);
	if (codage[0] == 3)
		arg[0] = ft_read_4(core, (arg[0] % IDX_MOD + pc - 1) % MEM_SIZE);
	if (codage[1] == 3)
		arg[1] = ft_read_4(core, (arg[1] % IDX_MOD + pc - 1) % MEM_SIZE);
	if (ft_check_cod_and_arg(champ, codage, arg) && arg[2] < 17 && arg[2] > 0) {
        if (codage[0] == REG_CODE)
            arg[0] = champ->cars->reg[arg[0] - 1];
        if (codage[1] == REG_CODE)
            arg[1] = champ->cars->reg[arg[1] - 1];
		champ->cars->reg[arg[2] - 1] = (unsigned int)(arg[0] ^ arg[1]);
		champ->cars->carry = 1;
	} else
		champ->cars->carry = 0;
}

void    ft_09_opcode(t_core *core, t_champ *champ) {
	int shift;
	int r,c;

	if (champ->cars->carry) {
		shift = ft_read_2(core, champ->cars->pos % MEM_SIZE);
		champ->cars->pos = (champ->cars->pos + shift - 1) % MEM_SIZE;
		if (core->v)
		{
			r = 3 + ((champ->cars->pos%MEM_SIZE)/64)%64;
			c = 3 + (3*((champ->cars->pos%MEM_SIZE)%64))%192;
			attron(COLOR_PAIR(champ->cc));
			// attron(COLOR_PAIR(core->a[champ->cars->pos]));
			attron(A_REVERSE);
			attron(A_BOLD);
			mvprintw(r, c, "%02x", core->arena[champ->cars->pos%MEM_SIZE]);
			attroff(A_BOLD);
			attroff(A_REVERSE);
			// attroff(COLOR_PAIR(core->a[champ->cars->pos]));
			attroff(COLOR_PAIR(champ->cc));
			ft_memset(core->a+1 + champ->cars->pos%MEM_SIZE, champ->cc, 1);
		}
	}
	else
		champ->cars->pos += 2;
}

void    ft_10_opcode(t_core *core, t_champ *champ) {
	int *arg;
	int pc;
	int *codage;

	pc = champ->cars->pos % MEM_SIZE;
	codage = ft_get_codage(core, champ);
	arg = ft_get_args(core, champ, codage);
	if (codage[0] == 3)
		arg[0] = ft_read_4(core, (arg[0] % IDX_MOD + pc - 1) % MEM_SIZE);
	if (ft_check_cod_and_arg(champ, codage, arg)) {
        if (codage[0] == REG_CODE)
            arg[0] = champ->cars->reg[arg[0] - 1];
        if (codage[1] == REG_CODE)
            arg[1] = champ->cars->reg[arg[1] - 1];
		champ->cars->reg[arg[2] - 1] = (unsigned int)ft_read_4(core, ((arg[0] + arg[1]) % IDX_MOD + pc - 1 ) % MEM_SIZE);
    }
}
