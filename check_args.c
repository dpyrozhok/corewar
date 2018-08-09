//
// Created by Vitalii LEVKO on 8/9/18.
//

typedef struct	s_check
{
	char			buf[4];
	unsigned char	name[PROG_NAME_LENGTH];
	unsigned char	comment[COMMENT_LENGTH];
	unsigned int	size;
	unsigned char	*code;
}				t_check;

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
		write(2, ": ", 2);
		write(2, orig, ft_strlen(orig));
	}
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
	ft_printf("usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
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

void 	check_num(int ac, char **av, int i, t_core *core)
{
	int		num;

	if (i >= ac)
		exit(p_err(105, "Missed player number", NULL));
	if (!is_num(av[i]))
		exit(p_err(106, "Player number is not a number", av[i]));
	is_int(av[i]);
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
	fd = open(str, O_RDONLY);
	return (fd);
}

void	check_file(char *str)
{
	int		fd;
	t_check *file;

	fd = 0;
	while (fd != -1)
	{
		fd = check_dir(str);
		file = (t_check *)malloc(sizeof(t_check));
		read(fd, &file->buf, 4);
		if (file->buf ^ COREWAR_EXEC_MAGIC != 0)
			exit(p_err(109, "Invalid magic bytes", NULL));
		read(fd, &file->name, PROG_NAME_LENGTH);
		read(fd, &file->buf, 4);
		if (file->buf != NULL)
			exit(p_err(110, "Invalid NULL bytes after bot name", NULL));
		read(fd, &file->buf, 4);
		file->size = (unsigned int)((unsigned char)file->buf[0] << 24 | (unsigned char)file->buf[1] << 16 | \
					(unsigned char)file->buf[2] << 8 | (unsigned char)file->buf[3]);
		if (file->size > CHAMP_MAX_SIZE)
			exit(p_err(111, "Exceeded bot max size", NULL));
		read(fd, &file->comment, COMMENT_LENGTH);
		read(fd, &file->buf, 4);
		if (file->bur != NULL)
			exit(p_err(110, "Invalid NULL bytes after bot comment", NULL));
		close(fd);
	}
}

void	check_args(int ac, char **av, t_core *core)
{
	int i;
	int c;

	if (ac == 1)
		p_usage();
	i = 1;
	c = 0;
	while (i < ac)
	{
		if (c > MAX_ARGS_NUMBER)
			exit(p_err(100, "Exceeded number of args", av[i]));
		if (!ft_strcmp(av[i], "-dump"))
			store_dump(ac, av, ++i, core);
		else if (!ft_strcmp(av[i], "-n"))
			check_num(ac, av, ++i, core);
		else
			check_file(av[i]);
		i++;
		c++;
	}
}
