NAME = ../asm

SRC = free.c \
	name_comment_errors.c \
	check_args.c \
	push_back.c \
	helpful.c \
	read_body.c \
	go_through.c \
	write_label.c \
	write_commands.c \
	arguments.c \
	main.c \
	../op.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C ../libft
	gcc -Wall -Wextra -Werror $^ -L ../libft -lft -o $@

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
