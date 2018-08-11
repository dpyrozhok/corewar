#include "corewar.h"

void    ft_check_single_car(t_core *core, t_champ *champ, t_car *car)
{
    if (!car->live) {
        core->qt_car--;
        car->prev->next = car->next;
        car->next->prev = car->prev;
        free(car);
        champ->cars = NULL;
    }
    car->live = 0;
}

void    ft_check_cars(t_core *core, t_champ *champ)
{
    t_car   *tmp;
    t_car   *start;

    start = champ->cars;
    tmp = champ->cars;
    if (tmp && tmp->next == start)
        ft_check_single_car(core, champ, tmp);
    else
    {
        while (tmp && tmp->next != start)
        {
            ft_check_single_car(core, champ, tmp);
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
        ft_check_cars(core, tmp);
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
