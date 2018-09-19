/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 17:44:03 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/19 13:18:37 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_args.h"

int		ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' \
	|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int		ft_err(int ret, char *str, char *orig)
{
	write(2, str, ft_strlen(str));
	if (orig)
	{
		write(2, ": '", 3);
		write(2, orig, ft_strlen(orig));
		write(2, "'\n", 2);
	}
	else
		write(2, "\n", 1);
	return (ret);
}

int		ft_is_num(char *str)
{
	if (str)
	{
		if (*str == '-' || *str == '+')
			str++;
		if (!*str)
			return (0);
		while (*str)
		{
			if (!ft_isdigit(*str))
				return (0);
			str++;
		}
		return (1);
	}
	return (0);
}

int		ft_is_posint(char *str)
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

void	ft_is_int(char *str, char *orig)
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
			exit(ft_err(107, "Player number is out of 'int' range", orig));
	}
}

void	ft_print_usage(void)
{
	ft_printf("usage: ./corewar [-help | [-v] [-dump nbr_cycles] "
		"[[-n number] champion1.cor] ...]\n");
	exit(0);
}

void	ft_store_dump(int ac, char **av, int i, t_core *core)
{
	int		dump;

	if (core->dump != -1)
		exit(ft_err(101, "Invalid argument usage", av[i - 1]));
	if (i >= ac)
		exit(ft_err(102, "Missed dump cycle number", NULL));
	if (!ft_is_num(av[i]))
		exit(ft_err(103, "Dump cycle number is not a number", av[i]));
	dump = ft_is_posint(av[i]);
	if (dump == -1)
	{
		ft_err(104, "Dump cycle number is out of positive 'int' range", av[i]);
		exit(104);
	}
	core->dump = dump;
}

void	ft_check_num(int ac, char **av, int i)
{
	if (i >= ac)
		exit(ft_err(105, "Missed player number", NULL));
	if (!ft_is_num(av[i]))
		exit(ft_err(106, "Player number is not a number", av[i]));
	ft_is_int(av[i], av[i]);
}

int		ft_str_include(const char *haystack, const char *needle)
{
	const char	*h;
	const char	*n;

	while (*haystack)
	{
		if (*haystack == *needle)
		{
			h = haystack;
			n = needle;
			while (*h)
			{
				if (*h != *n)
					break ;
				h++;
				n++;
			}
			if (!*n && !*h)
				return (1);
		}
		haystack++;
	}
	return (0);
}

void	ft_check_filename(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 5)
		exit(ft_err(112, "Invalid file type", str));
	if (!ft_str_include(str, ".cor"))
		exit(ft_err(113, "Invalid file type", str));
}

int		ft_check_dir(char *str)
{
	int		fd;

	fd = open(str, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		exit(ft_err(108, "Argument is not a file", str));
	}
	ft_check_filename(str);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		exit(ft_err(2, "Unable to open file", str));
	return (fd);
}

void	ft_check_null(t_check *file)
{
	int i;

	if (file->ret != 4)
	{
		ft_err(116, "Bot NULL bytes length mismatch", ft_itoa((int)file->ret));
		exit(116);
	}
	i = 0;
	while (i < 4)
	{
		if (file->buf[i] != '\0')
			exit(ft_err(110, "Invalid NULL bytes", NULL));
		i++;
	}
}

void	ft_check_size(int fd, t_check **file)
{
	(*file)->size = (unsigned int)((unsigned char)(*file)->buf[0] << 24 \
		| (unsigned char)(*file)->buf[1] << 16 \
		| (unsigned char)(*file)->buf[2] << 8 \
		| (unsigned char)(*file)->buf[3]);
	if ((*file)->size > CHAMP_MAX_SIZE)
		exit(ft_err(110, "Exceeded bot max size", NULL));
	(*file)->ret = read(fd, &(*file)->comment, COMMENT_LENGTH);
	if ((*file)->ret != COMMENT_LENGTH)
	{
		ft_err(115, "Bot comment length mismatch", ft_itoa((int)(*file)->ret));
		exit(115);
	}
	(*file)->ret = read(fd, &(*file)->buf, 4);
	ft_check_null((*file));
	(*file)->code = (unsigned char *)ft_memalloc(sizeof(unsigned char) * \
		(*file)->size);
	(*file)->ret = read(fd, (*file)->code, CHAMP_MAX_SIZE);
	if ((*file)->ret != (*file)->size)
		exit(ft_err(117, "Bot size mismatch", ft_itoa((int)(*file)->ret)));
	ft_strclr((*file)->buf);
	(*file)->ret = read(fd, &(*file)->buf, 1);
	if ((*file)->ret > 0)
		exit(ft_err(112, "Invalid bot size", NULL));
	free((*file)->code);
	free(*file);
}

void	ft_check_file(char *str, int *bots, t_check *file)
{
	int		fd;

	fd = ft_check_dir(str);
	file = (t_check *)ft_memalloc(sizeof(t_check));
	file->ret = read(fd, &file->buf, 4);
	file->size = (unsigned int)((unsigned char)file->buf[0] << 24 \
		| (unsigned char)file->buf[1] << 16 \
		| (unsigned char)file->buf[2] << 8 \
		| (unsigned char)file->buf[3]);
	if (file->ret != 4 || file->size != COREWAR_EXEC_MAGIC)
		exit(ft_err(109, "Invalid magic bytes", NULL));
	file->ret = read(fd, &file->name, PROG_NAME_LENGTH);
	if (file->ret != PROG_NAME_LENGTH)
		exit(ft_err(114, "Bot name length mismatch", ft_itoa((int)file->ret)));
	file->ret = read(fd, &file->buf, 4);
	ft_check_null(file);
	file->ret = read(fd, &file->buf, 4);
	if (file->ret != 4)
	{
		ft_err(116, "Bot max size length mismatch", ft_itoa((int)file->ret));
		exit(116);
	}
	ft_check_size(fd, &file);
	close(fd);
	*bots += 1;
}

void	ft_help(void)
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

int		ft_is_arg(int ac, char **av, t_core *core, int *i)
{
	if (!ft_strcmp(av[*i], "-v"))
	{
		core->v = 1;
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
	if (core->v && core->dump != -1)
		exit(ft_err(118, "Invalid arguments usage", NULL));
	if (!bots)
		exit(ft_err(119, "Missed bot file", NULL));
	else if (bots > MAX_PLAYERS)
		exit(ft_err(120, "Exceeded number of bots", ft_itoa(bots)));
}
