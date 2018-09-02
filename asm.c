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
	if (format && ft_strcmp(format, ".s") == 0)
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
	get = malloc(sizeof(char) * (i + 1));
	ft_strncpy(get, name, i);
	get[i] = '\0';
	tmp = get;
	get = ft_strjoin(get, ".cor");
	get[i + 4] = '\0';
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

void		ft_go_space(char *line, int *x)
{
    while (line[*x] && (line[*x] == ' ' || line[*x] == '\t'))
    {
        (*x)++;
    }
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
	inf.x++;
    ft_go_space(inf.head->line, &(inf.x));
	if (inf.head->line[inf.x] != '\0')
	{
		ft_printf("Lexical error[TOKEN][%i:%i]. Excess information after %s\n", inf.y, inf.x + 1, define + 1);
		exit(1);
	}
}

void	ft_name_comment(t_my inf, char *define, char **buf)
{
    /// CHECK Define
//	char 	*line;

    inf.x = 0;
    if (!inf.head || !inf.head->next)
    {
        ft_printf("Lexical error[TOKEN][%i:%i]. Too small file. Not enough information\n", inf.y,0);
        exit(1);
    }
    ft_go_space(inf.head->line, &(inf.x));
    if (inf.head->line + inf.x != ft_strstr(inf.head->line + inf.x, define))
    {
        ft_printf("Lexical error[TOKEN][%i:%i]. Command line should starts with \"%s\"\n", inf.y, inf.x, define);
        exit(1);
    }
    inf.x += ft_strlen(define);
    ft_go_space(inf.head->line, &(inf.x));
    if (inf.head->line[inf.x] != '"')
    {
        ft_printf("Lexical error[TOKEN][%i:%i]. %s should starts with \"\n", inf.y, inf.x, define + 1);
        exit(1);
    }
    inf.x++;
    /// WRITE Define
	ft_write_name_comment(buf, inf.head->line + inf.x, define, inf);
}

void		ft_throu_empt_lines(t_my *inf)
{
    t_text	*p_t;

    inf->x = 0;
    while(inf->head && inf->head->line)
    {
        ft_go_space(inf->head->line, &(inf->x));
        if (inf->head->line[inf->x] == '\0')
        {
            free(inf->head->line);
            p_t = inf->head;
            inf->head = inf->head->next;
            free(p_t);
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
	name2 = ft_memalloc(PROG_NAME_LENGTH + 4); // 132
	comment = ft_memalloc(COMMENT_LENGTH + 4); // 2052

	/// MAGIC NUMBER
	magic_num = convert_end(COREWAR_EXEC_MAGIC);
	write(g_fd, &magic_num, sizeof(magic_num));

	///NAME
	ft_throu_empt_lines(inf);
	ft_name_comment(*inf, NAME_CMD_STRING, &name2);
	write(g_fd, name2, 132);

	/// BOTSIZE
	char *botsize = "a"; // botsize nujno budet naiti!!!!!!!!!!!!!!!!!!!!!!!!!!!
	write(g_fd, &(botsize), 4); // botsize nujno budet naiti!!!!!!!!!!!!!!!!!!!!!!!!!!!

	///COMMENT
	if (inf->head->next)
	{
		inf->head = inf->head->next;
		inf->y++;
	}
	ft_throu_empt_lines(inf);
	ft_name_comment(*inf, COMMENT_CMD_STRING, &comment);
	write(g_fd, comment, 2052);
	if (inf->head->next)
	{
		inf->head = inf->head->next;
		inf->y++;
	}
}

int     ft_reg(const char *line, t_my *inf, int end)
{
    int m;
	int z;

    if (line[inf->x] == 'r')
    {
        m = inf->x;
        m++;
        while (line[m] >= '0' && line[m] <= '9')
            m++;
        ft_go_space(line, &(m));
		if (end == 0 && line[m] != '\0')
			return (0);
       if (end != 0 && line[m] != ',')
            return (0);
        if (((z = ft_atoi(line + inf->x + 1)) < 100) && z > 0)
        {
            inf->x = m + 1; // +1 propusk zapyatoi
            return (1);
        }
        else
            return (0);
    }
    else
        return (0);
}

int 	ft_lable(t_my *inf)
{
	while (inf->head->line[inf->x] != '\0' && inf->head->line[inf->x] != ',')
		inf->x++;
	inf->x++;
	return (1);
}

int		ft_dir(const char *line, t_my *inf, int end)
{
	int 	m;

	if (line[inf->x] != '%')
		return (0);
	m = inf->x;
	m++;
	if (line[m] == ':')
		return (ft_lable(inf));
	else
	{
		if (line[m] == '-')
			m++;
		while(line[m] >= '0' && line[m] <= '9')
			m++;
		ft_go_space(line, &(m));
		if (end == 0 && line[m] != '\0')
			return (0);
		if (end != 0 && line[m] != ',')
			return (0);
		inf->x = m + 1;
		return (1);
	}

}

int 	ft_ind(const char *line, t_my *inf, int end)
{
	int 	m;

	m = inf->x;
	while(line[m] >= '0' && line[m] <= '9')
		m++;
	ft_go_space(line, &(m));
	if (end == 0 && line[m] != '\0')
		return (0);
	if (end != 0 && line[m] != ',')
		return (0);
	inf->x = m + 1;
	return (1);
}

int     ft_check_args(t_my *inf, char *line, int num_command)
{
    int z;
    int i;

    i = 0;
	ft_go_space(inf->head->line, &(inf->x));
    while (i < 3 && (z = OP(num_command).args[i]) != 0)
	{
		i++;
		ft_go_space(line, &(inf->x));
        if ((z == 1 || z == 3 || z == 5 || z == 7) && (ft_reg(line, inf, (i == 3) ? 0 : OP(num_command).args[i])))
            continue;
        if ((z == 2 || z == 3 || z == 6 || z == 7) && (ft_dir(line, inf, (i == 3) ? 0 :  OP(num_command).args[i])))
			continue;
   		if ((z == 4 || z == 5 || z == 6 || z == 7) && (ft_ind(line, inf, (i == 3) ? 0 : OP(num_command).args[i])))
			continue;
		else
			return (0);
    }
	return (1);
}

int 	ft_is_label_name(char *name)
{
	int 	i;

	i = 0;
	ft_go_space(name, &i);
	while (name[i] && name[i] != LABEL_CHAR && (ft_isdigit(name[i]) || ft_isalpha(name[i])))
		i++;
	return ((name[i] == LABEL_CHAR) ? 1 : 0);
}

void		ft_read_body(t_my *inf, char *name)
{
    int j;
	t_text	*p_t;

    char command_name[6];
	while (inf->head)
	{
		ft_throu_empt_lines(inf);
		ft_bzero(command_name, 6);
		inf->x = 0;
		j = 0;
		name = inf->head->line;
		if (ft_is_label_name(name))
			while (name[inf->x++] != LABEL_CHAR);
		while (name[inf->x] == ' ' || name[inf->x] == '\t')
			inf->x++;
		while (name[inf->x] >= 97 && name[inf->x] <= 122) {
			command_name[j] = name[inf->x];
			j++;
			inf->x++;
		}
		j = 0;
		while (j < 16) {
			if (ft_strcmp(command_name, OP(j).name) == 0) {
				j = j + 1;
				write(g_fd, &j, 1);
				break;
			}
			j++;
		} // zapisali imya komandi v fail
		if (ft_check_args(inf, name, j - 1) == 0)
		{
			ft_printf("Lexical error[TOKEN][%i:%i]. Wrong argument\n", inf->y, inf->x + 1);
			exit(1);
		}
		free(name);
		p_t = inf->head;
		inf->head = inf->head->next;
		inf->y++;
		free(p_t);
	}
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


int 	ft_gnl_without_com(int fd, char **line)
{
	char 	*new;
	int 	i;
	int 	r;

	r = get_next_line(fd, line);
	if (ft_strchr(*line, '#'))
	{
		i = 0;
		while ((*line)[i] != '#')
			i++;
		new = (char*)malloc(sizeof(char) * (i + 2));
		ft_strncpy(new, *line, i);
		new[i] = '\0';
		ft_memdel(line);
		*line = new;
	}
	return (r);
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
		return (ft_printf("Not valid file\n"));
	else
		name = ft_get_name(av[1]);


	//reading
	ft_obnul(&inf, av[1]);
	new_t = (t_text *) malloc(sizeof(t_text));
	new_t->next = NULL;
	while (ft_gnl_without_com(inf.fd, &(new_t->line)) > 0)
	{
		ft_push_back(&inf, new_t, i++);
		new_t = (t_text *) malloc(sizeof(t_text));
		new_t->next = NULL;
	}
	free(new_t);
	ft_print_txt(inf.head);


	ft_read_head(&inf, name);
//	ft_throu_empt_lines(&inf);

	ft_read_body(&inf, name);

	ft_printf("Writing output program to %s", name);
	free(name);
//	int fd = open(av[1], O_RDONLY);
//	char *line;
//	ft_gnl_without_com(fd, &line);
//	ft_printf("%s\n", line);
	return (0);

}