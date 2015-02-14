#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/18 14:05:55 by aleung-c          #+#    #+#              #
#    Updated: 2015/02/14 16:29:30 by aleung-c         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = wolf3d

HEADER = wolf3d.h

SRC = wolf3d.c create_map.c colors.c angles.c minimap.c images.c trace.c keys.c \
keys2.c rays.c init_wolf.c textures.c

OBJ = $(SRC:.c=.o)

LIB = ./libft/

MLX = -L/usr/X11/lib -lXext -lX11 -lmlx

CC = gcc -g -Wall -Werror -Wall -Ofast -I/opt/X11/include

all : Lib $(NAME)

$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -L./libft/ -lft $(MLX)

Lib :
	make -C $(LIB)

clean :
	rm -rf $(OBJ)
	cd $(LIB) ; make clean

fclean : clean
	rm -rf $(NAME)
	cd $(LIB) ; make fclean

re : fclean all

.PHONY : all clean fclean re