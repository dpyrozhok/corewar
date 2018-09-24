/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 15:17:11 by popanase          #+#    #+#             */
/*   Updated: 2018/09/24 10:19:44 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <sys/types.h>
# include <stdio.h>
# include <fcntl.h>
# include "../../libft/includes/libft.h"
# include "../../op.h"

typedef struct s_champ	t_champ;
typedef struct s_car	t_car;
typedef struct s_core	t_core;

struct		s_core
{
	unsigned char		*arena;
	struct s_champ		*champs;
	t_car				*cars;
	int					qt_champ;
	int					qt_car;
	int					init_nub;
	int					cycle;
	int					c_to_die;
	int					last_check;
	int					qt_check;
	int					winner_id;
	int					dump;
	int					vis;
	int					col_mod;
	unsigned char		*a_col;
	int					last_break;
	int					microsec;
	int					pas;
	int					fin;
	int					resz;
	pthread_mutex_t		mut;
};

struct		s_champ
{
	unsigned char		name[PROG_NAME_LENGTH + 1];
	unsigned char		comment[COMMENT_LENGTH + 1];
	unsigned int		size;
	int					id;
	int					s_live;
	int					all_live;
	int					last_live;
	unsigned char		*code;
	t_champ				*next;
	int					col;
	int					col_live;
};

struct		s_car
{
	int					pos;
	int					carry;
	int					state;
	int					num;
	int					id;
	int					live;
	unsigned int		reg[REG_NUMBER];
	int					opcode;
	int					cycle;
	t_car				*next;
	t_car				*prev;
	int					sw;
	int					pos_res;
};

void		ft_parse_champion(t_core *core, int fd, int n);
void		ft_place_champ(t_core *core);
void		ft_create_car(t_core *core, t_champ *champ, int pos, t_car *tmp);
void		ft_dump(t_core *core);
void		ft_start_fight(t_core *core);
void		ft_fight_visual(t_core *core);
void		ft_key_pause(t_core *p, int ch);
void		ft_key_speedup(t_core *p);
void		ft_key_speeddown(t_core *p);
void		ft_key_reset(t_core *p);
void		ft_key_finish(t_core *p);
void		ft_is_paused(t_core *core);
void		ft_vfight_run(t_core *core, t_car *tmp);
void		ft_copy_car(t_core *core, t_car *src, int pos);
void		ft_make_check(t_core *core);
void		ft_opcode_switcher(t_core *core, t_car *car);
t_champ		*ft_get_champ(t_core *core, int id);
int			*ft_get_codage(t_core *core, t_car *car);
int			ft_check_cod_and_arg(t_car *car, int const *cod, int const *arg);
int			*ft_get_args(t_core *core, t_car *car, int const *cod);
int			ft_read_1(t_core *core, int pos);
int			ft_read_2(t_core *core, int pos);
int			ft_read_4(t_core *core, int pos);
void		ft_put_4(t_core *core, int arg, int pos);
void		ft_introduce(t_core *core);
void		ft_winner_is(t_core *core);
void		ft_01_opcode(t_core *core, t_car *car);
void		ft_02_opcode(t_core *core, t_car *car);
void		ft_03_opcode(t_core *core, t_car *car);
void		ft_04_opcode(t_core *core, t_car *car);
void		ft_05_opcode(t_core *core, t_car *car);
void		ft_06_opcode(t_core *core, t_car *car);
void		ft_07_opcode(t_core *core, t_car *car);
void		ft_08_opcode(t_core *core, t_car *car);
void		ft_09_opcode(t_core *core, t_car *car);
void		ft_10_opcode(t_core *core, t_car *car);
void		ft_11_opcode(t_core *core, t_car *car);
void		ft_12_opcode(t_core *core, t_car *car);
void		ft_13_opcode(t_core *core, t_car *car);
void		ft_14_opcode(t_core *core, t_car *car);
void		ft_15_opcode(t_core *core, t_car *car);
void		ft_16_opcode(t_core *core, t_car *car);

#endif
