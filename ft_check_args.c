/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_check_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 12:43:28 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/22 17:33:01 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_args.h"

static int	ft_is_arg(int ac, char **av, t_core *core, int *i)
{
	if (!ft_strcmp(av[*i], "-v"))
	{
		core->vis = 1;
		return (1);
	}
	else if (!ft_strcmp(av[*i], "-dump"))
	{
		ft_store_dump(ac, av, ++(*i), core);
		return (1);
	}
	else if (!ft_strcmp(av[*i], "-n"))
	{
		ft_check_num(ac, av, ++(*i));
		return (1);
	}
	return (0);
}

static void	ft_print_usage(void)
{
	ft_printf("usage: ./corewar [-help | [-v] [-dump nbr_cycles] "
		"[[-n number] champion1.cor] ...]\n");
	exit(0);
}

static void	ft_help(void)
{
	int		fd;
	int		ret;

	fd = open("man/corewar.man", O_RDONLY);
	if (fd == -1)
		exit(ft_err(1, "Cannot access the man file", "man/corewar.man"));
	ret = ft_print_help(0, 0, fd, '\0');
	close(fd);
	exit(ret);
}

void	ft_check_args(int ac, char **av, t_core *core, int args)
{
	int		i;
	int		bots;

	if (ac == 1)
		ft_print_usage();
	i = 1;
	bots = 0;
	while (i < ac)
	{
		if (args > MAX_ARGS_NUMBER)
			exit(ft_err(100, "Exceeded number of args", av[i]));
		if (!ft_strcmp(av[i], "-help"))
			ft_help();
		else if (ft_is_arg(ac, av, core, &i))
			args++;
		else
			ft_check_file(av[i], &bots, NULL);
		i++;
	}
	if (core->vis && core->dump != -1)
		exit(ft_err(118, "Invalid arguments usage", NULL));
	if (!bots)
		exit(ft_err(119, "Missed bot file", NULL));
	else if (bots > MAX_PLAYERS)
		exit(ft_err(120, "Exceeded number of bots", ft_itoa(bots)));
}
