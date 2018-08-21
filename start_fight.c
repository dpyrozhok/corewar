#include "corewar.h"
#include "ncurs.h"

void    ft_get_n_car_value(t_core *core, t_champ *champ)
{
    if (core->arena[champ->cars->pos % MEM_SIZE] > 0 && core->arena[champ->cars->pos % MEM_SIZE] < 16)
    {
        champ->cars->opcode = core->arena[champ->cars->pos % MEM_SIZE];
        champ->cars->cycle = op_tab[champ->cars->opcode - 1].cycle;;
    }
    else
        champ->cars->opcode = 0;
}

void    ft_touch_car(t_core *core, t_champ *champ)
{
    int r,c;
 
    if (champ->cars->cycle < 2) {
        if (core->v)
        {
            r = 3+((champ->cars->pos%MEM_SIZE)/64)%64;
            c = 3+(3*((champ->cars->pos%MEM_SIZE)%64))%192;
            attron(COLOR_PAIR(core->a[champ->cars->pos%MEM_SIZE]));
            mvprintw(r,c,"%02x", core->arena[champ->cars->pos%MEM_SIZE]);
            attroff(COLOR_PAIR(core->a[champ->cars->pos%MEM_SIZE]));
        }
        champ->cars->cycle = 0;
        if (champ->cars->opcode > 0 && champ->cars->opcode < 16)
            ft_opcode_switcher(core, champ);
        if (core->v)
        {
            r = 3+((champ->cars->pos%MEM_SIZE)/64)%64;
            c = 3+(3*((champ->cars->pos%MEM_SIZE)%64))%192;
            attron(COLOR_PAIR(core->a[champ->cars->pos%MEM_SIZE]));
            mvprintw(r,c,"%02x", core->arena[champ->cars->pos%MEM_SIZE]);
            attroff(COLOR_PAIR(core->a[champ->cars->pos%MEM_SIZE]));
        }
        champ->cars->pos++;
        if (core->v)
        {
            r = 3 + ((champ->cars->pos%MEM_SIZE)/64)%64;
            c = 3 + (3*((champ->cars->pos%MEM_SIZE)%64))%192;
            attron(COLOR_PAIR(core->a[champ->cars->pos%MEM_SIZE]));
            attron(A_REVERSE);
            mvprintw(r, c, "%02x", core->arena[champ->cars->pos%MEM_SIZE]);
            attroff(A_REVERSE);
            attroff(COLOR_PAIR(core->a[champ->cars->pos%MEM_SIZE]));
        }
        ft_get_n_car_value(core, champ);
    }
    else
        champ->cars->cycle--;
}

void    ft_start_fight(t_core *core) {
    t_champ *tmp;
    t_car   *car;

    tmp = NULL;
    if (core->v)
    {
        getch();
        attron(A_BOLD); mvprintw(3, 200, "** RUNNING **"); attroff(A_BOLD);
    }
    while (core->c_to_die > 0 && core->qt_car > 0) {
        while (tmp)
        {
            if (tmp->cars) {
                car = tmp->cars;
                ft_touch_car(core, tmp);
                tmp->cars = tmp->cars->next;
                while (car != tmp->cars) {
                    ft_touch_car(core, tmp);
                    tmp->cars = tmp->cars->next;
                }
            }
            tmp = tmp->next;
        }
        tmp = core->champs;
        ft_dump(core);
        if (!core->v && core->dump != -1 && core->cycle == core->dump)
            ft_dump(core);
        if (core->v)
        {
            do_ncurs(core);
            // attron(A_BOLD); mvprintw(8, 208, "%d", core->cycle);
            // attroff(A_BOLD); refresh();
            // usleep(10000);
        }
        //usleep(100000);
        core->cycle++;
        if (core->cycle == core->c_to_die + core->last_check) {
            ft_make_check(core);
            core->last_check = core->cycle;
        }
    }
    if (core->v)
    {
        // do_ncurs(NULL);
        do_ncurs(core);
        attron(A_BOLD); mvprintw(3, 200, "** FINISH ** "); attroff(A_BOLD);
        getch(); endwin();
    }
}
