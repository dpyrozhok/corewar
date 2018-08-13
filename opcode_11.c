//
// Created by Pavlo OPANASENKO on 8/13/18.
//
#include "corewar.h"

void    ft_11_opcode(t_core *core, t_champ *champ) {
    int arg[3];
    int pc;
    int codage[4];

    pc = champ->cars->pos;
    champ->cars->pos++;
    codage[0] = (unsigned char)(core->arena[champ->cars->pos % MEM_SIZE] & 192) >> 6;
    codage[1] = (unsigned char)(core->arena[champ->cars->pos % MEM_SIZE] & 48) >> 4;
    codage[2] = (unsigned char)(core->arena[champ->cars->pos % MEM_SIZE] & 12) >> 2;
    codage[3] = (unsigned char)(core->arena[champ->cars->pos % MEM_SIZE] & 3);
    champ->cars->pos++;
    if (codage[0] == T_REG) {
        arg[0] = champ->cars->reg[ft_read_2(core, champ->cars->pos % MEM_SIZE)];
        champ->cars->pos += 2;
    }
    if (codage[1] == T_REG) {
        arg[1] = champ->cars->reg[ft_read_2(core, champ->cars->pos % MEM_SIZE)];
        champ->cars->pos += 2;
    } else if (codage[1] == T_DIR) {
        arg[1] = ft_read_2(core, champ->cars->pos % MEM_SIZE);
        champ->cars->pos += 2;
    } else if (codage[1] == T_IND) {
        arg[1] = ft_read_4(core, (ft_read_2(core, champ->cars->pos % MEM_SIZE) + pc) % IDX_MOD);
        champ->cars->pos += 2;
    }
    if (codage[2] == T_REG) {
        arg[2] = champ->cars->reg[ft_read_2(core, champ->cars->pos % MEM_SIZE)];
        champ->cars->pos += 2;
    } else if (codage[2] == T_DIR) {
        arg[2] = ft_read_2(core, champ->cars->pos % MEM_SIZE);
        champ->cars->pos += 2;
    } else if (codage[2] == T_IND) {
        arg[2] = ft_read_4(core, (ft_read_2(core, champ->cars->pos % MEM_SIZE) + pc) % IDX_MOD);
        champ->cars->pos += 2;
    }
//    ft_put_4(arg[0], core->arena[pc + (arg[1] + arg[2]) % IDX_MOD % MEM_SIZE]);  // ft_put_4 записывает 4 байта на карту
}
