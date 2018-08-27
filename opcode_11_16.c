//
// Created by Pavlo OPANASENKO on 8/13/18.
//
#include "corewar.h"
#include "ncurs.h"

void    ft_11_opcode(t_core *core, t_champ *champ) {
	int *arg;
	int pc;
	int *codage;
	int ag,pos,r,c;

	pc = champ->cars->pos % MEM_SIZE;
	codage = ft_get_codage(core, champ);
	arg = ft_get_args(core, champ, codage);
	if (codage[1] == 3)
		arg[1] = ft_read_4(core, (arg[1] + pc - 1) % IDX_MOD);
	if (ft_check_cod_and_arg(champ, codage, arg))
	{
		if (codage[1] == REG_CODE)
			arg[1] = champ->cars->reg[arg[1] - 1];
		if (codage[2] == REG_CODE)
			arg[2] = champ->cars->reg[arg[2] - 1];
		ft_put_4(core, champ->cars->reg[arg[0] - 1], ((arg[1] + arg[2]) % IDX_MOD + pc) % MEM_SIZE);

		if (core->v)
		{
			ag = champ->cars->reg[arg[0] - 1];
			pos = ((arg[1] + arg[2]) % IDX_MOD + pc  ) % MEM_SIZE;
			champ->cars->rp = pos;
			champ->cars->sw = 1;
			r = 3+((pos%MEM_SIZE)/64)%64;
			c = 3+(3*((pos%MEM_SIZE)%64))%192;
			attron(A_BOLD);
			attron(COLOR_PAIR(champ->c));
			mvprintw(r,c,"%02x", (unsigned char)(ag >> 24));
			ft_memset(core->a + (pos%MEM_SIZE), champ->c, 1);
			pos++;
			r = 3+((pos%MEM_SIZE)/64)%64;
			c = 3+(3*((pos%MEM_SIZE)%64))%192;
			// c += 3;
			// c %= 64; ?? нужно ли
			// r += c/64; 
			mvprintw(r,c,"%02x", (unsigned char)(ag >> 16 & 255));
			ft_memset(core->a + (pos%MEM_SIZE), champ->c, 1);
			pos++;
			r = 3+((pos%MEM_SIZE)/64)%64;
			c = 3+(3*((pos%MEM_SIZE)%64))%192;
			// c += 3;
			mvprintw(r,c,"%02x", (unsigned char)(ag >> 8 & 255));
			ft_memset(core->a + (pos%MEM_SIZE), champ->c, 1);
			pos++;
			r = 3+((pos%MEM_SIZE)/64)%64;
			c = 3+(3*((pos%MEM_SIZE)%64))%192;
			// c += 3;
			mvprintw(r,c,"%02x", (unsigned char)(ag & 255));
			ft_memset(core->a + (pos%MEM_SIZE), champ->c, 1);
			attroff(COLOR_PAIR(champ->c));
			attroff(A_BOLD);
			// ft_memset(core->a+1 + pos%MEM_SIZE, champ->c, 4);
		}
	}
}

void    ft_12_opcode(t_core *core, t_champ *champ) {
	int new_pc;

	new_pc = ft_read_2(core, champ->cars->pos % MEM_SIZE);
	new_pc = (new_pc % IDX_MOD + champ->cars->pos) % MEM_SIZE;
	ft_copy_car(core, champ, champ->cars, new_pc);
	champ->cars->pos += 2;
}

void    ft_13_opcode(t_core *core, t_champ *champ) {
	int *arg;
	int pc;
	int *codage;

	pc = champ->cars->pos % MEM_SIZE;
	codage = ft_get_codage(core, champ);
	arg = ft_get_args(core, champ, codage);
	if (codage[0] == 3)
		arg[0] = ft_read_4(core, arg[0] + pc);
	if (ft_check_cod_and_arg(champ, codage, arg)) {
		champ->cars->reg[arg[1] - 1] = (unsigned int)arg[0];
		champ->cars->carry = 1;
	} else
		champ->cars->carry = 0;
}

void    ft_14_opcode(t_core *core, t_champ *champ) {
	int *arg;
	int pc;
	int *codage;

	pc = champ->cars->pos % MEM_SIZE;
	codage = ft_get_codage(core, champ);
	arg = ft_get_args(core, champ, codage);
	if (codage[0] == 3)
		arg[0] = ft_read_4(core, arg[0] % IDX_MOD + pc);
	if (ft_check_cod_and_arg(champ, codage, arg))
		champ->cars->reg[arg[2] - 1] = (unsigned int)ft_read_4(core, ((arg[0] + arg[1]) + pc) % MEM_SIZE);
}

void    ft_15_opcode(t_core *core, t_champ *champ) {
	int new_pc;

	new_pc = ft_read_2(core, champ->cars->pos % MEM_SIZE);
	new_pc = (new_pc + champ->cars->pos) % MEM_SIZE;
    ft_copy_car(core, champ, champ->cars, new_pc);
	champ->cars->pos += 2;
}