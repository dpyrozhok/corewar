# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 14:26:53 by popanase          #+#    #+#              #
#    Updated: 2018/09/24 01:27:16 by vlevko           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = srcs/ft_memset.c srcs/ft_bzero.c srcs/ft_memcpy.c srcs/ft_memccpy.c \
	  srcs/ft_memmove.c srcs/ft_memchr.c srcs/ft_memcmp.c srcs/ft_strlen.c \
	  srcs/ft_strdup.c srcs/ft_strcpy.c srcs/ft_strncpy.c srcs/ft_strcat.c \
	  srcs/ft_strncat.c srcs/ft_strlcat.c srcs/ft_strchr.c srcs/ft_strrchr.c \
	  srcs/ft_strstr.c srcs/ft_strnstr.c srcs/ft_strcmp.c srcs/ft_strncmp.c \
	  srcs/ft_atoi.c srcs/ft_isalpha.c srcs/ft_isdigit.c srcs/ft_isalnum.c \
	  srcs/ft_isascii.c srcs/ft_isprint.c srcs/ft_toupper.c srcs/ft_tolower.c \
	  srcs/ft_memalloc.c srcs/ft_memdel.c srcs/ft_strnew.c srcs/ft_strdel.c \
	  srcs/ft_strclr.c srcs/ft_striter.c srcs/ft_striteri.c srcs/ft_strmap.c \
	  srcs/ft_strmapi.c srcs/ft_strequ.c srcs/ft_strnequ.c srcs/ft_strsub.c \
	  srcs/ft_strjoin.c srcs/ft_strtrim.c srcs/ft_strsplit.c srcs/ft_itoa.c \
	  srcs/ft_putchar.c srcs/ft_putstr.c srcs/ft_putendl.c srcs/ft_putnbr.c \
	  srcs/ft_putchar_fd.c srcs/ft_putstr_fd.c srcs/ft_putendl_fd.c \
	  srcs/ft_putnbr_fd.c srcs/ft_lstnew.c srcs/ft_lstdelone.c \
	  srcs/ft_lstdel.c srcs/ft_lstadd.c srcs/ft_lstiter.c srcs/ft_lstmap.c \
	  srcs/ft_cntwrd.c srcs/ft_lnwrd.c srcs/ft_lstaddend.c \
	  srcs/ft_lstdellast.c srcs/ft_swap.c srcs/ft_itoal.c srcs/ft_itoao.c \
	  srcs/ft_itoax.c srcs/ft_itoau.c srcs/get_next_line.c\
	  srcs/ft_printf/ft_printf.c srcs/ft_printf/ft_conver_x.c \
	  srcs/ft_printf/ft_conver_o.c srcs/ft_printf/ft_conver_s.c \
	  srcs/ft_printf/ft_conver_c.c srcs/ft_printf/ft_conver_id.c \
	  srcs/ft_printf/ft_conver_u.c srcs/ft_printf/ft_conver_per.c \
	  srcs/ft_printf/ft_conver_p.c srcs/ft_printf/ft_conver_lc.c \
	  srcs/ft_printf/ft_conver_ls.c srcs/ft_printf/ft_conver_inv.c \
	  srcs/ft_printf/ft_readformat.c srcs/ft_printf/ft_helper_lc_ls.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $^
	
%.o: %.c
	gcc -Wall -Wextra -Werror -c $< -o $@

clean: 
	rm -f $(OBJ)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
