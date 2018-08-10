/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 13:13:07 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/08/09 13:13:09 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "asm.h"

int g_fd;

int		ft_check_format(char *name)
{
    char *format;

    format = ft_strchr(name, '.');
    if (ft_strcmp(format, ".s") == 0)
        return (1);
    else
        return (0);
}

char		*ft_get_name(char *name)
{
	char	*get;
	int		i;
	char	*tmp;

	i = 0;
	while (name[i] != '.')
		i++;
	get = malloc(sizeof(char) * i);
	ft_strncpy(get, name, i);
	tmp = get;
	get = ft_strjoin(get, ".cor");
	free(tmp);
	return (get);
}

static int	is_little(void)
{
	char		a;

	a = 1;
	if (a >> 2 == 0)
		return (1);
	return (0);
}

static int	swap_two_octets(int nb)
{
	int		tmp;

	tmp = nb & 0xff;
	nb = (nb & 0xff00) / 0xff;
	nb = nb + (tmp * 0x100);
	return (nb);
}

int		little_to_big_endian(int nb)
{
	int tmp;

	if (is_little() == 1)
	{
		tmp = nb & 0xffff;
		nb = (nb & 0xffff0000) / 0xffff;
		tmp = swap_two_octets(tmp) * 0x10000;
		nb = swap_two_octets(nb) + tmp;
	}
	return (nb);
}

void		ft_read_file(char *name)
{
	int su = little_to_big_endian(COREWAR_EXEC_MAGIC);
	if ((g_fd = open(name, O_WRONLY | O_CREAT | O_TRUNC,
					   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		ft_printf("error: open\n");
		exit(1);
	}
	write(g_fd, &su, sizeof(su));
}

int		main(int ac, char **av)
{
	char *name;

	if (ac < 2 || ac > 3)
		return (ft_printf("Invalid number of arguements")); // inform invalid number of arguement
	if (!ft_check_format(av[1]))
		return(ft_printf("Can't read source file\n"));
	else
		name = ft_get_name(av[1]);
	ft_read_file(name);
	ft_printf("Writing output program to %s", name);
	free(name);
	return (0);
}