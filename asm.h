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
	struct s_label  *next;
}                   t_label;

typedef struct     		s_use_label
{
	char 				*label;
	struct s_use_label  *next;
}                  		t_use_label;

typedef struct      s_comm
{
	char            *name;
    char			comm_id;
	char 			arg_id[3]; //1-T_REG 2-T_DIR 3-T_IND 0 - Net arg
	char 			*arg[3];
	char 			codage;
	int             size;
	int 			t_dir_size;
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
	int				x;
	int				y;
	int 			magic_num;
    int            	botsize;
	char 			*name2;
	char 			*comment;
	char 			*file_name;

}					t_my;

#endif