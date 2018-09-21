#include "corewar.h"
#include "check_args.h"

void	ft_introduce(t_core *core)
{
	int		j;
	t_champ	*tmp;

	j = 1;
	ft_printf("Introducing contestants...");
	tmp = core->champs;
	while (tmp)
	{
		ft_printf("\n* Player %i, weighing %i bytes, \"%s\" (\"%s\") !", j, \
			tmp->size, tmp->name, tmp->comment);
		j++;
		tmp = tmp->next;
	}
}

void	ft_dump(t_core *core)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
		{
			ft_printf("\n%#06x : ", i);
		}
		ft_printf("%02x ", core->arena[i]);
		i++;
	}
	ft_printf("\n");
}

void	ft_append_car(t_core *core, t_car *car)
{
	t_car	*tmp;

	tmp = core->cars;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = car;
	// if (tmp->num == 118)
	// {}
	car->num = tmp->num + 1;
	car->prev = tmp;
}

void	ft_copy_car(t_core *core, t_car *src, int pos)
{
	t_car	*car;
	int		i;

	i = 0;
	car = (t_car *)ft_memalloc(sizeof(t_car));
	car->pos = pos;
	car->pos_res = 0;
	car->sw = 0;
	car->carry = src->carry;
	car->id = src->id;
	if (core->vis)
		ft_vcars_fork(core, car, pos);
	car->state = src->state;
	car->live = src->live;
	while (i < REG_NUMBER)
	{
		car->reg[i] = src->reg[i];
		i++;
	}
	core->qt_car++;
	car->cycle = -1;
	car->opcode = 0;
	ft_append_car(core, car);
}

void	ft_create_car(t_core *core, t_champ *champ, int pos, t_car *tmp)
{
	t_car	*car;

	car = (t_car *)ft_memalloc(sizeof(t_car));
	car->sw = 0;
	car->pos_res = 0;
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
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = car;
		car->num = tmp->num + 1;
		car->prev = tmp;
	}
	else
		core->cars = car;
}

void	ft_place_champ(t_core *core)
{
	int		j;
	t_champ	*tmp;
	int		shift;

	shift = 0;
	j = 0;
	tmp = core->champs;
	if (core->vis)
	{
		ft_init_screen(core, 0, 3, 3);
		ft_draw(core);
	}
	while (tmp)
	{
		if (core->vis)
			ft_champ_visual(core, tmp, shift);
		j++;
		tmp->num = j;
		ft_memcpy(core->arena + shift, tmp->code, tmp->size);
		ft_create_car(core, tmp, shift, NULL);
		shift += MEM_SIZE / core->qt_champ;
		core->winner_id = tmp->id;
		tmp = tmp->next;
	}
}

void	ft_init_champ(t_core *core, t_champ *champ)
{
	champ->id = core->init_nub;
	champ->col = 20 + core->col_mod++;
	core->col_mod = core->col_mod % 4;
	champ->col_live = champ->col + 10;
	champ->s_live = 0;
	champ->all_live = 0;
}

void	ft_append_champ(t_core *core, t_champ *champ)
{
	t_champ	*tmp;

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

void	ft_parse_champion(t_core *core, int fd)
{
	char			buf[4];
	unsigned int	size;
	t_champ			*champ;

	champ = (t_champ *)ft_memalloc(sizeof(t_champ));
	read(fd, &buf, 4);
	ft_memset(&champ->name, '\0', PROG_NAME_LENGTH + 1);
	read(fd, &champ->name, PROG_NAME_LENGTH);
	champ->name[PROG_NAME_LENGTH] = '\0';
	read(fd, &buf, 4);
	read(fd, &buf, 4);
	size = (unsigned int)((unsigned char)buf[0] << 24 \
		| (unsigned char)buf[1] << 16 | (unsigned char)buf[2] << 8 \
		| (unsigned char)buf[3]);
	champ->size = size;
	ft_memset(&champ->comment, '\0', COMMENT_LENGTH + 1);
	read(fd, &champ->comment, COMMENT_LENGTH);
	champ->comment[COMMENT_LENGTH] = '\0';
	read(fd, &buf, 4);
	champ->code = (unsigned char *)ft_memalloc(sizeof(unsigned char) * \
		champ->size);
	read(fd, champ->code, champ->size);
	core->qt_champ++;
	ft_init_champ(core, champ);
	ft_append_champ(core, champ);
}

void	ft_free(t_core *core)
{
	t_champ	*champ;
	t_car	*car;

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
	free(core->a_col);
	free(core);
}

void	ft_winner_is(t_core *core)
{
	t_champ	*champ;

	champ = core->champs;
	while (champ)
	{
		if (champ->id == core->winner_id)
			ft_printf("\nContestant %i, \"%s\", has won !\n", \
				champ->num, champ->name);
		champ = champ->next;
	}
}

void	ft_init_core(t_core *core, int ac, char **av)
{
	core->dump = -1;
	core->col_mod = 0;
	core->last_break = 0;
	core->microsec = 100000;
	core->pas = 0;
	core->fin = 0;
	ft_check_args(ac, av, core, 0);
	core->arena = (unsigned char *)ft_memalloc(sizeof(unsigned char) * \
		MEM_SIZE);
	core->a_col= (unsigned char *)ft_memalloc(sizeof(unsigned char) * MEM_SIZE);
	core->init_nub = 0;
	core->c_to_die = CYCLE_TO_DIE;
}

int		main(int ac, char **av)
{
	t_core	*core;
	int		i;
	int		fd;

	i = 1;
	//setbuf(stdout, 0);
	core = (t_core *)ft_memalloc(sizeof(t_core));
	ft_init_core(core, ac, av);
	while (i < ac)
	{
		fd = open(av[i], O_RDONLY);
		if (fd != -1)
		{
			core->init_nub--;
			ft_parse_champion(core, fd);
		}
		i++;
	}
	if (!core->vis)
		ft_introduce(core);
	ft_place_champ(core);
	ft_start_fight(core);
	if (!core->vis)
		ft_winner_is(core);
	ft_free(core);
	//system("leaks corewar");
	return (0);
}
