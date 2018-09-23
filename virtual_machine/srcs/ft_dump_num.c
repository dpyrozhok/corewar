/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dump_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 17:34:03 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/24 00:50:55 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_check.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' \
	|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static int	ft_is_posint(char *str)
{
	long long int	nb;

	nb = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		nb = nb * 10 + (int)*str - '0';
		str++;
		if (nb > INT_MAX)
			return (-1);
	}
	return (int)(nb);
}

static void	ft_is_int(char *str, char *orig)
{
	long long int	nb;
	int				sign;

	nb = 0;
	sign = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		str++;
		sign = 1;
	}
	else if (*str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		nb = nb * 10 + (int)*str - '0';
		str++;
		if (nb > INT_MAX || (sign && -nb < INT_MIN))
			exit(ft_err(13, "Player number is out of 'int' range", orig));
	}
}

void		ft_store_dump(int ac, char **av, int i, t_core *core)
{
	int		dump;

	if (core->dump != -1)
		exit(ft_err(7, "Invalid argument usage", av[i - 1]));
	if (i >= ac)
		exit(ft_err(8, "Missed dump cycle number", NULL));
	if (!ft_is_num(av[i]))
		exit(ft_err(9, "Dump cycle number is not a number", av[i]));
	dump = ft_is_posint(av[i]);
	if (dump == -1)
	{
		ft_err(10, "Dump cycle number is out of positive 'int' range", av[i]);
		exit(10);
	}
	core->dump = dump;
}

void		ft_check_num(int ac, char **av, int i)
{
	if (i >= ac)
		exit(ft_err(11, "Missed player number", NULL));
	if (!ft_is_num(av[i]))
		exit(ft_err(12, "Player number is not a number", av[i]));
	ft_is_int(av[i], av[i]);
}
