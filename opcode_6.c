//
// Created by Pavlo OPANASENKO on 8/15/18.
//

#include "corewar.h"

//для zork.cor эта команда нужна лишь чтобы включить carry и выполнить zjmp

void    ft_06_opcode(t_core *core, t_champ *champ) {
    int arg[3];
    int pc;
    int codage[4];
    int carry;
    int reg_pos;

    pc = champ->cars->pos;
    champ->cars->pos++;
    carry = 1;
    codage[0] = (unsigned char)(core->arena[champ->cars->pos % MEM_SIZE] & 192) >> 6;
    codage[1] = (unsigned char)(core->arena[champ->cars->pos % MEM_SIZE] & 48) >> 4;
    codage[2] = (unsigned char)(core->arena[champ->cars->pos % MEM_SIZE] & 12) >> 2;
    codage[3] = (unsigned char)(core->arena[champ->cars->pos % MEM_SIZE] & 3);
    if (codage[0] == REG_CODE) {
        reg_pos = ft_read_1(core, champ->cars->pos % MEM_SIZE) - 1;
        if (reg_pos < 16 && reg_pos >= 0)   // проверка на валидность номера регистра с которого читаем значение, если невалидный каретка в 0, операция не выполняется, но байты считываются дальше
            arg[0] = champ->cars->reg[reg_pos];
        else
            carry = 0;
        champ->cars->pos += 1;
    } else if (codage[1] == DIR_CODE) {
        arg[0] = ft_read_4(core, champ->cars->pos % MEM_SIZE);
        champ->cars->pos += 4;
    } else if (codage[1] == IND_CODE) {
        arg[0] = ft_read_4(core, (ft_read_2(core, champ->cars->pos % MEM_SIZE) + pc) % IDX_MOD);
        champ->cars->pos += 2;
    }

    if (codage[1] == REG_CODE) {
        reg_pos = ft_read_1(core, champ->cars->pos % MEM_SIZE) - 1;
        if (reg_pos < 16 && reg_pos >= 0)
            arg[1] = champ->cars->reg[reg_pos];
        else
            carry = 0;
        champ->cars->pos += 1;
    } else if (codage[1] == DIR_CODE) {
        arg[1] = ft_read_4(core, champ->cars->pos % MEM_SIZE);
        champ->cars->pos += 4;
    } else if (codage[1] == IND_CODE) {
        arg[1] = ft_read_4(core, (ft_read_2(core, champ->cars->pos % MEM_SIZE) + pc) % IDX_MOD);
        champ->cars->pos += 2;
    }

    if (codage[2] == REG_CODE) {
        arg[2] = ft_read_1(core, champ->cars->pos % MEM_SIZE) - 1;
        champ->cars->pos += 1;
    }
    if (arg[2] < 16 && arg[2] >= 0 && carry) { // проверка на валидность номера регистра в который пишем
        champ->cars->reg[arg[2]] = (unsigned int)(arg[0] & arg[1]);
        champ->cars->carry = carry;
    } else {
        champ->cars->carry = 0;
    }
}