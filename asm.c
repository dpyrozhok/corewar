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
int g_fd1;

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

int	ft_change(int ch)
{
	int		new;

	new = ch & 0xff;
	ch = (ch & 0xff00) / 0xff;
	ch = ch + (new * 0x100);
	return (ch);
}

int		convert_end(int new)
{
	int ch;

	if (is_little() == 1)
	{
		ch = new & 0xffff;
		new = (new & 0xffff0000) / 0xffff;
		ch = ft_change(ch) * 0x10000;
		new = ft_change(new) + ch;
	}
	return (new);
}

void		ft_read_file(char *name)
{
	int su = convert_end(COREWAR_EXEC_MAGIC);
    char *line;
	if ((g_fd = open(name, O_WRONLY | O_CREAT | O_TRUNC,
					   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		ft_printf("error: open\n");
		exit(1);
	}
	write(g_fd, &su, sizeof(su));
    int fd;


    /// CHECK IMENI
    fd = open("zork.s", O_RDONLY);

    get_next_line(fd, &line);
    line = ft_strchr(line, '\"') + 1;
    int i = 0;
    char newline[132] = {0};
    while (line[i] != '\"')
    {
        newline[i] = line[i];
        i++;
    }
    char *botsize = "a"; // botsize nujno budet naiti!!!!!!!!!!!!!!!!!!!!!!!!!!!
    write(g_fd, &newline,sizeof(newline));
    write(g_fd, &(botsize), sizeof(2)); // botsize nujno budet naiti!!!!!!!!!!!!!!!!!!!!!!!!!!!


    /// CHECK COMMENTA
    char comment[2052] = {0};
    get_next_line(fd, &line);
    line = ft_strchr(line, '\"') + 1;

   i = 0;
    while (line[i] != '\"')
    {
        comment[i] = line[i];
        i++;
    }
    write(g_fd, &comment,sizeof(comment));
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