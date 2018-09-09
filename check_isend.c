#include "corewar.h"
#include "ncurs.h"

void    ft_check_cars(t_core *core)
{
    t_car   *tmp;

    tmp = core->cars;
    while (tmp) {
        if (tmp->state) {
            if (!tmp->live) {
                tmp->state = 0;
                core->qt_car--;
            } else
                tmp->live = 0;
        }
        tmp = tmp->next;
    }
}

void    ft_make_check(t_core *core) {
    t_champ *champ;
    int     flag;
    int     a_l;

    flag = 0;
    a_l = 0;
    core->qt_check++;
    champ = core->champs;
    if (core->v)
        do_last(core);
    ft_check_cars(core);
    while (champ)
    {
        a_l += champ->all_live;
        champ->s_live = 0;
        champ->all_live = 0;
        champ = champ->next;
    }
    if (a_l >= NBR_LIVE)
        flag = 1;
    if (flag || core->qt_check == MAX_CHECKS)
    {
        core->qt_check = 0;
        core->c_to_die -= CYCLE_DELTA;
    }
}
