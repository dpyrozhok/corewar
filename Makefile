NAME = asm

SRC_PATH = ./srcs/

OBJ_PATH = ./objs/

INC_PATH = ./inc/

SRC_NAME =	main.c free.c 1.c 2.c 3.c 4.c 5.c 6.c 7.c 8.c 9.c 10.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

LDFLAGS = -L./libft/

GRAPH = -lmlx -framework OpenGL -framework AppKit

LFT = -lft

CC = gcc $(CFLAGS)

CFLAGS = -Wall -Wextra -Werror


all: $(NAME)

$(NAME): $(OBJ) $(INC_PATH)
	@ make -C./libft/
	@ $(CC) $(LDFLAGS) $(LFT) $(OBJ) -o $@ $(GRAPH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@ mkdir $(OBJ_PATH) 2> /dev/null || true
	@ $(CC) -I$(INC_PATH) -o $@ -c $<

clean: cleanlib
	@ rm -f $(OBJ)
	@ rmdir $(OBJ_PATH) 2> /dev/null || true

cleanlib:
	@ make clean -C ./libft/

fclean: clean fcleanlib
	@ rm -f $(NAME)

fcleanlib:
	@ make fclean -C ./libft/

re : fclean all

.PHONY : all clean fclean re