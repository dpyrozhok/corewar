//
// Created by Pavlo OPANASENKO on 8/13/18.
//
#include "corewar.h"

void    ft_11_opcode(t_core *core, t_champ *champ) {
    int *arg;
    int pc;
    int *codage;

    pc = champ->cars->pos % MEM_SIZE;
    codage = ft_get_codage(core, champ);
    arg = ft_get_args(core, champ, codage);
    if (codage[1] == 3)
        arg[1] = ft_read_4(core, (arg[1] + pc) % IDX_MOD);
    if (ft_check_cod_and_arg(champ, codage, arg))
        ft_put_4(core, champ->cars->reg[arg[0] - 1], pc + (arg[1] + arg[2]) % IDX_MOD % MEM_SIZE);
}
