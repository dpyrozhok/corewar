#include "corewar.h"
#include "ncurs.h"

void    ft_check_cars(t_core *core)
{
    t_car   *tmp;
    int pos,r,c;

    tmp = core->cars;
    while (tmp->next)
        tmp = tmp->next;
    while (tmp) {
        if (tmp->state) {
            if (!tmp->live) {
                tmp->state = 0;
                core->qt_car--;
                if (core->v)
                {
                    pthread_mutex_lock(&core->m);
                    
                    if (tmp->sw)
                    {
                        tmp->sw = 0;
                        pos = tmp->rp;
                        r = 3+((pos%MEM_SIZE)/64)%64;
                        c = 3+(3*((pos%MEM_SIZE)%64))%192;
                        attron(COLOR_PAIR(core->a[pos%MEM_SIZE]));
                        mvprintw(r,c,"%02x", (unsigned char)(core->arena[pos%MEM_SIZE]));
                        attroff(COLOR_PAIR(core->a[pos%MEM_SIZE]));
                        pos++;
                        r = 3+((pos%MEM_SIZE)/64)%64;
                        c = 3+(3*((pos%MEM_SIZE)%64))%192;
                        attron(COLOR_PAIR(core->a[pos%MEM_SIZE]));
                        mvprintw(r,c,"%02x", (unsigned char)(core->arena[pos%MEM_SIZE]));
                        attroff(COLOR_PAIR(core->a[pos%MEM_SIZE]));
                        pos++;
                        r = 3+((pos%MEM_SIZE)/64)%64;
                        c = 3+(3*((pos%MEM_SIZE)%64))%192;
                        attron(COLOR_PAIR(core->a[pos%MEM_SIZE]));
                        mvprintw(r,c,"%02x", (unsigned char)(core->arena[pos%MEM_SIZE]));
                        attroff(COLOR_PAIR(core->a[pos%MEM_SIZE]));
                        pos++;
                        r = 3+((pos%MEM_SIZE)/64)%64;
                        c = 3+(3*((pos%MEM_SIZE)%64))%192;
                        attron(COLOR_PAIR(core->a[pos%MEM_SIZE]));
                        mvprintw(r,c,"%02x", (unsigned char)(core->arena[pos%MEM_SIZE]));
                        attroff(COLOR_PAIR(core->a[pos%MEM_SIZE]));
                    }
                    r = 3+((tmp->pos%MEM_SIZE)/64)%64;
                    c = 3+(3*((tmp->pos%MEM_SIZE)%64))%192;
                    attron(COLOR_PAIR(core->a[tmp->pos%MEM_SIZE]));
                    mvprintw(r,c,"%02x", core->arena[tmp->pos%MEM_SIZE]);
                    attroff(COLOR_PAIR(core->a[tmp->pos%MEM_SIZE]));
                    
                    pthread_mutex_unlock(&core->m);
                }
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
        ft_breakdown(core);
    pthread_mutex_lock(&core->m);
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
    pthread_mutex_unlock(&core->m);
    ft_check_cars(core);
}
