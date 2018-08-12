NAME = libft.a

SRC_NAME = ft_atoi.c ft_bzero.c ft_countw.c ft_isalpha.c ft_intrev.c ft_isascii.c ft_isprint.c ft_isdigit.c ft_lstadd.c ft_isalnum.c ft_lstdel.c ft_intsort.c ft_lstiter.c ft_lstmap.c ft_memalloc.c ft_itoa.c ft_memccpy.c ft_lstdelone.c ft_memchr.c ft_memdel.c ft_lstnew.c ft_memcmp.c ft_putchar.c ft_memcpy.c ft_memmove.c ft_putendl.c ft_putendl_fd.c ft_memset.c ft_putnbr.c ft_putchar_fd.c ft_putstr.c ft_putstr_fd.c ft_putnbr_fd.c ft_strcat.c ft_strclr.c ft_strdel.c ft_strchr.c ft_strcmp.c ft_strequ.c ft_strcpy.c ft_striter.c ft_strdup.c ft_strlen.c ft_striteri.c ft_strlcat.c ft_strjoin.c ft_strmapi.c ft_strmap.c ft_strncat.c ft_strnequ.c ft_strncmp.c ft_strnew.c ft_strncpy.c ft_strrev.c ft_strrchr.c ft_strsort.c ft_strsub.c ft_strnstr.c ft_strstr.c ft_toupper.c ft_strsplit.c ft_tolower.c ft_strtrim.c ft_printf.c itoa_base.c pr_num_str.c pr_uni_char.c type.c unicode.c get_next_line.c read.c

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_PATH = ./objs/

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

INC = libft.h

all: $(NAME)


$(NAME): $(OBJ) 
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@gcc -c -Wall -Werror -Wextra -o $@ -c $<

clean:
	@/bin/rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean:
	@/bin/rm -f $(NAME)

re: @fclean all

.PHONY: re all clean fclean

