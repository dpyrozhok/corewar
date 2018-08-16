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

char	*ft_go_space(char *line, int *x)
{
	while (*line && (*line == ' ' || *line == '\t'))
	{
		line++;
		(*x)++;
	}
	return (line);
}

void	ft_write_name_comment(char **buf, char *line, char *define, t_my inf)
{
	int		i;
	int 	max_i;

	i = 0;
	max_i = (*(define + 1) == 'n') ? PROG_NAME_LENGTH - 1 : COMMENT_LENGTH - 1;
	while (line[i] && line[i] != '"')
	{
		if (i >= max_i)
		{
			ft_printf("Lexical error[TOKEN][%i:%i]. Too big %s\n", inf.y, inf.x, define + 1);
			exit(1);
		}
		(*buf)[i] = line[i];
		if (line[i] =='\\')
		{
			i++;
			inf.x++;
			(*buf)[i] = line[i];
		}
		inf.x++;
		i++;
	}
	if (line[i] != '"')
	{
		ft_printf("Lexical error[TOKEN][%i:%i]. %s should ends with \"\n", inf.y, inf.x + 1, define + 1);
		exit(1);
	}
	line += i + 1;
	inf.x++;
	line = ft_go_space(line, &(inf.x));
	if (*(line) != '\0')
	{
		ft_printf("Lexical error[TOKEN][%i:%i]. Excess information after %s\n", inf.y, inf.x + 1, define + 1);
		exit(1);
	}
}

void	ft_name_comment(t_my inf, char *define, char **buf)
{
	/// CHECK Define
	char 	*line;

	inf.x = 0;
	if (!inf.head || !inf.head->next)
	{
		ft_printf("Lexical error[TOKEN][%i:%i]. Too small file. Not enough information\n", inf.y,0);
		exit(1);
	}
	line = ft_go_space(inf.head->line, &(inf.x));
	if (!(line == ft_strstr(line, define)))
	{
		ft_printf("Lexical error[TOKEN][%i:%i]. Command line should starts with \"%s\"\n", inf.y, inf.x, define);
		exit(1);
	}
	line += ft_strlen(define);
	inf.x += ft_strlen(define);
	line = ft_go_space(line, &(inf.x));
	if (*(line) != '"')
	{
		ft_printf("Lexical error[TOKEN][%i:%i]. %s should starts with \"\n", inf.y, inf.x, define + 1);
		exit(1);
	}
	line++;
	inf.x++;
	/// WRITE Define
	ft_write_name_comment(buf, line, define, inf);
}

void		ft_throu_empt_lines(t_my *inf)
{
	char 	*l;

	while(inf->head && inf->head->line)
	{
		l = ft_go_space(inf->head->line, &(inf->x));
		if (*l == '\0')
		{
			inf->head = inf->head->next;
			inf->y++;
		}
		else
			break ;
	}
}

void		ft_read_head(t_my *inf, char *name)
{
	char	*name2;
	char	*comment;
	int		magic_num;


	if ((g_fd = open(name, O_WRONLY | O_CREAT | O_TRUNC,
					 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		ft_printf("error: open\n");
		exit(1);
	}
	name2 = ft_memalloc(PROG_NAME_LENGTH + 4);
	comment = ft_memalloc(COMMENT_LENGTH + 4);

	/// MAGIC NUMBER
	magic_num = convert_end(COREWAR_EXEC_MAGIC);
	write(g_fd, &magic_num, sizeof(magic_num));

	///NAME
	ft_throu_empt_lines(inf);
	ft_name_comment(*inf, NAME_CMD_STRING, &name2);
	write(g_fd, &name2,sizeof(name2));

	/// BOTSIZE
	char *botsize = "a"; // botsize nujno budet naiti!!!!!!!!!!!!!!!!!!!!!!!!!!!
	write(g_fd, &(botsize), 2); // botsize nujno budet naiti!!!!!!!!!!!!!!!!!!!!!!!!!!!

	///COMMENT
	if (inf->head->next)
	{
		inf->head = inf->head->next;
		inf->y++;
	}
	ft_throu_empt_lines(inf);
	ft_name_comment(*inf, COMMENT_CMD_STRING, &comment);
	write(g_fd, &comment,sizeof(comment));
	if (inf->head->next)
	{
		inf->head = inf->head->next;
		inf->y++;
	}
}

void		ft_read_body(t_my inf, char *name)
{

}

void	ft_obnul(t_my	*inf, char *name)
{
	inf->fd = open(name, O_RDONLY);
	inf->head = (t_text*)malloc(sizeof(t_text));
	inf->head->line = NULL;
	inf->head->next = NULL;
	inf->x = 1;
	inf->y = 1;

}

void    ft_push_back(t_my *my, t_text *new, int i)
{
	t_text  *p_t;

	p_t = my->head;
	new->i = i;
	while (p_t->next)
	{
		p_t = p_t->next;
	}
	if (p_t->line)
		p_t->next = new;
	else
		my->head = new;
}

void    ft_print_txt(t_text *t)
{
	t_text      *p_t;

	p_t = t;
	while (p_t->next)
	{
		ft_printf("%s\t\n", p_t->line);
		p_t = p_t->next;
	}
	if(p_t)
		ft_printf("%s\t\n", p_t->line);
}

int		main(int ac, char **av)
{
	char *name;
	t_my inf;
	t_text *new_t;
	int i;

	i = 1;
	if (ac < 2 || ac > 3)
		return (ft_printf("Invalid number of arguements")); // inform invalid number of arguement
	if (!ft_check_format(av[1]))
		return (ft_printf("Can'head read source file\n"));
	else
		name = ft_get_name(av[1]);


	//reading
	ft_obnul(&inf, av[1]);
	new_t = (t_text *) malloc(sizeof(t_text));
	new_t->next = NULL;
	while (get_next_line(inf.fd, &(new_t->line)) > 0)
	{
		ft_push_back(&inf, new_t, i++);
		new_t = (t_text *) malloc(sizeof(t_text));
		new_t->next = NULL;
	}
	free(new_t);
	ft_print_txt(inf.head);


	ft_read_head(&inf, name);
	ft_throu_empt_lines(&inf);
	ft_read_body(inf, name);
	ft_printf("Writing output program to %s", name);
	free(name);
	return (0);

}
