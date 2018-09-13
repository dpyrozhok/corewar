#include "corewar.h"
#include "check_args.h"

void   ft_introduce(t_core *core)
{
    int j;
    t_champ             *tmp;

    j = 1;
    ft_printf("Introducing contestants...");
    tmp = core->champs;
    while (tmp) {
        ft_printf("\n* Player %i, weighing %i bytes, \"%s\" (\"%s\") !", j, tmp->size, tmp->name, tmp->comment);
        // printf("\n* Player %i, weighing %i bytes, \"%s\" (\"%s\") !", j, tmp->size, tmp->name, tmp->comment);
        j++;
        tmp = tmp->next;
    }
}

void ft_dump(t_core *core)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
        if (i % 64 == 0) {
            ft_printf("\n%#06x : ", i);
        }
		ft_printf("%02x ", core->arena[i]);
		i++;
	}
	ft_printf("\n");
}

void    ft_copy_car(t_core *core, t_car *src, int pos)
{
	t_champ *champ;
    t_car   *car;
	t_car   *tmp;
    int     i;
    int	r,c;

    i = 0;
    car = (t_car *)ft_memalloc(sizeof(t_car));
    car->pos = pos;
	car->rp = 0;
	car->sw = 0;
	car->carry = src->carry;
	car->id = src->id;
	if (core->v)
	{
        pthread_mutex_lock(&core->m);

		champ = ft_get_champ(core, car->id);
		r = 3 + ((pos%MEM_SIZE)/64)%64;
		c = 3 + (3*((pos%MEM_SIZE)%64))%192;
		attron(COLOR_PAIR(champ->c));
		attron(A_REVERSE);
		mvprintw(r, c, "%02x", core->arena[pos]);
		attroff(A_REVERSE);
		attroff(COLOR_PAIR(champ->c));
	    

	    //refresh();

    
        pthread_mutex_unlock(&core->m);
	}
	car->state = src->state;
    car->live = src->live;
	while (i < REG_NUMBER) {
		car->reg[i] = src->reg[i];
		i++;
	}
	core->qt_car++;
	car->cycle = -1;
	car->opcode = 0;
	tmp = core->cars;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = car;
	if (tmp->num == 118)
    {}
    car->num = tmp->num + 1;
	car->prev = tmp;
}

void    ft_create_car(t_core *core, t_champ *champ, int pos)
{
	t_car   *car;
	t_car   *tmp;

	car = (t_car *)ft_memalloc(sizeof(t_car));

	car->sw = 0;
	car->rp = 0;
    car->pos = pos;
    car->state = 1;
    car->id = champ->id;
    car->reg[0] = (unsigned int)champ->id;
    core->qt_car++;
    car->next = NULL;
    car->prev = NULL;
    car->cycle = -1;
    car->num = 1;
    if (core->cars)
    {
        tmp = core->cars;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = car;
        car->num = tmp->num + 1;
        car->prev = tmp;
    }
    else
        core->cars = car;
}

void    ft_place_champ(t_core *core)
{
	t_champ *tmp;
	int    shift;
	unsigned int i, r, c;

	shift = 0;
	tmp = core->champs;
	if (core->v)
	{
		init_ncurs(core);
		do_ncurs(core);
	}
	while (tmp) {
		if (core->v)
		{
            pthread_mutex_lock(&core->m);

			attron(COLOR_PAIR(tmp->c));
			i = 0;
			r = 3 + (shift / 64);
			c = 3 + 3*(shift % 64);
			while (i < tmp->size)
			{
				mvprintw(r, c, "%02x", tmp->code[i]);
				if ((1+i + shift%64) % 64 == 0 && !(i == 0 && shift == 0))
				{
					c = 3;
					r++;
				}
				else
					c += 3;
				i++;
			}
			attroff(COLOR_PAIR(tmp->c));
			ft_memset(core->a + shift, tmp->c, tmp->size);


			refresh();


            pthread_mutex_unlock(&core->m);
		}
		ft_memcpy(core->arena + shift, tmp->code, tmp->size);
		ft_create_car(core, tmp, shift);
		shift += MEM_SIZE / core->qt_champ;
		tmp = tmp->next;
	}
}

void    ft_parse_champion(t_core *core, int fd)
{
	char                buf[4];
	unsigned int        size;
	t_champ             *champ;
	t_champ             *tmp;

	champ = (t_champ *)ft_memalloc(sizeof(t_champ));
	read(fd, &buf, 4);
	ft_memset(&champ->name, '\0', PROG_NAME_LENGTH + 1);
	read(fd, &champ->name, PROG_NAME_LENGTH);
	champ->name[PROG_NAME_LENGTH] = '\0';
	read(fd, &buf, 4);
	read(fd, &buf, 4);
	size = (unsigned int)((unsigned char)buf[0] << 24 | (unsigned char)buf[1] << 16 | (unsigned char)buf[2] << 8 | (unsigned char)buf[3]);
	champ->size = size;
	ft_memset(&champ->comment, '\0', COMMENT_LENGTH + 1);
	read(fd, &champ->comment, COMMENT_LENGTH);
	champ->comment[COMMENT_LENGTH] = '\0';
	read(fd, &buf, 4);
	champ->code = (unsigned char *)ft_memalloc(sizeof(unsigned char) * champ->size);
	read(fd, champ->code, champ->size);
	core->qt_champ++;
	champ->id = core->init_nub;
	champ->c = 20 + core->c++;
	core->c = core->c % 4;
	champ->cc = champ->c+10;
	champ->s_live = 0;
    champ->all_live = 0;
	if (!core->champs)
		core->champs = champ;
	else
	{
		tmp = core->champs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = champ;
	}
}

void ft_free(t_core *core)
{
    t_champ *champ;
    t_car   *car;

    while (core->champs)
    {
        free(core->champs->code);
        champ = core->champs->next;
        free(core->champs);
        core->champs = champ;
    }
    while (core->cars)
    {
        car = core->cars->next;
        free(core->cars);
        core->cars = car;
    }
    free(core->arena);
    free(core->a);
    free(core);
}

void    ft_winner_is(t_core *core)
{
    int i;
    t_champ *champ;

    i = 0;
    champ = core->champs;
    while (champ) {
        i++;
        if (champ->id == core->winner_id)
            ft_printf("\nContestant %i, \"%s\", has won !\n", i, champ->name);
        champ = champ->next;
    }
}

int main(int ac, char **av)
{
	t_core *core;
	int i;
	int fd;

	i = 1;
	//setbuf(stdout, 0);
	core = (t_core *)ft_memalloc(sizeof(t_core));
	core->dump = -1;
	core->c = 0;
	core->l = 0;
	core->t = 100000;
	core->p = 0;
	check_args(ac, av, core);
	core->arena = (unsigned char *)ft_memalloc(sizeof(unsigned char) * MEM_SIZE);
	core->a = (unsigned char *)ft_memalloc(sizeof(unsigned char) * MEM_SIZE);
	core->init_nub = 0;
	core->c_to_die = CYCLE_TO_DIE;
	while(i < ac) {
		fd = open(av[i], O_RDONLY);
		if (fd != -1)
		{
			core->init_nub--;
			ft_parse_champion(core, fd);
		}
		i++;
	}
	if (!core->v)
        ft_introduce(core);
	ft_place_champ(core);
	ft_start_fight(core);
    if (!core->v)
	    ft_winner_is(core);
	ft_free(core);
	//system("leaks corewar");
	return 0;
}
