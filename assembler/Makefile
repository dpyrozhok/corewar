NAME = ../asm

SRC = main9.c \
	main8.c \
	main7.c \
	main6.c \
	main.c \
	main1.c \
	main4.c \
	main2.c \
	main3.c \
	main5.c \
	main10.c \
	../op.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -Wall -Wextra -Werror $^ -L ../libft -lft -o $@

%.o: %.c
	gcc -Wall -Wextra -Werror -c $<

clean: 
	rm -f $(OBJ)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
