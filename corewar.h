#ifndef COREWAR_COREWAR_H
#define COREWAR_COREWAR_H

# include "libft/libft.h"
# include "ft_printf/libftprintf.h"
# include "op.h"

typedef struct s_core
{
	unsigned char *arena;
	struct s_champ *champs;
} t_core;

typedef struct s_champ
{
	unsigned char name[PROG_NAME_LENGTH + 1];
	char comment[COMMENT_LENGTH + 1];
	unsigned int size;
	int id;
	unsigned char *code;
	struct s_champ *next;
} t_champ;

#endif
