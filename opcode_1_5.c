//
// Created by Pavlo OPANASENKO on 8/17/18.
//

#include "corewar.h"
#include "ncurs.h"

void    ft_01_opcode(t_core *core, t_champ *champ) {
	// int r,c;

	if (champ->id == ft_read_4(core, champ->cars->pos % MEM_SIZE)) {  // codage нету, а labelsize == 4, поєтому читаем четыре байта
		champ->s_live++;
		champ->last_live = core->cycle;
		core->winner_id = champ->id;  // условие кто последний сказал - тот и чемпион
	}
	champ->cars->live = 1; // каретка (процесс) жив в этом цикле
	champ->cars->pos += 4;
	/*
	if (core->v)
	{
		r = 3+((champ->cars->pos%MEM_SIZE)/64)%64;
		c = 3+(3*((champ->cars->pos%MEM_SIZE)%64))%192;
		attron(COLOR_PAIR(champ->c));
		// attron(COLOR_PAIR(core->a[champ->cars->pos]));
		attron(A_REVERSE);
		// attron(A_BOLD);
		mvprintw(r,c,"%02x", core->arena[champ->cars->pos%MEM_SIZE]);
		// attroff(A_BOLD);
		attroff(A_REVERSE);
		// attroff(COLOR_PAIR(core->a[champ->cars->pos]));
		attroff(COLOR_PAIR(champ->c));
		ft_memset(core->a + champ->cars->pos%MEM_SIZE, champ->c, 1);
	}
	*/
}

void    ft_02_opcode(t_core *core, t_champ *champ) {
	int *arg;
	int pc;
	int *codage;

	pc = champ->cars->pos % MEM_SIZE;
	codage = ft_get_codage(core, champ);
	arg = ft_get_args(core, champ, codage);
	if (codage[0] == 3)
		arg[0] = ft_read_4(core, (arg[0] % IDX_MOD + pc - 1) % MEM_SIZE);
	if (ft_check_cod_and_arg(champ, codage, arg)) {
		champ->cars->reg[arg[1] - 1] = (unsigned int)arg[0];
        if (!arg[0])
		    champ->cars->carry = 1;
        else
            champ->cars->carry = 0;
	}
}

void    ft_03_opcode(t_core *core, t_champ *champ) {
	int *arg;
	int pc;
	int *codage;
	int ag, pos, r, c;

	pc = champ->cars->pos % MEM_SIZE;
	codage = ft_get_codage(core, champ);
	arg = ft_get_args(core, champ, codage);
	if (ft_check_cod_and_arg(champ, codage, arg)) {
		if (codage[1] != 3)
			champ->cars->reg[arg[1] - 1] = champ->cars->reg[arg[0] - 1];
		else
		{
			ft_put_4(core, champ->cars->reg[arg[0] - 1], (arg[1] % IDX_MOD + pc) % MEM_SIZE);
			if (core->v)
			{
				ag = champ->cars->reg[arg[0] - 1];
				pos = (arg[1] % IDX_MOD + pc) % MEM_SIZE;
				if (pos < 0)
					pos = MEM_SIZE + pos;
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
				// c %= 192; ?? нужно ли
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
}

void    ft_04_opcode(t_core *core, t_champ *champ) {
	int *arg;
	int *codage;

	codage = ft_get_codage(core, champ);
	arg = ft_get_args(core, champ, codage);
	if (ft_check_cod_and_arg(champ, codage, arg)) {
		champ->cars->reg[arg[2] - 1] = champ->cars->reg[arg[0] - 1] + champ->cars->reg[arg[1] - 1];
        if (!champ->cars->reg[arg[2] - 1])
            champ->cars->carry = 1;
        else
            champ->cars->carry = 0;
	}
}

void    ft_05_opcode(t_core *core, t_champ *champ) {
	int *arg;
	int *codage;

	codage = ft_get_codage(core, champ);
	arg = ft_get_args(core, champ, codage);
	if (ft_check_cod_and_arg(champ, codage, arg)) {
		champ->cars->reg[arg[2] - 1] = champ->cars->reg[arg[0] - 1] - champ->cars->reg[arg[1] - 1];
        if (!champ->cars->reg[arg[2] - 1])
            champ->cars->carry = 1;
        else
            champ->cars->carry = 0;
	}
}