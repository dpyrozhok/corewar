NAME = asm

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
    op.c
	 
 
	 

OBJ = $(SRC:.c=.o)

# SDL = -L./SDL2/build/.libs/ -lSDL2
# SDL = -F /Library/Frameworks -framework SDL2

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	@#make -C ft_printf
	@#gcc -Wall -Wextra -Werror $^ -lncurses -L./libft -lft -L./ft_printf -lftprintf -o $@
	gcc -Wall -Wextra -Werror $^ -L ./libft -lft -o $@
	
./srcs/%.o: %.c
	gcc -Wall -Wextra -Werror $< -o $@ $(INC)

clean: 
	make clean -C ./libft
	@#make clean -C ft_printf
	rm -f $(OBJ)

fclean: clean 
	make fclean -C ./libft
	@#make fclean -C ft_printf
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re