#include "corewar.h"
#include "check_args.h"

void ft_dump(t_core *core)
{
	int i;

	i = 0;
	ft_printf("Cycle: %i\n", core->cycle);
	ft_printf("\n");
	while (i < MEM_SIZE)
	{
		ft_printf("%02x ", core->arena[i]);
		i++;
		if (i % 64 == 0)
			ft_printf("\n");
	}
	ft_printf("\n");
}

void    ft_create_car(t_core *core, t_champ *champ, int pos)
{
	t_car   *car;
	int r,c;

	car = (t_car *)ft_memalloc(sizeof(t_car));
	if (core->v)
	{
		r = 3 + (pos/64);
		c = 3 + 3*(pos%64);
		attron(COLOR_PAIR(core->a[pos]));
		// attron(COLOR_PAIR(champ->c));
		attron(A_REVERSE);
		mvprintw(r, c, "%02x", core->arena[pos]);
		attroff(A_REVERSE);
		// attroff(COLOR_PAIR(champ->c));
		attroff(COLOR_PAIR(core->a[pos]));
		refresh();
	}
	car->pos = pos;
	car->id = champ->id;
	car->reg[0] = (unsigned int)champ->id;
	car->opcode = (int)core->arena[pos];
	core->qt_car++;
	if (car->opcode > 0 && car->opcode < 17)
		car->cycle = op_tab[car->opcode - 1].cycle;  // must take value from op.c
	if (champ->cars) {
		car->prev = champ->cars->prev;
		car->next = champ->cars;
		champ->cars->prev->next = car;
		champ->cars->prev = car;
	}
	else
	{
		champ->cars = car;
		car->next = car;
		car->prev = car;
	}
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
		init_ncurs();
		do_ncurs(core);
	}
	while (tmp) {
		if (core->v)
		{
			attron(COLOR_PAIR(tmp->c));
			i = 0;
			r = 3 + (shift / 64);
			c = 3 + 3*(shift % 64);
			while (i < tmp->size)
			{
				mvprintw(r, c, "%02x ", tmp->code[i]);
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
	read(fd, &champ->name, PROG_NAME_LENGTH);
	champ->name[PROG_NAME_LENGTH] = '\0';
	read(fd, &buf, 4);
	read(fd, &buf, 4);
	size = (unsigned int)((unsigned char)buf[0] << 24 | (unsigned char)buf[1] << 16 | (unsigned char)buf[2] << 8 | (unsigned char)buf[3]);
	champ->size = size;
	read(fd, &champ->comment, COMMENT_LENGTH);
	champ->comment[COMMENT_LENGTH] = '\0';
	read(fd, &buf, 4);
	champ->code = (unsigned char *)ft_memalloc(sizeof(unsigned char) * champ->size);
	read(fd, champ->code, champ->size);
	core->qt_champ++;
	champ->id = core->init_nub;
	champ->c = core->c++;
	champ->cc = champ->c+10; // сделать по % мод чтоб переворачивался цвет
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

int main(int ac, char **av)
{
	t_core *core;
	int i;
	int fd;

	i = 1;
	setbuf(stdout, 0);
	core = (t_core *)ft_memalloc(sizeof(t_core));
	core->dump = -1;
	core->c = 20;
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
	ft_place_champ(core);
	ft_start_fight(core);
	return 0;
}
