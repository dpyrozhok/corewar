/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 17:44:03 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/23 15:34:43 by popanase         ###   ########.fr       */
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
void			ft_check_args(int ac, char **av, t_core *core, int args);
void			ft_check_file(char *str, int *bots, t_check *file);
void			ft_store_dump(int ac, char **av, int i, t_core *core);
void			ft_check_num(int ac, char **av, int i);
int				ft_err(int ret, char *str, char *orig);
int				ft_is_num(char *str);
int				ft_check_dir(char *str);

#endif
