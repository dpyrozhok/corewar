cmake_minimum_required(VERSION 3.9)
project(corewar C)

set(CMAKE_C_STANDARD 99)
set(LIBFT ${CMAKE_SOURCE_DIR}/libft/libft.a)
set(LIBFTPRINTF ${CMAKE_SOURCE_DIR}/ft_printf/libftprintf.a)

add_executable(corewar t_op.h op.c op.h main.c ncurs.c ncurs.h check_args.c check_args.h corewar.h start_fight.c check_isend.c opcode_switcher.c t_op.h opcode_11_16.c opcode_6_10.c op_handler.c opcode_1_5.c)
target_link_libraries(corewar -lncurses ${LIBFT} ${LIBFTPRINTF})
