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
        if (champ->cars->opcode > 0 && champ->cars->opcode < 17)
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
        champ->cars->pos++; // в этом месте лажа при прижке и обновлении кода следующей кареткой
        ft_get_n_car_value(core, champ);
        if (core->v)
        {
            r = 3 + ((champ->cars->pos%MEM_SIZE)/64)%64;
            c = 3 + (3*((champ->cars->pos%MEM_SIZE)%64))%192;
            // if (champ->cars->opcode == 1 && champ->s_live) // ? champ_id == opcode' id
            if (champ->cars->opcode == 1 && champ->c == core->a[champ->cars->pos%MEM_SIZE]) // champ_id == opcode_id
            {
                attron(A_BOLD | COLOR_PAIR(champ->cc));
                ft_memset(core->a+champ->cars->pos%MEM_SIZE, champ->c, 1);
            }
            // else if (champ->cars->opcode == 1)
                // attron(A_BOLD | COLOR_PAIR(core->a[champ->cars->pos%MEM_SIZE]+10));
            // else if (champ->cars->opcode && champ->s_live)
            // {
                // attron(A_REVERSE | COLOR_PAIR(champ->c));
                // ft_memset(core->a+champ->cars->pos%MEM_SIZE, champ->c, 1);
            // }
            else
                attron(A_REVERSE | COLOR_PAIR(core->a[champ->cars->pos%MEM_SIZE]));
            //// attron(A_REVERSE);
            mvprintw(r, c, "%02x", core->arena[champ->cars->pos%MEM_SIZE]);
            //// attroff(A_REVERSE);
            if (champ->cars->opcode == 1)
                attroff(A_BOLD | COLOR_PAIR(champ->cc));
            // else if (champ->cars->opcode && champ->s_live)
                // attroff(A_REVERSE | COLOR_PAIR(champ->c));
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
    t_core  *p;

    p = (t_core*)ptr;
    while ((ch = getch()) != 27) // ESC
    {
        if (!(p)->p && ch == KEY_F(1)) // F1 - reset speed
            (p)->t = 100000;
        else if (!(p)->p && ch == KEY_UP) // ARROW UP - speed up
        {
            if ((p)->t > 10000)
                (p)->t /= 10;
            else
            {
                (p)->t = 0;
                pthread_exit(NULL);
                exit(131);
            }
        }
        else if (!(p)->p && (p)->t < 1000000 && ch == KEY_DOWN) // ARROW DOWN - speed down
            (p)->t *= 10;
        else if (!(p)->p && ch == KEY_LEFT) // ARROW LEFT - pause
            (p)->p = 1;
        else if ((p)->p && ch == KEY_RIGHT) // ARROW RIGHT - play
            (p)->p = 0;
    }
    endwin();
    SDL_Quit();
    exit(121);
    return (NULL);
}

void    *myThreadFun2(void *ptr)
{
    if (!ptr)
    {
        ;
        // play("Track1.wav");
    }
    pthread_exit(NULL);
    exit(132);
    return (NULL);
}

void    ft_start_fight(t_core *core) {
    t_champ *tmp;
    t_car   *car;
    pthread_t thread_id;
    pthread_t thread_id2;

    tmp = NULL;
    if (core->v)
    {
        pthread_create(&thread_id, NULL, myThreadFun, (void*)core);
        pthread_create(&thread_id2, NULL, myThreadFun2, NULL);
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
            do_ncurs(core);
            // attron(A_BOLD); mvprintw(8, 208, "%d", core->cycle);
            // attroff(A_BOLD); refresh();
            if (core->t)
                usleep(core->t);
            // getch();
            //usleep(100000);
            while (core->p)
            {
                attron(A_BOLD);
                mvprintw(3, 200, "** PAUSED ** ");
                refresh();
            mvprintw(3, 200, "** RUNNING **");
                attroff(A_BOLD);
                usleep(100000);
                // continue ;
            }
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
        refresh(); getch(); endwin(); SDL_Quit();
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
            if (core->dump != -1 && core->dump == core->cycle) {
                ft_dump(core);
                exit(0);
            }
            core->cycle++;
            if (core->cycle == core->c_to_die + core->last_check) {
                ft_make_check(core);
                core->last_check = core->cycle;
            }
        }
    }
}
