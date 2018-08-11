cmake_minimum_required(VERSION 3.9)
project(corewar C)

set(CMAKE_C_STANDARD 99)
set(LIBFT ${CMAKE_SOURCE_DIR}/libft/libft.a)
set(LIBFTPRINTF ${CMAKE_SOURCE_DIR}/ft_printf/libftprintf.a)

add_executable(corewar main.c ncurs.c ncurs.h check_args.c check_args.h corewar.h start_fight.c check_isend.c opcode_switcher.c)
target_link_libraries(corewar -lncurses ${LIBFT} ${LIBFTPRINTF})
