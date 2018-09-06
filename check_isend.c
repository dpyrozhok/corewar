#include "corewar.h"
#include "ncurs.h"

void    ft_check_cars(t_core *core)
{
    t_car   *tmp;

    tmp = core->cars;
    while (tmp) {
        if (!tmp->live)
            tmp->state = 0;
        else
            tmp->live = 0;
        tmp = tmp->next;
    }
}

void    ft_make_check(t_core *core) {
    t_champ *champ;
    int     flag;
    int     s_live;

    flag = 0;
    s_live = 0;
    core->qt_check++;
    champ = core->champs;
    if (core->v)
        do_last(core);
    ft_check_cars(core);
    while (champ)
    {
        s_live += champ->s_live;
        champ->s_live = 0;
        champ = champ->next;
    }
    if (s_live >= NBR_LIVE)
        flag = 1;
    if (flag || core->qt_check == MAX_CHECKS)
    {
        core->qt_check = 0;
        core->c_to_die -= CYCLE_DELTA;
    }
}
