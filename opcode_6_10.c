//
// Created by Pavlo OPANASENKO on 8/15/18.
//

#include "corewar.h"

void    ft_06_opcode(t_core *core, t_champ *champ) {
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
    if (codage[0] == 3)
        arg[0] = ft_read_4(core, (arg[0] % IDX_MOD + pc - 1) % MEM_SIZE);
    if (codage[1] == 3)
        arg[1] = ft_read_4(core, (arg[1] % IDX_MOD + pc - 1) % MEM_SIZE);
    if (ft_check_cod_and_arg(champ, codage, arg) && arg[2] < 17 && arg[2] > 0) {
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
        champ->cars->reg[arg[2] - 1] = (unsigned int)(arg[0] ^ arg[1]);
        champ->cars->carry = 1;
    } else
        champ->cars->carry = 0;
}

void    ft_09_opcode(t_core *core, t_champ *champ) {
    int shift;

    if (champ->cars->carry) {
        shift = ft_read_2(core, champ->cars->pos % MEM_SIZE);
        shift = champ->cars->pos % MEM_SIZE - 1 + shift % MEM_SIZE;
        champ->cars->pos = shift % MEM_SIZE;
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
    if (ft_check_cod_and_arg(champ, codage, arg))
        champ->cars->reg[arg[2] - 1] = (unsigned int)ft_read_4(core, ((arg[0] + arg[1]) % IDX_MOD + pc) % MEM_SIZE);
}
