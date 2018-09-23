NAME = asm

SRC_PATH = ./srcs/

OBJ_PATH = ./objs/

INC_PATH = ./inc/

SRC_NAME =	main.c main1.c main2.c main3.c main4.c main5.c main6.c main7.c main8.c main9.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

LDFLAGS = -L./inc/libft/

GRAPH = -lmlx -framework OpenGL -framework AppKit

LFT = -lft

CC = gcc $(CFLAGS)

CFLAGS = -Wall -Wextra -Werror


all: $(NAME)

$(NAME): $(OBJ) $(INC_PATH)
	@ make -C./inc/libft/
	@ $(CC) $(LDFLAGS) $(LFT) $(OBJ) -o $@ $(GRAPH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@ mkdir $(OBJ_PATH) 2> /dev/null || true
	@ $(CC) -I$(INC_PATH) -o $@ -c $<

clean: cleanlib
	@ rm -f $(OBJ)
	@ rmdir $(OBJ_PATH) 2> /dev/null || true

cleanlib:
	@ make clean -C ./inc/libft/

fclean: clean fcleanlib
	@ rm -f $(NAME)

fcleanlib:
	@ make fclean -C ./inc/libft/

re : fclean all

.PHONY : all clean fclean re