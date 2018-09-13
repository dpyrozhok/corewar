#include "corewar.h"
#include "ncurs.h"

void    ft_get_n_car_value(t_core *core, t_car *car)
{
    t_champ *champ;
    int r,c;
 
    if (core->arena[car->pos % MEM_SIZE] > 0 && core->arena[car->pos % MEM_SIZE] < 17)
    {
        car->opcode = core->arena[car->pos % MEM_SIZE];
        car->cycle = op_tab[car->opcode - 1].cycle;
    }
    else
        car->opcode = 0;
    if (core->v)
    {
        pthread_mutex_lock(&core->m);

        champ = ft_get_champ(core, car->id);
        r = 3 + ((car->pos%MEM_SIZE)/64)%64;
        c = 3 + (3*((car->pos%MEM_SIZE)%64))%192;
        // r = 3 + (pos/64);
        // c = 3 + 3*(pos%64);
        if (car->opcode == 1 && car->id == ft_read_4(core, car->pos % MEM_SIZE)) // champ_id == opcode_id
        // if (car->opcode == 1 && champ->c == core->a[car->pos%MEM_SIZE]) // champ_id == opcode_id
            attron(A_BOLD | COLOR_PAIR(champ->cc));
        else
            attron(A_REVERSE | COLOR_PAIR(core->a[car->pos%MEM_SIZE]));
        // attron(COLOR_PAIR(core->a[pos]));
        // attron(A_REVERSE);
        // attron(COLOR_PAIR(champ->c));
        mvprintw(r, c, "%02x", core->arena[car->pos%MEM_SIZE]);
        // attroff(COLOR_PAIR(champ->c));
        // attroff(A_REVERSE);
        // attroff(COLOR_PAIR(core->a[pos]));
        if (car->opcode == 1 && car->id == ft_read_4(core, car->pos % MEM_SIZE)) // champ_id == opcode_id
        // if (car->opcode == 1 && champ->c == core->a[car->pos%MEM_SIZE])
            attroff(A_BOLD | COLOR_PAIR(champ->cc));
        else
            attroff(A_REVERSE | COLOR_PAIR(core->a[car->pos%MEM_SIZE]));

        /*
        refresh();
        */

        pthread_mutex_unlock(&core->m);
    }
}

void    ft_touch_car(t_core *core, t_car *car)
{
    int pos,r,c;
    t_champ *champ;

    if (car->cycle == -1)
        ft_get_n_car_value(core, car);
    if (car->cycle < 2) {
        if (core->v)
        {
            pthread_mutex_lock(&core->m);

            r = 3+((car->pos%MEM_SIZE)/64)%64;
            c = 3+(3*((car->pos%MEM_SIZE)%64))%192;
            attron(COLOR_PAIR(core->a[car->pos%MEM_SIZE]));
            mvprintw(r,c,"%02x", core->arena[car->pos%MEM_SIZE]);
            attroff(COLOR_PAIR(core->a[car->pos%MEM_SIZE]));

            /*
            refresh();
            */

            pthread_mutex_unlock(&core->m);
        }
        if (car->opcode > 0 && car->opcode < 17)
        {
            if (core->v && car->sw)
            {
                pthread_mutex_lock(&core->m);

                car->sw = 0;
                pos = car->rp;
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

                /*
                refresh();
                */
                
                pthread_mutex_unlock(&core->m);
            }
            ft_opcode_switcher(core, car);
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
        car->cycle = -1;
        car->pos++;
        if (core->v)
        {
            pthread_mutex_lock(&core->m);

            champ = ft_get_champ(core, car->id);
            r = 3 + ((car->pos%MEM_SIZE)/64)%64;
            c = 3 + (3*((car->pos%MEM_SIZE)%64))%192;
            // if (champ->cars->opcode == 1 && champ->s_live) // ? champ_id == opcode' id
            if (car->opcode == 1 && car->id == ft_read_4(core, car->pos % MEM_SIZE)) // champ_id == opcode_id
            // if (core->arena[car->pos%MEM_SIZE] == 1 && champ->c == core->a[car->pos%MEM_SIZE]) // champ_id == opcode_id
            // if (car->opcode == 1 && champ->c == core->a[car->pos%MEM_SIZE]) // champ_id == opcode_id
            {
                attron(A_BOLD | COLOR_PAIR(champ->cc));
                // ft_memset(core->a+car->pos%MEM_SIZE, champ->c, 1);
            }
            // else if (champ->cars->opcode == 1)
                // attron(A_BOLD | COLOR_PAIR(core->a[champ->cars->pos%MEM_SIZE]+10));
            // else if (champ->cars->opcode && champ->s_live)
            // {
                // attron(A_REVERSE | COLOR_PAIR(champ->c));
                // ft_memset(core->a+champ->cars->pos%MEM_SIZE, champ->c, 1);
            // }
            else
                attron(A_REVERSE | COLOR_PAIR(core->a[car->pos%MEM_SIZE]));
            //// attron(A_REVERSE);
            mvprintw(r, c, "%02x", core->arena[car->pos%MEM_SIZE]);
            //// attroff(A_REVERSE);
            if (car->opcode == 1 && car->id == ft_read_4(core, car->pos % MEM_SIZE)) // champ_id == opcode_id
            // if (core->arena[car->pos%MEM_SIZE] == 1 && champ->c == core->a[car->pos%MEM_SIZE])
                attroff(A_BOLD | COLOR_PAIR(champ->cc));
            // else if (champ->cars->opcode && champ->s_live)
                // attroff(A_REVERSE | COLOR_PAIR(champ->c));
            else
                attroff(A_REVERSE | COLOR_PAIR(core->a[car->pos%MEM_SIZE]));
            refresh();

            pthread_mutex_unlock(&core->m);
        }
    }
    else
        car->cycle--;
}

void    *myThreadFun(void *ptr)
{
    int     ch;
    t_core  *p;

    p = (t_core*)ptr;
    while ((ch = getch())) // ESC
    // while ((ch = getch()) != 27) // ESC
    {
        if (ch == 27 && (p)->t)
            break ;
        else if (!(p)->p && ch == KEY_F(1)) // F1 - reset speed
        {
            pthread_mutex_lock(&(p)->m);

            (p)->t = 100000;
         
            pthread_mutex_unlock(&(p)->m);
        }
        else if (!(p)->p && (p)->t && ch == KEY_UP) // ARROW UP - speed up
        {
            pthread_mutex_lock(&(p)->m);

            if ((p)->t > 100)
                (p)->t /= 10;
            else
            {
                (p)->t = 0;
                // pthread_exit(NULL);
                // exit(131);
            }

            pthread_mutex_unlock(&(p)->m);
        }
        else if (!(p)->p && (p)->t < 1000000 && ch == KEY_DOWN) // ARROW DOWN - speed down
        {
            pthread_mutex_lock(&(p)->m);

            (p)->t *= 10;

            pthread_mutex_unlock(&(p)->m);
        }
        else if (!(p)->p && (p)->t && ch == ' ') // SPACE - pause
        // else if (!(p)->p && ch == KEY_LEFT) // ARROW LEFT - pause
        {
            pthread_mutex_lock(&(p)->m);
            (p)->p = 1;
            pthread_mutex_unlock(&(p)->m);
        }
        else if ((p)->p && (p)->t && ch == ' ') // SPACE - play
        // else if ((p)->p && ch == KEY_RIGHT) // ARROW RIGHT - play
        {
            pthread_mutex_lock(&(p)->m);
            (p)->p = 0;
            pthread_mutex_unlock(&(p)->m);
        }
    }
    
    pthread_mutex_lock(&(p)->m);

    endwin();
    //SDL_Quit();
    exit(121);

    pthread_mutex_unlock(&(p)->m);

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
    t_car   *tmp;
    pthread_t thread_id;
    pthread_t thread_id2;

    if (core->v)
    {
        pthread_create(&thread_id, NULL, myThreadFun, (void*)core);
        pthread_detach(thread_id);
        pthread_create(&thread_id2, NULL, myThreadFun2, NULL);
        pthread_detach(thread_id2);
        // getch();
        // attron(A_BOLD); mvprintw(3, 200, "** RUNNING **"); attroff(A_BOLD);
        while (core->c_to_die > 0 && core->qt_car > 0) {
            tmp = core->cars;
            core->cycle++;
            while (tmp->next)
                tmp = tmp->next;
            while (tmp) {
                if (tmp->state) {
                    ft_touch_car(core, tmp);
                }
                tmp = tmp->prev;
            }
            do_ncurs(core);
            // attron(A_BOLD); mvprintw(8, 208, "%d", core->cycle);
            // attroff(A_BOLD); refresh();
            if (core->t)
                usleep(core->t);
            // getch();
            //usleep(100000);
            while (core->p)
            {
                pthread_mutex_lock(&core->m);

                attron(A_BOLD);
                mvprintw(3, 200, "** PAUSED ** ");
                attroff(A_BOLD);
                refresh();

                pthread_mutex_unlock(&core->m);

                usleep(100000);
                // continue ;
            }
            if (core->cycle == core->c_to_die + core->last_check) {
                ft_make_check(core);
                core->last_check = core->cycle;
            }
        }
        // do_ncurs(NULL);
        do_ncurs(core);
        if (core->l)
        {
            pthread_mutex_lock(&core->m);

            mvprintw(core->l - 3, 201, "--------------------------------------------------]");

            pthread_mutex_unlock(&core->m);
        }
        pthread_mutex_lock(&core->m);
        attron(A_BOLD); mvprintw(3, 200, "** FINISH ** "); attroff(A_BOLD);
        refresh(); 
        pthread_mutex_unlock(&core->m);

        getch(); endwin(); //SDL_Quit();
    }
    else
    {
        while (core->c_to_die > 0 && core->qt_car > 0) {
            tmp = core->cars;
            core->cycle++;
            while (tmp->next)
                tmp = tmp->next;
            while (tmp) {
                if (tmp->state) {
                    ft_touch_car(core, tmp);
                }
                tmp = tmp->prev;
            }
            if (core->dump != -1 && core->dump == core->cycle) {
                ft_dump(core);
                //ft_free(core); // нужно ли?
                exit(0);
            }
            if (core->cycle == core->c_to_die + core->last_check) {
                ft_make_check(core);
                core->last_check = core->cycle;
            }
        }
        ft_make_check(core);
    }
}
