# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 14:26:53 by popanase          #+#    #+#              #
#    Updated: 2018/09/24 13:51:46 by vlevko           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../corewar

SRC = srcs/main.c \
	srcs/ft_start_fight.c \
	srcs/ft_prinnt_out.c \
	srcs/ft_fight_visual_1.c \
	srcs/ft_fight_visual_2.c \
	srcs/ft_check_isend.c \
	srcs/ft_bit_handler.c \
	srcs/ft_champ_handler.c \
	srcs/ft_car_handler.c \
	../op.c \
	srcs/ft_opcode_1_5.c \
	srcs/ft_opcode_11_15.c \
	srcs/ft_opcode_6_10.c \
	srcs/ft_opcode_handler.c \
	srcs/ft_check_args.c \
	srcs/ft_check_file.c \
	srcs/ft_dump_num.c \
	srcs/ft_dir_err.c \
	srcs/ft_print_help.c \
	srcs/ft_init_screen.c \
	srcs/ft_init_win.c \
	srcs/ft_fill_screen.c \
	srcs/ft_breakdown.c \
	srcs/ft_draw.c \
	srcs/ft_play_sound.c \
	srcs/ft_vcars_check_on.c \
	srcs/ft_vcars_champ.c

OBJ = $(SRC:.c=.o)

SDL = -F /Library/Frameworks -framework SDL2

all: $(NAME)

$(NAME): $(OBJ)
	make -C ../libft
	gcc -Wall -Wextra -Werror $^ $(SDL) -lpthread -lncurses -L../libft -lft -o $@
	
%.o: %.c
	gcc -Wall -Wextra -Werror -c $< -o $@

clean: 
	make clean -C ../libft
	rm -f $(OBJ)

fclean: clean 
	make fclean -C ../libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
