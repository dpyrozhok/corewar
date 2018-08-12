//
// Created by Vitalii LEVKO on 8/9/18.
//

#include "check_args.h"
#include "ncurs.h"
void	op(void);

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' \
	|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int		p_err(int ret, char *str, char *orig)
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

int		is_num(char *str)
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

int 	is_posint(char *str)
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

void	is_int(char *str, char *orig)
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
			exit(p_err(107, "Player number is out of 'int' range", orig));
	}
}

void	p_usage(void)
{
	ft_printf("usage: ./corewar [-help | [-v] [-dump nbr_cycles] [[-n number] champion1.cor] ...]\n");
	exit(0);
}

void	store_dump(int ac, char **av, int i, t_core *core)
{
	int		dump;

	if (core->dump != -1)
		exit(p_err(101, "Invalid argument usage", av[i - 1]));
	if (i >= ac)
		exit(p_err(102, "Missed dump cycle number", NULL));
	if (!is_num(av[i]))
		exit(p_err(103, "Dump cycle number is not a number", av[i]));
	dump = is_posint(av[i]);
	if (dump == -1)
		exit(p_err(104, "Dump cycle number is out of positive 'int' range", av[i]));
	core->dump = dump;
}

void 	check_num(int ac, char **av, int i)
{
	if (i >= ac)
		exit(p_err(105, "Missed player number", NULL));
	if (!is_num(av[i]))
		exit(p_err(106, "Player number is not a number", av[i]));
	is_int(av[i], av[i]);
}

int		str_inc(const char *haystack, const char *needle)
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

void	check_filename(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 5)
		exit(p_err(112, "Invalid file type", str));
	if (!str_inc(str, ".cor"))
		exit(p_err(113, "Invalid file type", str));
}

int	check_dir(char *str)
{
	int		fd;

	fd = open(str, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		exit(p_err(108, "Argument is not a file", str));
	}
	check_filename(str);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		exit(p_err(2, "Unable to open file", str));
	return (fd);
}

void	check_null(t_check *file)
{
	int i;

	if (file->ret != 4)
		exit(p_err(116, "Bot NULL bytes length mismatch", ft_itoa((int)file->ret)));
	i = 0;
	while(i < 4)
	{
		if (file->buf[i] != '\0')
			exit(p_err(110, "Invalid NULL bytes", NULL));
		i++;
	}
}

void	check_bot_name(t_check *file)
{
	int		i;
	char *str;

	if (file->ret != PROG_NAME_LENGTH)
		exit(p_err(114, "Bot name length mismatch", ft_itoa((int)file->ret)));
	i = 0;
	while(i < PROG_NAME_LENGTH)
	{
		str = ft_strchr(LABEL_CHARS, file->name[i]);
		if (str == NULL)
			exit(p_err(113, "Invalid character in the bot name", file->name));
		i++;
	}
}

void	check_file(char *str)
{
	int		fd;
	t_check *file;

	fd = check_dir(str);
	file = (t_check *)ft_memalloc(sizeof(t_check));
	file->ret = read(fd, &file->buf, 4);
	file->size = (unsigned int)((unsigned char)file->buf[0] << 24 | (unsigned char)file->buf[1] << 16 | \
		(unsigned char)file->buf[2] << 8 | (unsigned char)file->buf[3]);
	if (file->ret != 4 || file->size != COREWAR_EXEC_MAGIC)
		exit(p_err(109, "Invalid magic bytes", NULL));
	file->ret = read(fd, &file->name, PROG_NAME_LENGTH);
	check_bot_name(file);
	file->ret = read(fd, &file->buf, 4);
	check_null(file);
	file->ret = read(fd, &file->buf, 4);
	if (file->ret != 4)
		exit(p_err(116, "Bot max size length mismatch", ft_itoa((int)file->ret)));
	file->size = (unsigned int)((unsigned char)file->buf[0] << 24 | (unsigned char)file->buf[1] << 16 | \
				(unsigned char)file->buf[2] << 8 | (unsigned char)file->buf[3]);
	if (file->size > CHAMP_MAX_SIZE)
		exit(p_err(110, "Exceeded bot max size", NULL));
	file->ret = read(fd, &file->comment, COMMENT_LENGTH);
	if (file->ret != COMMENT_LENGTH)
		exit(p_err(115, "Bot comment length mismatch", ft_itoa((int)file->ret)));
	file->ret = read(fd, &file->buf, 4);
	check_null(file);
	file->ret = read(fd, &file->code, CHAMP_MAX_SIZE);
	if (file->ret != file->size)
		exit(p_err(116, "Bot size mismatch", ft_itoa((int)file->ret)));
	ft_strclr(file->buf);
	file->ret = read(fd, &file->buf, 1);
	if (file->ret > 0)
		exit(p_err(112, "Invalid bot size", NULL));
	close(fd);
}

void	check_args(int ac, char **av, t_core *core)
{
	int i;
	int c;
	int fd;

	if (ac == 1)
		p_usage();
	i = 1;
	c = 0;
	while (i < ac)
	{
		if (c > MAX_ARGS_NUMBER)
			exit(p_err(100, "Exceeded number of args", av[i]));
		if (!ft_strcmp(av[i], "-help"))
		{
			fd = open("man/corewar.man", O_RDONLY);
			if (fd == -1)
				exit(p_err(1, "Cannot access the man file", "man/corewar.man"));
			i = p_help(0, 0, fd, '\0');
			close(fd);
			exit(i);
		}
		else if (!ft_strcmp(av[i], "-v"))
		{
			c++;
			do_more();
			exit(0);
		}
		else if (!ft_strcmp(av[i], "-dump"))
		{
			c++;
			store_dump(ac, av, ++i, core);
		}
		else if (!ft_strcmp(av[i], "-n"))
		{
			c++;
			check_num(ac, av, ++i);
		}
		else if (!ft_strcmp(av[i], "-op"))
		{
			op();
		}
		else
			check_file(av[i]);
		i++;
	}
}

void	op(void)
{
	printf("%s\n", op_tab[0].exp);
	exit(0);
}