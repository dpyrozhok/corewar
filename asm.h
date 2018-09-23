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
# define LE1 "Lexical error[TOKEN][%i:%i]. Too big %s\n"
# define LE2 "Lexical error[TOKEN][%i:%i]. %s should ends with \"\n"
# define LE3 "Lexical error[TOKEN][%i:%i]. Excess information after %s\n"
# define LE4 "Lexical error[TOKEN][%i:%i]. Too small file. Not enough information\n"
# define LE5 "Lexical error[TOKEN][%i:%i]. Command line should starts with \"%s\"\n"
# define LE6 "Lexical error[TOKEN][%i:%i]. %s should starts with \"\n"
# define LE7 ft_printf("Lexical error[TOKEN][%i:%i]. Not a command %s\n", inf->y, inf->x + 1, command_name)
# define LE8 ft_printf("Lexical error[TOKEN][%i:%i]. Wrong argument\n", inf->y, inf->x + 1)
# define LE9 ft_printf("Syntax error[TOKEN][%i:0]. Unexpected end of input \n", inf->y)
# define SE1 ft_printf("Syntax error[TOKEN][%i:%i].Wrong ssilka to label (%s)\n", p_use_l->y, p_use_l->x, p_use_l->label)
# define AG1 ft_write_label(inf, this_command->arg[i], this_command, this_command->t_dir_size)
# include "libft/libft.h"
# include "op.h"
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>


typedef struct      s_text
{
    char            *line;
	int             i;
    struct s_text   *next;
}                   t_text;

typedef struct      s_label
{
	char            *name;
	int             size;
	int 			cidr;
	struct s_label  *next;
}                   t_label;

typedef struct     		s_use_label
{
	char 				*label;
	struct s_use_label  *next;
	unsigned int		x;
	unsigned int		y;
}                  		t_use_label;

typedef struct      s_comm
{
	char            *name;
    char			comm_id;
	char 			arg_id[3]; //1-T_REG 2-T_DIR 3-T_IND 0 - Net arg
	char 			*arg[3];
	char 			codage;
	int             size;
	unsigned int 	t_dir_size;
	int 			cidr;
	t_label 		*label;
	struct s_comm  	*next;
}                   t_comm;


typedef struct		s_my
{
    t_text			*head;
	t_label			*label_s;
	t_label			*label_e;
	t_use_label		*use_label;
	t_comm			*command_s;
    t_comm			*command_e;
    int				fd;
	unsigned int	x;
	unsigned int	y;
	int 			magic_num;
    unsigned int	botsize;
	char 			*name2;
	char 			*comment;
	char 			*file_name;

}					t_my;

#endif