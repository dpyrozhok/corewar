#include "corewar.h"

int     ft_get_wait_cycles(int opcode) // значения которые нужны для zork
{
    if (opcode == 1)
        return(10);
    if (opcode == 6)
        return(10);
    if (opcode == 9)
        return(20);
    if (opcode == 11)
        return(25);
    return(0);
}

void    ft_make_move(t_core *core, t_champ *champ)
{
    champ->cars->pos++;
    if (core->arena[champ->cars->pos % MEM_SIZE] > 0 && core->arena[champ->cars->pos % MEM_SIZE] < 16)
    {
        champ->cars->opcode = core->arena[champ->cars->pos % MEM_SIZE];
        champ->cars->cycle = ft_get_wait_cycles(champ->cars->opcode);
    }
    else
        champ->cars->opcode = 0;
}

void    ft_touch_car(t_core *core, t_champ *champ)
{
    if (!champ->cars->cycle) {
        if (champ->cars->opcode > 0 && champ->cars->opcode < 16)
            ft_opcode_switcher(core, champ);
        ft_make_move(core, champ);
    }
    else
        champ->cars->cycle--;
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
