#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/18 14:05:55 by aleung-c          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2015/01/17 15:32:07 by aleung-c         ###   ########.fr        #
=======
#    Updated: 2015/01/16 16:26:17 by aleung-c         ###   ########.fr        #
>>>>>>> 29301d8802db52516fab8a0089c6c263a7321faf
#                                                                              #
#******************************************************************************#

NAME = wolf3d

HEADER = wolf3d.h

SRC = wolf3d.c create_map.c colors.c angles.c minimap.c images.c trace.c keys.c

SRCO = $(SRC:.c=.o)

LIB = ./libft/

MLX = -L/usr/X11/lib -lXext -lX11 -lmlx -I/opt/X11/include

$(NAME) :
	gcc -Ofast -c -Wall -Werror -Wextra $(SRC) $(MLX)
	cd $(LIB) ; make re
	gcc -Ofast -g -o $(NAME) $(HEADER) -Wall -Werror -Wextra $(SRCO) -L./libft/ -lft $(MLX)

clean :
	rm -rf $(SRCO)
	cd $(LIB) ; make clean

fclean : clean
	rm -rf $(NAME)
	cd $(LIB) ; make fclean

re : fclean $(NAME)
	./wolf3d
.PHONY : all clean fclean re