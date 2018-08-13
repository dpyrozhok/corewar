//
// Created by Vitalii LEVKO on 8/12/18.
//

#ifndef COREWAR_T_OP_H
#define COREWAR_T_OP_H

#include "op.h"

#define T_REG	1
#define T_DIR	2
#define T_IND	3

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

extern t_op op_tab[17];

#endif //COREWAR_T_OP_H
