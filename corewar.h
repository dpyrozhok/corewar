#ifndef COREWAR_COREWAR_H
#define COREWAR_COREWAR_H

#include <stdio.h>
#include <fcntl.h>
# include "libft/libft.h"
# include "ft_printf/libftprintf.h"
# include "op.h"
# include "t_op.h"

typedef struct s_champ	t_champ;
typedef struct s_car	t_car;

typedef struct          s_core {
	unsigned char   *arena;
	struct s_champ  *champs;
	int             qt_champ;
	int             qt_car;
	int             init_nub;
	int             cycle;
	int             c_to_die;
	int             last_check;
	int             qt_check;
	int             winner_id;
	int				dump;
	int				v;
	int				c;
	unsigned char	*a;
	int				l;
	int				t;
}                       t_core;

struct          s_champ {
	unsigned char   name[PROG_NAME_LENGTH + 1];
	unsigned char   comment[COMMENT_LENGTH + 1];
	unsigned int    size;
	int             id;
	int             s_live;
	int             last_live;
	unsigned char   *code;
	t_car    		*cars;
	t_champ  		*next;
	int				c;
	int				cc;
};

struct              s_car {
	int             pos;
	int             carry;
	int             id;
	int             live;
	unsigned int    reg[REG_NUMBER];
	int             opcode;
	int             cycle;
	t_car    		*next;
	t_car    		*prev;
	int				sw;
	int				rp;
};


void    ft_dump(t_core *core);
void    ft_start_fight(t_core *core);
void    ft_copy_car(t_core *core, t_champ *champ, t_car *src, int pos);
void    ft_make_check(t_core *core);
void    ft_opcode_switcher(t_core *core, t_champ *champ);
int     *ft_get_codage(t_core *core, t_champ *champ);
int     ft_check_cod_and_arg(t_champ *champ, int const *cod, int const *arg);
int 	*ft_get_args(t_core *core, t_champ *champ, int const *cod);
int     ft_read_1(t_core *core, int pos);
int 	ft_read_2(t_core *core, int pos);
int 	ft_read_4(t_core *core, int pos);
void    ft_put_4(t_core *core, int arg, int pos);
void    ft_01_opcode(t_core *core, t_champ *champ);
void    ft_02_opcode(t_core *core, t_champ *champ);
void    ft_03_opcode(t_core *core, t_champ *champ);
void    ft_04_opcode(t_core *core, t_champ *champ);
void    ft_05_opcode(t_core *core, t_champ *champ);
void    ft_06_opcode(t_core *core, t_champ *champ);
void    ft_07_opcode(t_core *core, t_champ *champ);
void    ft_08_opcode(t_core *core, t_champ *champ);
void    ft_09_opcode(t_core *core, t_champ *champ);
void    ft_10_opcode(t_core *core, t_champ *champ);
void    ft_11_opcode(t_core *core, t_champ *champ);
void    ft_12_opcode(t_core *core, t_champ *champ);
void    ft_13_opcode(t_core *core, t_champ *champ);
void    ft_14_opcode(t_core *core, t_champ *champ);
void    ft_15_opcode(t_core *core, t_champ *champ);
#endif
