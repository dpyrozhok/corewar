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

int	is_little(void)
{
	return(1);
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

int		convert_end_two_bytes(int new)
{
	if (is_little() == 1)
			return (new << 8) | ((new >> 8) & 0xFF);
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

void		ft_read_head(t_my *inf)
{
	inf->name2 = ft_memalloc(PROG_NAME_LENGTH); // 128
	inf->comment = ft_memalloc(COMMENT_LENGTH); // 2048

	/// MAGIC NUMBER
	inf->magic_num = convert_end(COREWAR_EXEC_MAGIC);

	///NAME
	ft_throu_empt_lines(inf);
	ft_name_comment(*inf, NAME_CMD_STRING, &inf->name2);

	///COMMENT
	if (inf->head->next)
	{
		inf->head = inf->head->next;
		inf->y++;
	}
	ft_throu_empt_lines(inf);
	ft_name_comment(*inf, COMMENT_CMD_STRING, &inf->comment);
	if (inf->head->next)
	{
		inf->head = inf->head->next;
		inf->y++;
	}
}

void	ft_push_u_front(t_use_label **begin_list, t_use_label *elem)
{
	if (!*begin_list)
		elem->next = NULL;
	else
		elem->next = *begin_list;
	*begin_list = elem;
}


int 	ft_lable(t_my *inf, int arg_i)
{
	int 	start;
	int 	end;
	t_use_label	*new;

	new = (t_use_label*)malloc(sizeof(t_use_label));
	start = inf->x;
	while (inf->head->line[inf->x] != '\0' && inf->head->line[inf->x] != ',' &&
			inf->head->line[inf->x] != ' ' && inf->head->line[inf->x] != '\t')
	{
		inf->x++;
	}
	end = inf->x;
	inf->command_e->arg[arg_i] = ft_strsub(inf->head->line, start + 1, end - start - 1);
	new->label = ft_strsub(inf->head->line, start + 2, end - start - 1);
	new->next = NULL;
	ft_push_u_front(&(inf->use_label), new);
	inf->x++;
	return (1);
}

int     ft_num(t_my *inf, int arg_i, int m, int is_end)
{
    int     n_start;
    int     n_end;
    char    *line;

    line = inf->head->line;
    n_start = m;
    if (line[m] == '-')
        m++;
    while(line[m] >= '0' && line[m] <= '9')
        m++;
    n_end = m;
    ft_go_space(line, &(m));
    if (is_end == 0 && line[m] != '\0')
        return (0);
    if (is_end != 0 && line[m] != ',')
        return (0);
    inf->x = m + 1;
    inf->command_e->arg[arg_i] = ft_strsub(line, n_start, n_end - n_start);
    return (1);
}

int		ft_dir(const char *line, t_my *inf, int is_end)
{
	int 	m;
    int     arg_i;

	if (line[inf->x] != '%')
		return (0);
	m = inf->x;
	m++;
    arg_i = 0;

    while (inf->command_e->arg[arg_i] != NULL)
        arg_i++;
	inf->command_e->arg_id[arg_i] = 2;
	inf->command_e->size += inf->command_e->t_dir_size;
	if (line[m] == ':')
		return (ft_lable(inf, arg_i));
	else
        return (ft_num(inf, arg_i, m, is_end));

}

int 	ft_ind(const char *line, t_my *inf, int is_end)
{
    int 	m;
    int     arg_i;

    m = inf->x;
    arg_i = 0;
    while (inf->command_e->arg[arg_i] != NULL)
        arg_i++;
	inf->command_e->arg_id[arg_i] = 3;
	inf->command_e->size += 2;
    if (line[m] == ':')
        return (ft_lable(inf, arg_i));
    else
        return (ft_num(inf, arg_i, m, is_end));
}

int     ft_reg(const char *line, t_my *inf, int is_end)
{
    int 	m;
    int		z;
	int 	arg_i;

	arg_i = 0;
    if (line[inf->x] == 'r')
    {
		while (inf->command_e->arg[arg_i] != NULL)
			arg_i++;
		inf->command_e->arg_id[arg_i] = 1;
		inf->command_e->size += 1;
        m = inf->x;
        m++;
        if (line[m] >= '0' && line[m] <= '9' && ((z = ft_atoi(line + inf->x + 1)) < 100) && z >= 0)
			return (ft_num(inf, arg_i, m, is_end));
		else
			return (0);
    }
    else
        return (0);
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
	while (name[i] && name[i] != LABEL_CHAR && (ft_isdigit(name[i]) || ft_isalpha(name[i]) || name[i] == '_'))
		i++;
	return ((name[i] == LABEL_CHAR) ? 1 : 0);
}

void    ft_push_l_back(t_my *my, t_label *new)
{
	t_label  *p_l;

	p_l = my->label_s;
    if (my->label_e)
        my->label_e->next = new;
    else
    {
        while (p_l && p_l->next)
        {
            p_l = p_l->next;
        }
        if (p_l)
            p_l->next = new;
        else
            my->label_s = new;
    }
    my->label_e = new;
}

void	ft_label(char *name, t_my *inf)
{
	t_label	*new;
	int 	i;

	ft_go_space(inf->head->line, &inf->x);
	i = inf->x;
	new = (t_label*)malloc(sizeof(t_label));
	new->next = NULL;
	new->size = -1;
	while (name[i++] && name[i] != LABEL_CHAR);
	new->name = (char*)malloc(sizeof(char) * (i - inf->x + 1));
	i = 0;
	while (name[inf->x] && name[inf->x] != LABEL_CHAR)
		new->name[i++] = name[inf->x++];
	inf->x++;
	new->name[i] = '\0';
	ft_push_l_back(inf, new);
}

void    ft_push_c_back(t_my *my, t_comm *new)
{
    t_comm  *p_c;

    p_c = my->command_s;
    if (my->command_e)
        my->command_e->next = new;
    else
    {
        while (p_c && p_c->next)
        {
            p_c = p_c->next;
        }
        if (p_c)
            p_c->next = new;
        else
            my->command_s = new;
    }
    my->command_e = new;
}

void	ft_command(int j, t_my *inf)
{
	t_comm	*new;

	new = (t_comm*)malloc(sizeof(t_comm));
	new->name = ft_strdup(OP(j).name);
    new->next = NULL;
    new->label = inf->label_e;
    new->arg[0] = NULL;
    new->arg[1] = NULL;
    new->arg[2] = NULL;
	new->arg_id[0] = 0;
	new->arg_id[1] = 0;
	new->arg_id[2] = 0;
	new->size = 1;
	new->t_dir_size = 0;
	new->codage = 0;
    ft_push_c_back(inf, new);
}

int 		size_dira(int j)
{
	if ((j >= 0 && j <= 7) || j == 12 || j == 15)
		return (4);
	else
		return (2);
}

int 	codage(int j)
{
	return ((j == 0 || j == 8 || j == 12 || j == 14)  ? 0 : 1);
}

void		ft_read_body(t_my *inf)
{
    int j;
	t_text	*p_t;
	char *line;

    char command_name[6];
	while (inf->head)
	{
		ft_throu_empt_lines(inf);
		if (!inf->head)
			return ;
		ft_bzero(command_name, 6);
		inf->x = 0;
		j = 0;
		line = inf->head->line;
		if (ft_is_label_name(line))
		{
			ft_label(line, inf);
			ft_go_space(line, &(inf->x));
			if(line[inf->x] == '\0')
			{
				p_t = inf->head;
				if (inf->head->next)
					inf->head = inf->head->next;
				else
				{
					ft_printf("Syntax error at token [%i:%i]. END (null)\n", inf->y, inf->x + 1);
					exit(1);
				}
				free(p_t);
				inf->y++;
				ft_throu_empt_lines(inf);
				if (inf->head == NULL)
					return ; //vyhod dlya pustogo lebla
                line = inf->head->line;
			}
			if (ft_is_label_name(line + inf->x))
				continue ;
		}
		ft_go_space(line, (&inf->x));
		while (ft_isalpha(line[inf->x]) && j < 5){
			command_name[j] = line[inf->x];
			j++;
			inf->x++;
		}
		j = 0;
		while (j < 16)
		{
			if (ft_strcmp(command_name, OP(j).name) == 0)
			{
				ft_command(j, inf);
				break;
			}
			j++;
		}
		if (j >= 16)
		{
			ft_printf("Lexical error[TOKEN][%i:%i]. Not a command %s\n", inf->y, inf->x + 1, command_name);
		}
		inf->command_e->comm_id = (char)j;
		inf->command_e->t_dir_size = size_dira(j);
		inf->command_e->codage = (char)codage(j);
		inf->command_e->size += (int)inf->command_e->codage;
		if (ft_check_args(inf, line, j) == 0)
		{
			ft_printf("Lexical error[TOKEN][%i:%i]. Wrong argument\n", inf->y, inf->x + 1);
			exit(1);
		}
		free(line);
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
    inf->label_s = NULL;
	inf->label_e = NULL;
	inf->command_s = NULL;
    inf->command_e = NULL;
	inf->head->line = NULL;
	inf->head->next = NULL;
	inf->use_label = NULL;
	inf->x = 1;
	inf->y = 1;
    inf->botsiz = "0";

}

void    ft_push_t_back(t_my *my, t_text *new, int i)
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
	if (ft_strchr(*line, '#') || ft_strchr(*line, ';'))
	{
		i = 0;
		while ((*line)[i] != '#' && (*line)[i] != ';')
			i++;
		new = (char*)malloc(sizeof(char) * (i + 2));
		ft_strncpy(new, *line, i);
		new[i] = '\0';
		ft_memdel(line);
		*line = new;
	}
	return (r);
}

void	ft_check_end( t_my *inf)
{
	char 	c;

	lseek(inf->fd,-1,SEEK_END);
	read(inf->fd, &c, 1);
	if (c != '\n')
	{
		ft_printf("Syntax error[TOKEN][%i:0]. Unexpected end of input \n", inf->y);
		exit(1);
	}
}

int	ft_pliz_write_to_file(t_my *inf)
{
	char	*botsize;
	int 	i_bot_size;

	if ((g_fd = open(inf->file_name, O_WRONLY | O_CREAT | O_TRUNC,
					 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		ft_printf("error: open\n");
		exit(1);
	}
	char *nulek = {0};
	write(g_fd, &inf->magic_num, sizeof(inf->magic_num));
	write(g_fd, inf->name2, 128);
	write(g_fd, &nulek, 4);
	write(g_fd, &(nulek), 4); // botsize nujno budet naiti!!!!!!!!!!!!!!!!!!!!!!!!!!!
	write(g_fd, inf->comment, 2048);
	write(g_fd, &nulek, 4);

	return (0);
}

int 	ft_write_label(char *arg, t_comm *start, int size)
{

}

int 	ft_write_num(char *arg, t_comm *start, int size)
{
	int 	ch;

	ch = ft_atoi(arg);
	if (size == 2)
	{
		ch = convert_end_two_bytes(ch);
		write(g_fd, &ch, (size_t)size);
		return (0);
	}
	ch = convert_end(ch);
	write(g_fd, &ch, (size_t)size);
	return (0);
}

int 		ft_write_reg(char *arg, t_comm *start)
{
	int 	ch;

	ch = ft_atoi(arg);
	write(g_fd, &ch, 1);
}

int 	arguements_to_file(t_comm *start)
{
	int 	i;

	i = 0;
	while(start->arg[i])
	{
		if (start->arg_id[i] == 1)
			ft_write_reg(start->arg[i], start);
		if (start->arg_id[i] == 2 && start->arg[i][0] == ':')
			ft_write_label(start->arg[i], start, start->t_dir_size);
		if (start->arg_id[i] == 3 && start->arg[i][0] == ':')
			ft_write_label(start->arg[i], start, 2);
		if (start->arg_id[i] == 2 && start->arg[i][0] != ':')
			ft_write_num(start->arg[i], start, start->t_dir_size);
		if (start->arg_id[i] == 3 && start->arg[i][0] != ':')
			ft_write_num(start->arg[i], start, 2);
		i++;
	}
}

int 	ft_write_commands(t_my *inf)
{
	t_comm *start;
	int change_comm_id;
	int codage;
	int i;

	i = 0;
	codage = 0;
	start = inf->command_s;
	while(start != NULL)
	{
		change_comm_id = start->comm_id + 1;
		write(g_fd, &change_comm_id, 1);
		if (start->codage)
		{
			while (i < 3)
			{
				codage = codage | start->arg_id[i];
				codage = codage<<2;
				i++;
			}
			write(g_fd, &codage, 1);
			//ZAPIS CODAGE I ARGUMENTOV// LABLOV PO ETIM ARGUMENTAM // I BOT_SIZE//
		}
		arguements_to_file(start);
		start = start->next;
	}
}

int 			ft_check_correct_labels(t_my *inf)
{
	t_label *all;
	t_use_label *to_check;

	all = inf->label_s;
	to_check = inf->use_label;
	while (to_check != NULL)
	{
		while (all != NULL)
			{
			if (ft_strcmp(all->name, to_check->label) == 0)
				break;
			else
				all = all->next;
		}
		if (all == NULL)
			return (0);
		else
			to_check = to_check->next;
		all = inf->label_s;
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_my inf;
	t_text *new_t;
	int i;

	i = 1;
	if (ac < 2 || ac > 3)
		return (ft_printf("Invalid number of arguements")); // inform invalid number of arguement
	if (!ft_check_format(av[1]))
		return (ft_printf("Not valid file\n"));
	else
		inf.file_name = ft_get_name(av[1]);


	//reading
	ft_obnul(&inf, av[1]);
	new_t = (t_text *) malloc(sizeof(t_text));
	new_t->next = NULL;
	while (ft_gnl_without_com(inf.fd, &(new_t->line)) > 0)
	{
		ft_push_t_back(&inf, new_t, i++);
		new_t = (t_text *) malloc(sizeof(t_text));
		new_t->next = NULL;
	}
	free(new_t);
	ft_print_txt(inf.head);


	ft_read_head(&inf);
//	ft_throu_empt_lines(&inf);

	ft_read_body(&inf);
	ft_check_end(&inf);
	if (ft_check_correct_labels(&inf) == 0)
	{
		ft_printf("Wrong ssilka to label\n");
		exit(1);
	}
	ft_pliz_write_to_file(&inf);
	ft_write_commands(&inf);
	ft_printf("Writing output program to %s", inf.file_name);
	free(inf.file_name);
	return (0);

}