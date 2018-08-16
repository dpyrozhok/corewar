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

typedef struct s_my
{
    t_text *head;
    int fd;
	int x;
	int y;
}               t_my;

#endif