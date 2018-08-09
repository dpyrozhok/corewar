#include <stdio.h>
#include <fcntl.h>
#include "corewar.h"

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

void ft_parse_champion(t_core *core, int fd)
{
	int i;
	char buf[4];
	unsigned int size;
	t_champ *champ;

	champ = (t_champ *) ft_memalloc(sizeof(t_champ));
	read(fd, &buf, 4);
	read(fd, &champ->name, PROG_NAME_LENGTH + 1);
	read(fd, &buf, 3);
	read(fd, &buf, 4);
	size = (unsigned int) ((unsigned char) buf[0] << 24 | (unsigned char) buf[1] << 16 | (unsigned char) buf[2] << 8 |
						   (unsigned char) buf[3]);
	champ->size = size;
	read(fd, &champ->comment, COMMENT_LENGTH + 1);
	read(fd, &buf, 3);
	champ->code = (unsigned char *) ft_memalloc(sizeof(unsigned char) * champ->size);
	read(fd, champ->code, champ->size);
	ft_printf("%s\n", champ->name);
	ft_printf("%s\n", champ->comment);
	ft_printf("%u\n", champ->size);
	i = 0;
	while (i < champ->size)
	{
		ft_printf("%02x ", champ->code[i]);
		i++;
		if (i % 64 == 0)
			ft_printf("\n");
	}
	ft_printf("\n");
	core->champs = champ;
}

int main(int ac, char **av)
{
	t_core *core;
	int i;
	int fd;

	check_args(ac, av);
	i = 0;
	setbuf(stdout, 0);
	core = (t_core *) ft_memalloc(sizeof(t_core));
	core->arena = (unsigned char *) malloc(sizeof(unsigned char) * MEM_SIZE);
	fd = open(av[1], O_RDONLY);
	ft_parse_champion(core, fd);
	// ft_dump (core->arena);
	return 0;
}