#include "corewar.h"

void    ft_put_4(t_core *core, int arg, int pos) {
    core->arena[pos] = (unsigned char)(arg >> 24);
    core->arena[pos + 1] = (unsigned char)(arg >> 16 & 255);
    core->arena[pos + 2] = (unsigned char)(arg >> 8 & 255);
    core->arena[pos + 3] = (unsigned char)(arg & 255);
}

int     ft_read_1(t_core *core, int pos) {
    int    ret;

    ret = (int)(
            (unsigned char)core->arena[pos + 1]
    );
    return ret;
}

int     ft_read_2(t_core *core, int pos) {
    int    ret;

    ret = (int)(
            (unsigned char)core->arena[pos + 1] << 8 |
            (unsigned char)core->arena[pos + 2]
    );
    return ret;
}

int     ft_read_4(t_core *core, int pos) {
    int    ret;

    ret = (int)(
            (unsigned char)core->arena[pos + 1] << 24 |
            (unsigned char)core->arena[pos + 2] << 16 |
            (unsigned char)core->arena[pos + 3] << 8 |
            (unsigned char)core->arena[pos + 4]
    );
    return ret;
}

// <--вариант команды live для zork



// -->вариант команды live для zork



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
    if (champ->cars->opcode == 6)
        ft_06_opcode(core, champ);
//    if (champ->cars->opcode == 7)
//        ft_07_opcode(core, champ);
//    if (champ->cars->opcode == 8)
//        ft_08_opcode(core, champ);
}

void    ft_switch_op_9_16(t_core *core, t_champ *champ)
{
    if (champ->cars->opcode == 9)
        ft_09_opcode(core, champ);
//    if (champ->cars->opcode == 10)
//        ft_10_opcode(core, champ);
    if (champ->cars->opcode == 11)
        ft_11_opcode(core, champ);
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
