#include "corewar.h"

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

void    ft_make_op(t_core *core, t_champ *champ)
{
    if (champ->cars->opcode == 1) {
        if ((unsigned int)champ->id == ft_get_live_v(core, champ->cars->pos % MEM_SIZE)) {
            champ->s_live++;
            champ->last_live = core->cycle;
        }
        champ->cars->live = 1;
        champ->cars->pos += 4;
    } // для каждого opcode своя функция, здесь приведен только возможный вариант реализации одной команды live
    champ->cars->pos++;
    champ->cars->opcode = core->arena[champ->cars->pos % MEM_SIZE];
    if (champ->cars->opcode == 1)
        champ->cars->cycle = 10; // заменить условные 10 на значение в зависимости от исполняемой команды
}

void    ft_make_move(t_core *core, t_champ *champ)
{
    champ->cars->pos++;
    if (core->arena[champ->cars->pos % MEM_SIZE] > 0 && core->arena[champ->cars->pos % MEM_SIZE] < 16)
    {
        champ->cars->opcode = core->arena[champ->cars->pos % MEM_SIZE];
        champ->cars->cycle = 0;
    }
    else
        champ->cars->opcode = 0;
}

void    ft_touch_car(t_core *core, t_champ *champ)
{
    if (!champ->cars->cycle) {
        if (champ->cars->opcode > 0 && champ->cars->opcode < 16)
            ft_make_op(core, champ);
        else
            ft_make_move(core, champ);
    }
    else
        champ->cars->cycle--;
}

void    ft_check_car(t_core *core, t_champ *champ)
{
    t_car   *tmp;
    t_car   *start;

    start = champ->cars;
    tmp = champ->cars;
    if (tmp && tmp->next == start) {
        if (!tmp->live) {
            core->qt_car--;
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            free(tmp);
            champ->cars = NULL;
        }
        tmp->live = 0;
    }
    else
    {
        while (tmp && tmp->next != start)
        {
            if (!tmp->live) {
                core->qt_car--;
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
                free(tmp);
            }
            tmp->live = 0;
            tmp = tmp->next;
        }
    }
}

void    ft_make_check(t_core *core) {
    t_champ *tmp;
    int     flag;

    flag = 0;
    core->qt_check++;
    tmp = core->champs;
    while (tmp)
    {
        ft_check_car(core, tmp);
        if (tmp->s_live >= NBR_LIVE)
            flag = 1;
        tmp->s_live = 0;
        tmp = tmp->next;
    }
    if (flag || core->qt_check == MAX_CHECKS)
    {
        core->qt_check = 0;
        core->c_to_die -= CYCLE_DELTA;
    }
}


void    ft_start_fight(t_core *core) {
    t_champ *tmp;

    while (core->c_to_die > 0 && core->qt_car > 0) {
        tmp = core->champs;
        while (tmp)
        {
            if (tmp->cars) {
                ft_touch_car(core, tmp);
                core->winner_id = tmp->id;
            }
            tmp = tmp->next;
        }
        core->cycle++;
        if (core->cycle == core->c_to_die + core->last_check) {
            ft_make_check(core);
            core->last_check = core->cycle;
        }
    }
}
