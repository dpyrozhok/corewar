#include "corewar.h"
#include "ncurs.h"

void    ft_check_cars(t_core *core)
{
    t_car   *tmp;

    tmp = core->cars;
    while (tmp->next)
        tmp = tmp->next;
    while (tmp) {
        if (tmp->state) {
            if (!tmp->live) {
                tmp->state = 0;
                core->qt_car--;
            } else
                tmp->live = 0;
        }
        tmp = tmp->prev;
    }
}

void    ft_make_check(t_core *core) {
    t_champ *champ;
    int     flag;

    flag = 0;
    core->qt_check++;
    champ = core->champs;
    if (core->v)
        do_last(core);
    while (champ)
    {
        if (champ->all_live >= NBR_LIVE)
            flag = 1;
        champ->s_live = 0;
        champ->all_live = 0;
        champ = champ->next;
    }
    if (flag || core->qt_check == MAX_CHECKS)
    {
        core->qt_check = 0;
        core->c_to_die -= CYCLE_DELTA;
    }
    ft_check_cars(core);
}
