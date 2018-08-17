//
// Created by Pavlo OPANASENKO on 8/17/18.
//

#include "corewar.h"

void    ft_01_opcode(t_core *core, t_champ *champ) {
    if (champ->id == ft_read_4(core, champ->cars->pos % MEM_SIZE)) {  // codage нету, а labelsize == 4, поєтому читаем четыре байта
        champ->s_live++;
        champ->last_live = core->cycle;
        core->winner_id = champ->id;  // условие кто последний сказал - тот и чемпион
    }
    champ->cars->live = 1; // каретка (процесс) жив в этом цикле
    champ->cars->pos += 4;
}

void    ft_02_opcode(t_core *core, t_champ *champ) {
    int *arg;
    int pc;
    int *codage;

    pc = champ->cars->pos % MEM_SIZE;
    codage = ft_get_codage(core, champ);
    arg = ft_get_args(core, champ, codage);
    if (codage[0] == 3)
        arg[0] = ft_read_4(core, (arg[0] + pc) % IDX_MOD);
    if (ft_check_cod_and_arg(champ, codage, arg)) {
        champ->cars->reg[arg[1] - 1] = (unsigned int)arg[0];
        champ->cars->carry = 1;
    } else
        champ->cars->carry = 0;
}

void    ft_03_opcode(t_core *core, t_champ *champ) {
    int *arg;
    int pc;
    int *codage;

    pc = champ->cars->pos % MEM_SIZE;
    codage = ft_get_codage(core, champ);
    arg = ft_get_args(core, champ, codage);
    if (codage[1] == 3)
        arg[1] = ft_read_4(core, (arg[1] + pc) % IDX_MOD);
    if (ft_check_cod_and_arg(champ, codage, arg)) {
        if (codage[1] != 3)
            champ->cars->reg[arg[1] - 1] = champ->cars->reg[arg[0] - 1];
        else
            ft_put_4(core, champ->cars->reg[arg[0]], pc + arg[0] % IDX_MOD % MEM_SIZE);
    }
}

void    ft_04_opcode(t_core *core, t_champ *champ) {
    int *arg;
    int pc;
    int *codage;

    pc = champ->cars->pos % MEM_SIZE;
    codage = ft_get_codage(core, champ);
    arg = ft_get_args(core, champ, codage);
    if (ft_check_cod_and_arg(champ, codage, arg)) {
        champ->cars->reg[arg[2] - 1] = champ->cars->reg[arg[0] - 1] + champ->cars->reg[arg[1] - 1];
        champ->cars->carry = 1;
    } else
        champ->cars->carry = 0;
}

void    ft_05_opcode(t_core *core, t_champ *champ) {
    int *arg;
    int pc;
    int *codage;

    pc = champ->cars->pos % MEM_SIZE;
    codage = ft_get_codage(core, champ);
    arg = ft_get_args(core, champ, codage);
    if (ft_check_cod_and_arg(champ, codage, arg)) {
        champ->cars->reg[arg[2] - 1] = champ->cars->reg[arg[0] - 1] - champ->cars->reg[arg[1] - 1];
        champ->cars->carry = 1;
    } else
        champ->cars->carry = 0;
}