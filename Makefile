# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 14:26:53 by popanase          #+#    #+#              #
#    Updated: 2018/09/22 18:42:25 by vlevko           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

SRC = main.c \
    ft_start_fight.c \
    ft_prinnt_out.c \
    ft_fight_visual_1.c \
    ft_fight_visual_2.c \
    ft_check_isend.c \
    ft_bit_handler.c \
    ft_champ_handler.c \
    ft_car_handler.c \
    op.c \
    ft_opcode_1_5.c \
    ft_opcode_11_15.c \
    ft_opcode_6_10.c \
    ft_opcode_handler.c \
    ft_check_args.c \
    ft_check_file.c \
    ft_dump_num.c \
    ft_dir_err.c \
    ft_print_help.c \
    ft_init_screen.c \
    ft_init_win.c \
    ft_fill_screen.c \
    ft_breakdown.c \
    ft_draw.c \
    ft_play_sound.c \
    ft_vcars_check_on.c \
    ft_vcars_champ.c

OBJ = $(SRC:.c=.o)

# SDL = -L./SDL2/build/.libs/ -lSDL2
SDL = -F /Library/Frameworks -framework SDL2

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	@#make -C ft_printf
	@#gcc -Wall -Wextra -Werror $^ -lncurses -L./libft -lft -L./ft_printf -lftprintf -o $@
	gcc -Wall -Wextra -Werror $^ $(SDL) -lpthread -lncurses -L./libft -lft -o $@
	
%.o: %.c
	gcc -Wall -Wextra -Werror -c $<

clean: 
	make clean -C libft
	@#make clean -C ft_printf
	rm -f $(OBJ)

fclean: clean 
	make fclean -C libft
	@#make fclean -C ft_printf
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
