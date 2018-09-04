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
    struct s_text   *next;
    int             i;
}                   t_text;

typedef struct      s_label
{
	char            *name;
	struct s_label  *next;
	int             size;
}                   t_label;

typedef struct      s_comm
{
	char            *name;
	char 			*label;


	char 			*arg[3];
	int             size;
	struct s_com  	*next;
}                   t_comm;


typedef struct		s_my
{
    t_text			*head;
	t_label			*label_s;
	t_label			*label_e;
	t_comm			*command;
    int				fd;
	int				x;
	int				y;
	int 			magic_num;
	char 			*name2;
	char 			*comment;
	char 			*file_name;

}					t_my;

#endif