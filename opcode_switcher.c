#include "corewar.h"

// нужно разобраться как тянуть инфу со структуры op.c

// <--вариант команды live для zork

unsigned int ft_get_live_v(t_core *core, int pos) {
    unsigned int    ret;

    ret = (unsigned int)(
            (unsigned char)core->arena[pos + 1] << 24 |
            (unsigned char)core->arena[pos + 2] << 16 |
            (unsigned char)core->arena[pos + 3] << 8 |
            (unsigned char)core->arena[pos + 4]
    );
    return ret;
}

void    ft_01_opcode(t_core *core, t_champ *champ) {
    if ((unsigned int)champ->id == ft_get_live_v(core, champ->cars->pos % MEM_SIZE)) {
        champ->s_live++;
        champ->last_live = core->cycle;
    }
    champ->cars->live = 1;
    champ->cars->pos += 4;
}

// -->вариант команды live для zork

// <--вариант команды sti для zork

//void    ft_11_opcode(t_core *core, t_champ *champ) {
//
//}

// -->вариант команды sti для zork

void    ft_switch_op_1_8(t_core *core, t_champ *champ)
{
    if (champ->cars->opcode == 1)
        ft_01_opcode(core, champ);
//    if (champ->cars->opcode == 2)
//        ft_02_opcode(core, champ);
//    if (champ->cars->opcode == 3)
//        ft_03_opcode(core, champ);
//    if (champ->cars->opcode == 4)
//        ft_04_opcode(core, champ);
//    if (champ->cars->opcode == 5)
//        ft_05_opcode(core, champ);
//    if (champ->cars->opcode == 6)
//        ft_06_opcode(core, champ);
//    if (champ->cars->opcode == 7)
//        ft_07_opcode(core, champ);
//    if (champ->cars->opcode == 8)
//        ft_08_opcode(core, champ);
}

void    ft_switch_op_9_16(t_core *core, t_champ *champ)
{
    if (core && champ)
        ;
//    if (champ->cars->opcode == 9)
//        ft_09_opcode(core, champ);
//    if (champ->cars->opcode == 10)
//        ft_10_opcode(core, champ);
//    if (champ->cars->opcode == 11)
//        ft_11_opcode(core, champ);
//    if (champ->cars->opcode == 12)
//        ft_12_opcode(core, champ);
//    if (champ->cars->opcode == 13)
//        ft_13_opcode(core, champ);
//    if (champ->cars->opcode == 14)
//        ft_14_opcode(core, champ);
//    if (champ->cars->opcode == 15)
//        ft_15_opcode(core, champ);
//    if (champ->cars->opcode == 16)
//        ft_16_opcode(core, champ);
}

void    ft_opcode_switcher(t_core *core, t_champ *champ)
{
    if (champ->cars->opcode < 9)
        ft_switch_op_1_8(core, champ);
    else
        ft_switch_op_9_16(core, champ);
}
