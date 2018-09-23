/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_op.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 15:35:04 by popanase          #+#    #+#             */
/*   Updated: 2018/09/23 15:36:48 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_T_OP_H
# define COREWAR_T_OP_H
# include "op.h"

typedef struct	s_op
{
	char			*op;
	short			qt_arg;
	unsigned char	arg[3];
	short			code;
	short			cycle;
	char			*exp;
	short			codage;
	char			lable;
}				t_op;

extern			t_op g_op_tab[17];
#endif
