#include "corewar.h"
#include "check_args.h"

/*
void	p_usage(void)
{
	ft_printf("usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
	exit(0);
}

void	check_args(int ac, char **av)
{
	int i;

	if (ac == 1)
		p_usage();
	i = 1;
	while (i < ac)
		i++;
}
*/
void ft_dump(unsigned char *arena)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%02x ", arena[i]);
		i++;
		if (i % 64 == 0)
			ft_printf("\n");
	}
}

void    ft_create_car(t_core *core, t_champ *champ, int pos)
{
    t_car   *car;

    car = (t_car *)ft_memalloc(sizeof(t_car));
    car->pos = pos;
    car->id = champ->id;
    car->reg[0] = (unsigned int)champ->id;
    car->opcode = (int)core->arena[pos];
    core->qt_car++;
    if (car->opcode > 0 && car->opcode < 17)
        car->cycle = 0;  // must take value from op.c
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

    shift = 0;
    tmp = core->champs;
    while (tmp) {
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
	core = (t_core *) ft_memalloc(sizeof(t_core));
	core->dump = -1;
	check_args(ac, av, core);
	core->arena = (unsigned char *) malloc(sizeof(unsigned char) * MEM_SIZE);
    core->init_nub = 81;
    core->c_to_die = CYCLE_TO_DIE;
    while(i < ac) {
        fd = open(av[i], O_RDONLY);
        ft_parse_champion(core, fd);
        core->init_nub++;
        i++;
    }
    ft_place_champ(core);
    ft_start_fight(core);
    ft_dump(core->arena);
    return 0;
}