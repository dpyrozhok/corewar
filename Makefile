# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 14:26:53 by popanase          #+#    #+#              #
#    Updated: 2018/09/23 23:31:28 by vlevko           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	make -C libft
	make -C assembler
	make -C virtual_machine

clean:
	make clean -C libft
	make clean -C assembler
	make clean -C virtual_machine

fclean: clean
	make fclean -C libft
	make fclean -C assembler
	make fclean -C virtual_machine

re: fclean all

.PHONY: all clean fclean re
