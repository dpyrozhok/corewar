#ifndef COREWAR_COREWAR_H
#define COREWAR_COREWAR_H

#include <stdio.h>
#include <fcntl.h>
# include "libft/libft.h"
# include "ft_printf/libftprintf.h"
# include "op.h"

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
};

void    ft_start_fight(t_core *core);
void    ft_make_check(t_core *core);
void    ft_opcode_switcher(t_core *core, t_champ *champ);
#endif