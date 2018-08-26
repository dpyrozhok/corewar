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
    int pos,r,c;
 
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
        {
            if (core->v && champ->cars->sw)
            {
                champ->cars->sw = 0;
                pos = champ->cars->rp;
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
            ft_opcode_switcher(core, champ);
        }
        /*
        if (core->v)
        {
            r = 3+((champ->cars->pos%MEM_SIZE)/64)%64;
            c = 3+(3*((champ->cars->pos%MEM_SIZE)%64))%192;
            attron(COLOR_PAIR(core->a[champ->cars->pos%MEM_SIZE]));
            mvprintw(r,c,"%02x", core->arena[champ->cars->pos%MEM_SIZE]);
            attroff(COLOR_PAIR(core->a[champ->cars->pos%MEM_SIZE]));
        }
        */
        champ->cars->pos++;
        ft_get_n_car_value(core, champ);
        if (core->v)
        {
            r = 3 + ((champ->cars->pos%MEM_SIZE)/64)%64;
            c = 3 + (3*((champ->cars->pos%MEM_SIZE)%64))%192;
            if (champ->cars->opcode == 1 && champ->s_live)
            {
                attron(A_BOLD | COLOR_PAIR(champ->cc));
                ft_memset(core->a+champ->cars->pos%MEM_SIZE, champ->c, 1);
            }
            else if (champ->cars->opcode == 1)
                attron(A_BOLD | COLOR_PAIR(core->a[champ->cars->pos%MEM_SIZE]+10));
            else if (champ->cars->opcode && champ->s_live)
            {
                attron(A_REVERSE | COLOR_PAIR(champ->c));
                ft_memset(core->a+champ->cars->pos%MEM_SIZE, champ->c, 1);
            }
            else
                attron(A_REVERSE | COLOR_PAIR(core->a[champ->cars->pos%MEM_SIZE]));
            // attron(A_REVERSE);
            mvprintw(r, c, "%02x", core->arena[champ->cars->pos%MEM_SIZE]);
            // attroff(A_REVERSE);
            if (champ->cars->opcode == 1)
                attroff(A_BOLD | COLOR_PAIR(champ->cc));
            else if (champ->cars->opcode && champ->s_live)
                attroff(A_REVERSE | COLOR_PAIR(champ->c));
            else
                attroff(A_REVERSE | COLOR_PAIR(core->a[champ->cars->pos%MEM_SIZE]));
        }
    }
    else
        champ->cars->cycle--;
}

void    *myThreadFun(void *ptr)
{
    int     ch;
    int     *p;

    p = (int*)ptr;
    while ((ch = getch()) != 27)
    {
        if (ch == KEY_F(1))
        {
            *p = 100000;
            mvprintw(12, 200, "Speed: %dx     ", 100000/(*p));
        }
        else if (ch == KEY_UP)
        {
            *p /= (*p > 1 ? 10 : 1);
            mvprintw(12, 200, "Speed: %dx     ", 100000/(*p));
        }
        //     ((t_core*)(ptr))->t *= 10;
        else if (ch == KEY_DOWN)
        {
            *p *= (*p < 1000000 ? 10 : 1);
            if (*p != 1000000)
                mvprintw(12, 200, "Speed: %dx     ", 100000/(*p));
            else
                mvprintw(12, 200, "Speed: %.1fx     ", 0.5);
        }
        //     ((t_core*)(ptr))->t *= 10;
    }
    endwin();
    exit(121);
    return (NULL);
}

void    ft_start_fight(t_core *core) {
    t_champ *tmp;
    t_car   *car;
    pthread_t thread_id;

    tmp = NULL;
    if (core->v)
    {
        pthread_create(&thread_id, NULL, myThreadFun, (void*)&(core->t));
        // pthread_join(thread_id, NULL);
        // getch();
        attron(A_BOLD); mvprintw(3, 200, "** RUNNING **"); attroff(A_BOLD);
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
            //ft_dump(core);
            if (core->dump != -1 && core->cycle == core->dump)
                ft_dump(core);
            do_ncurs(core);
            // attron(A_BOLD); mvprintw(8, 208, "%d", core->cycle);
            // attroff(A_BOLD); refresh();
            usleep(core->t);
            // getch();
            //usleep(100000);
            core->cycle++;
            if (core->cycle == core->c_to_die + core->last_check) {
                ft_make_check(core);
                core->last_check = core->cycle;
            }
        }
        // do_ncurs(NULL);
        do_ncurs(core);
        if (core->l)
            mvprintw(core->l - 3, 201, "--------------------------------------------------]");
        attron(A_BOLD); mvprintw(3, 200, "** FINISH ** "); attroff(A_BOLD);
        getch(); endwin();
    }
    else
    {
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
            //ft_dump(core);
            if (core->dump != -1 && core->cycle == core->dump)
                ft_dump(core);
            //usleep(100000);
            core->cycle++;
            if (core->cycle == core->c_to_die + core->last_check) {
                ft_make_check(core);
                core->last_check = core->cycle;
            }
        }
    }
}
