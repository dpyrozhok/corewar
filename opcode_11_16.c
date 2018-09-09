//
// Created by Pavlo OPANASENKO on 8/13/18.
//
#include "corewar.h"
#include "ncurs.h"

void    ft_11_opcode(t_core *core, t_car *car) {
	t_champ *champ;
	int *arg;
	int pc;
	int *codage;
	int ag,pos,r,c;

	pc = car->pos % MEM_SIZE;
	codage = ft_get_codage(core, car);
	arg = ft_get_args(core, car, codage);
	if (codage[1] == 3)
		arg[1] = ft_read_4(core, (arg[1] + pc - 1) % IDX_MOD);
	if (ft_check_cod_and_arg(car, codage, arg))
	{
		if (codage[1] == REG_CODE)
			arg[1] = (int)car->reg[arg[1] - 1];
		if (codage[2] == REG_CODE)
			arg[2] = (int)car->reg[arg[2] - 1];
		ft_put_4(core, car->reg[arg[0] - 1], ((arg[1] + arg[2]) % IDX_MOD + pc) % MEM_SIZE);
		if (core->v)
		{
			champ = ft_get_champ(core, car->id);
			ag = car->reg[arg[0] - 1];
			pos = ((arg[1] + arg[2]) % IDX_MOD + pc) % MEM_SIZE;
			if (pos < 0)
				pos = MEM_SIZE + pos;
			car->rp = pos;
			car->sw = 1;
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

void    ft_12_opcode(t_core *core, t_car *car) {
	int new_pc;

	new_pc = ft_read_2(core, car->pos % MEM_SIZE);
	new_pc = (new_pc % IDX_MOD + car->pos) % MEM_SIZE;
	if (new_pc < 0)
		new_pc = MEM_SIZE + new_pc;
	ft_copy_car(core, car, new_pc);
	car->pos += 2;
}

void    ft_13_opcode(t_core *core, t_car *car) {
	int *arg;
	int pc;
	int *codage;

	pc = car->pos % MEM_SIZE;
	codage = ft_get_codage(core, car);
	arg = ft_get_args(core, car, codage);
	if (codage[0] == 3)
		arg[0] = ft_read_4(core, arg[0] + pc);
	if (ft_check_cod_and_arg(car, codage, arg)) {
		car->reg[arg[1] - 1] = (unsigned int)arg[0];
		if (car->reg[arg[1] - 1] == 0)
			car->carry = 1;
		else
			car->carry = 0;
	}
}

void    ft_14_opcode(t_core *core, t_car *car) {
	int *arg;
	int pc;
	int *codage;

	pc = car->pos % MEM_SIZE;
	codage = ft_get_codage(core, car);
	arg = ft_get_args(core, car, codage);
	if (codage[0] == 3)
		arg[0] = ft_read_4(core, arg[0] % IDX_MOD + pc);
	if (ft_check_cod_and_arg(car, codage, arg)) {
		car->reg[arg[2] - 1] = (unsigned int) ft_read_4(core, ((arg[0] + arg[1]) + pc - 1) % MEM_SIZE);
		if (car->reg[arg[2] - 1] == 0)
			car->carry = 1;
		else
			car->carry = 0;
	}
}

void    ft_15_opcode(t_core *core, t_car *car) {
	int new_pc;

	new_pc = ft_read_2(core, car->pos % MEM_SIZE);
	new_pc = (new_pc + car->pos) % MEM_SIZE;
	if (new_pc < 0)
		new_pc = MEM_SIZE + new_pc;
	ft_copy_car(core, car, new_pc);
	car->pos += 2;
}

void    ft_16_opcode(t_core *core, t_car *car) {
    int *arg;
    int *codage;

    codage = ft_get_codage(core, car);
    arg = ft_get_args(core, car, codage);
    arg[0] = (int)car->reg[arg[0] - 1];
}