//
// Created by Vitalii LEVKO on 8/12/18.
//

#ifndef COREWAR_T_OP_H
#define COREWAR_T_OP_H

#include "op.h"


typedef struct s_op
{
	char *op;
	short qt_arg;
	unsigned char arg[3];
	short code;
	short cycle;
	char *exp;
	short codage;
	char lable;
} t_op;

extern t_op g_op_tab[17];

#endif //COREWAR_T_OP_H
