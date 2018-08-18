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
        ft_put_4(core, champ->cars->reg[arg[0] - 1], ((arg[1] + arg[2]) % IDX_MOD + pc) % MEM_SIZE);
}

void    ft_12_opcode(t_core *core, t_champ *champ) {
    int new_pc;

    new_pc = ft_read_2(core, champ->cars->pos % MEM_SIZE);
    new_pc = (new_pc % IDX_MOD + champ->cars->pos) % MEM_SIZE;
    ft_create_car(core, champ, new_pc); // вопрос переноситься ли жизнь процеса на новый ли нет?
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
    ft_create_car(core, champ, new_pc); // вопрос переноситься ли жизнь процеса на новый ли нет?
    champ->cars->pos += 2;
}