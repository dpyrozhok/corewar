cmake_minimum_required(VERSION 3.9)
project(corewar C)

set(CMAKE_C_STANDARD 99)
set(LIBFT ${CMAKE_SOURCE_DIR}/libft/libft.a)
set(LIBFTPRINTF ${CMAKE_SOURCE_DIR}/ft_printf/libftprintf.a)

add_executable(corewar t_op.h op.c op.h main.c ncurs.c ncurs.h check_args.c check_args.h corewar.h ft_start_fight.c ft_check_isend.c ft_bit_handler.c t_op.h ft_opcode_11_15.c ft_opcode_6_10.c ft_opcode_handler.c ft_opcode_1_5.c ft_fight_visual_1.c ft_fight_visual_2.c)
target_link_libraries(corewar -lncurses ${LIBFT} ${LIBFTPRINTF})
