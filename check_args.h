//
// Created by Vitalii LEVKO on 8/10/18.
//

#ifndef COREWAR_CHECK_ARGS_H
#define COREWAR_CHECK_ARGS_H
#include "corewar.h"

typedef struct	s_check
{
	char			buf[4];
	unsigned char	name[PROG_NAME_LENGTH];
	unsigned char	comment[COMMENT_LENGTH];
	unsigned int	size;
	unsigned char	*code;
}				t_check;

void	check_args(int ac, char **av, t_core *core);


#endif //COREWAR_CHECK_ARGS_H
