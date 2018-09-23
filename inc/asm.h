/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpyrozho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 14:49:21 by dpyrozho          #+#    #+#             */
/*   Updated: 2018/08/09 14:49:23 by dpyrozho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# define OP(index)	g_op_tab[index]
# define LE0 "Lexical error[TOKEN][%i:%i]. "
# define S0 "Syntax error[TOKEN][%i:%i]."
# define S1 "Syntax error[TOKEN][%i:0]."
# define HZ1 p_use_l->y, p_use_l->x, p_use_l->label
# define HZ2 inf, this_command->arg[i], this_command, this_command->t_dir_size
# define HZ3 (ft_go_space(line, &(inf->x))) && line[inf->x] == '\0'
# define HZ4 ft_throu_empt_lines(inf) && inf->head == NULL
# define HZ5 inf->y, inf->x + 1, command_name
# define LE1 LE0"Too big %s\n"
# define LE2 LE0"%s should ends with \"\n"
# define LE3 LE0"Excess information after %s\n"
# define LE4 LE0"Too small file. Not enough information\n"
# define LE5 LE0"Command line should starts with \"%s\"\n"
# define LE6 LE0" %s should starts with \"\n"
# define LE7 ft_printf(LE0"Not a command %s\n", HZ5)
# define LE8 ft_printf(LE0"Wrong argument\n", inf->y, inf->x + 1)
# define LE9 ft_printf(S1"Unexpected end of input \n", inf->y)
# define SE1 ft_printf(S0"Wrong ssilka to label (%s)\n", HZ1)
# define AG1 ft_write_label(HZ2)
# define HUYAIN (ft_label(line, inf)) && HZ3
# define HUYAIN2 ft_gogogogo(inf, &p_t) && HZ4
# include "libft/libft.h"
# include "op.h"
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct				s_text
{
	char					*line;
	int						i;
	struct s_text			*next;
}							t_text;

typedef struct				s_label
{
	char					*name;
	int						size;
	int						cidr;
	struct s_label			*next;
}							t_label;

typedef struct				s_use_label
{
	char					*label;
	struct s_use_label		*next;
	unsigned int			x;
	unsigned int			y;
}							t_use_label;

typedef struct				s_comm
{
	char					*name;
	char					comm_id;
	char					arg_id[3];
	char					*arg[3];
	char					codage;
	int						size;
	unsigned int			t_dir_size;
	int						cidr;
	t_label					*label;
	struct s_comm			*next;
}							t_comm;

typedef struct				s_my
{
	t_text					*head;
	t_label					*label_s;
	t_label					*label_e;
	t_use_label				*use_label;
	t_comm					*command_s;
	t_comm					*command_e;
	int						fd;
	unsigned int			x;
	unsigned int			y;
	int						magic_num;
	unsigned int			botsize;
	char					*name2;
	char					*comment;
	char					*file_name;

}							t_my;

int							g_fd;
void						ft_read_head(t_my *inf);
void						ft_free_command(t_my *inf);
void						ft_free_label(t_my *inf);
void						ft_free(t_my *inf);
int							ft_check_format(char *name);
char						*ft_get_name(char *name);
unsigned int				convert_end(unsigned int ch, char bytes);
int							ft_go_space(char *line, unsigned int *x);
void						ft_error_code(char *le, t_my *inf, char *define);
void						ft_write_name_comment(char **buf, char *line,
							char *define, t_my inf);
void						ft_name_comment(t_my inf, char *define, char **buf);
int							ft_throu_empt_lines(t_my *inf);
void						ft_read_head(t_my *inf);
void						ft_push_u_front(t_use_label **begin_list,
							t_use_label *elem);
int							ft_lable(t_my *inf, int arg_i);
int							ft_num(t_my *inf, int arg_i,
							unsigned int m, int is_end);
int							ft_dir(const char *line,
							t_my *inf, int is_end);
int							ft_ind(const char *line, t_my *inf, int is_end);
int							ft_reg(const char *line, t_my *inf, int is_end);
int							ft_check_args(t_my *inf, char *line,
							int num_command);
int							ft_is_label_name(char *name);
void						ft_push_l_back(t_my *my, t_label *new);
int							ft_label(char *name, t_my *inf);
void						ft_push_c_back(t_my *my, t_comm *new);
void						ft_command(int j, t_my *inf);
unsigned int				size_dira(int j);
int							codage(int j);
void						ft_eror_code_n2(void *le, t_my *inf);
int							ft_gogogogo(t_my *inf, t_text **p_t);
void						ft_help_read_body1(t_my *inf, int j);
int							ft_find_command(t_my *inf, char *command_name);
char						*ft_nastenka(char command_name[6],
							t_my *inf, int *j);
void						ft_function(t_my *inf, int j,
							char *line, t_text **p_t);
void						ft_read_body(t_my *inf,
							char command_name[6], char *line);
void						ft_obnul(t_my *inf, char *name);
void						ft_push_t_back(t_my *my, t_text *new, int i);
void						ft_print_txt(t_text *t);
int							ft_gnl_without_com(int fd, char **line);
void						ft_check_end(t_my *inf);
int							ft_pliz_write_to_file(t_my *inf);
int							ft_empty_label(t_my *inf, char *ssilka);
int							ft_find_label(t_comm *all, char *ssilka, t_my *inf);
int							from_ssylk_to_command(int do_ssylk,
							int do_comm, t_comm *all);
int							ft_write_label(t_my *inf, char *ssilka,
							t_comm *this_command, int size_byte);
int							ft_write_num(char *arg, unsigned int size);
void						ft_write_reg(char *arg);
void						arguements_to_file(t_my *inf, t_comm *this_command);
void						ft_write_commands(t_my *inf, int i, int codage);
t_use_label					*ft_check_correct_labels(t_my *inf);
void						ft_write_botsize(t_my *inf);
void						ft_read_all(t_my *inf);

#endif
