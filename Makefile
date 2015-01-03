#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/18 14:05:55 by aleung-c          #+#    #+#              #
#    Updated: 2015/01/03 16:47:26 by aleung-c         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = wolf3d

HEADER = wolf3d.h

SRC = wolf3d.c create_map.c colors.c angles.c minimap.c images.c

SRCO = $(SRC:.c=.o)

LIB = ./libft/

MLX = -L/usr/X11/lib -lXext -lX11 -lmlx -I/opt/X11/include

$(NAME) :
	gcc -c -Wall -Werror -Wextra $(SRC) $(MLX)
	cd $(LIB) ; make re
	gcc -o $(NAME) $(HEADER) -Wall -Werror -Wextra $(SRCO) -L./libft/ -lft $(MLX)

clean :
	rm -rf $(SRCO)
	cd $(LIB) ; make clean

fclean : clean
	rm -rf $(NAME)
	cd $(LIB) ; make fclean

re : fclean $(NAME)
	./wolf3d
.PHONY : all clean fclean re