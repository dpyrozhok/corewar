# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: popanase <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 14:26:53 by popanase          #+#    #+#              #
#    Updated: 2018/03/19 18:33:40 by popanase         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf.c ft_conver_x.c ft_conver_o.c ft_conver_s.c ft_conver_c.c \
	  ft_conver_id.c ft_conver_u.c ft_conver_per.c ft_conver_p.c ft_conver_lc.c \
	  ft_conver_ls.c ft_conver_inv.c ft_readformat.c ft_helper_lc_ls.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $^
	
%.o: %.c
	gcc -Wall -Wextra -Werror -c $<

clean: 
	rm -f $(OBJ)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
