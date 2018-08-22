#include "corewar.h"

void    ft_check_single_car(t_core *core, t_champ *champ, t_car *car)
{
    if (!car->live) {
        core->qt_car--;
        car->prev->next = car->next;
        car->next->prev = car->prev;
        if (champ->cars == champ->cars->next)
            champ->cars = NULL;
        else
            champ->cars = car->next;
        free(car);
    }
    else {
        car->live = 0;
        champ->cars = champ->cars->next;
    }
}

void    ft_check_cars(t_core *core, t_champ *champ)
{
    t_car   *start;

    start = champ->cars;
    ft_check_single_car(core, champ, champ->cars);
    while (champ->cars && champ->cars != start)
            ft_check_single_car(core, champ, champ->cars);
}

void    ft_make_check(t_core *core) {
    t_champ *tmp;
    int     flag;
    int     s_live;

    flag = 0;
    s_live = 0;
    core->qt_check++;
    tmp = core->champs;
    while (tmp)
    {
        ft_check_cars(core, tmp);
        s_live += tmp->s_live;
        tmp->s_live = 0;
        tmp = tmp->next;
    }
    if (s_live >= NBR_LIVE)
        flag = 1;
    if (flag || core->qt_check == MAX_CHECKS)
    {
        core->qt_check = 0;
        core->c_to_die -= CYCLE_DELTA;
    }
}
