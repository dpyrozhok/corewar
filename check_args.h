/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 17:44:03 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/19 13:36:26 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_CHECK_ARGS_H
# define COREWAR_CHECK_ARGS_H

# include "corewar.h"
# include "t_op.h"
# include "ncurs.h"

typedef struct	s_check
{
	char			buf[4];
	char			name[PROG_NAME_LENGTH];
	unsigned char	comment[COMMENT_LENGTH];
	unsigned int	size;
	unsigned char	*code;
	ssize_t			ret;
}				t_check;

void			ft_check_args(int ac, char **av, t_core *core, int args);

#endif
