#ifndef COREWAR_COREWAR_H
#define COREWAR_COREWAR_H

# include "libft/libft.h"
# include "ft_printf/libftprintf.h"
# include "op.h"

typedef struct          s_core {
    unsigned char   *arena;
    struct s_champ  *champs;
    int             qt_champ;
    int             init_nub;
    int             c_to_die;
}                       t_core;

typedef struct          s_champ {
    unsigned char   name[PROG_NAME_LENGTH + 1];
    unsigned char   comment[COMMENT_LENGTH + 1];
    unsigned int    size;
    int             id;
    int             s_live;
    int             last_live;
    unsigned char   *code;
    struct s_car    *cars;
    struct s_champ  *next;
}                       t_champ;

typedef struct              s_car {
    int             pos;
    int             carry;
    int             id;
    unsigned int    live;
    unsigned int    reg[REG_NUMBER];
    int             opcode;
    int             cycle;
    struct s_car    *next;
    struct s_car    *prev;
}                           t_car;
#endif
