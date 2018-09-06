//
// Created by Pavlo OPANASENKO on 8/17/18.
//
#include "corewar.h"

//T_REG; 001 1
//T_DIR; 010 2
//T_IND; 100 4
//T_DIR | T_IND; 6 110
//T_IND | T_REG; 5 101
//T_DIR | T_REG; 3 011
//T_REG | T_DIR | T_IND; 7 111

t_champ *ft_get_champ(t_core *core, int id)
{
    t_champ *tmp;

    tmp = core->champs;
    while(tmp)
    {
        if (tmp->id == id)
            return(tmp);
        tmp = tmp->next;
    }
    return(NULL);
}

int ft_check_cod_and_arg(t_car *car, int const *cod, int const *arg) {
    int i;
    int op;

    i = 0;
    op = car->opcode - 1;
    while (i < op_tab[op].qt_arg) {
        if (!(cod[i] & op_tab[op].arg[i])) // проверка валидные значение в codage маски вверху
            return 0;
        else if (cod[i] == REG_CODE) // проверка если T_REG
        {
            if (!(arg[i] > 0 && arg[i] < 17)) // проверка валидное ли значение T_REG
                return 0;
        }
        i++;
    }
    return 1;
}

int *ft_get_codage(t_core *core, t_car *car) {
    int *cod;
    int op;

    op = car->opcode - 1;
    if (op_tab[op].codage)
    {
        car->pos++;
        cod = (int *)ft_memalloc(sizeof(int) * 4);
        cod[0] = (core->arena[car->pos % MEM_SIZE] & 192) >> 6;
        cod[1] = (core->arena[car->pos % MEM_SIZE] & 48) >> 4;
        cod[2] = (core->arena[car->pos % MEM_SIZE] & 12) >> 2;
        cod[3] = (core->arena[car->pos % MEM_SIZE] & 3);
        return cod;
    }
    return NULL;
}

int *ft_get_args(t_core *core, t_car *car, int const *cod) {
    int *arg;
    int op;
    int i;

    i = 0;
    op = car->opcode -1;
    arg = (int *)ft_memalloc(sizeof(int) * op_tab[op].qt_arg);
    while (i < op_tab[op].qt_arg) {
        if (cod[i] == REG_CODE) {
            arg[i] = ft_read_1(core, car->pos % MEM_SIZE);
            car->pos += 1;
        } else if (cod[i] == DIR_CODE) {
            if (op_tab[op].lable) {
                arg[i] = ft_read_2(core, car->pos % MEM_SIZE);
                car->pos += 2;
            } else {
                arg[i] = ft_read_4(core, car->pos % MEM_SIZE);
                car->pos += 4;
            }
        } else if (cod[i] == IND_CODE) {
            arg[i] = ft_read_2(core, car->pos % MEM_SIZE);
            car->pos += 2;
        }
        i++;
    }
    return arg;
}

