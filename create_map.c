/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 13:21:39 by aleung-c          #+#    #+#             */
/*   Updated: 2015/02/11 16:59:49 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int ft_ctoi(char c)
{
	int chiffre;

	chiffre = c - 48;
	
	return (chiffre);
}

int		**ft_create_int_map(char *arg)
{
	int 	fd;
	int 	ret;
	int 	i;
	int 	y;
	int 	x;
	int		**map;
	char 	*buf;

	i = 0;
	y = 0;
	x = 0;
	if (!(fd = open(arg, O_RDONLY)))
		exit(0);
	buf = ft_strnew(4096);
	map = (int **)malloc(sizeof(int *) * 10);
	if ((ret = read(fd, buf, 4096)))
	{
	//	ft_putendl("Buf content :");
	//	ft_putstr(buf);		
		//y++;
		while (buf[i])
		{	
			if (!(map[y] = (int *)malloc(sizeof(int) * 15)))
				exit(0);
			while (buf[i] != '\n' && buf[i])
			{
				if (ft_isdigit(buf[i]) == 1)
				{
					map[y][x] = ft_ctoi(buf[i]);
					//ft_putnbr(map[y][x]);
					//ft_putchar(' ');
					x++;
				}
				i++;				
			}
			if (buf[i] == '\n')
			{
				//ft_putchar('\n');

				y++;
				x = 0;
				i++;
			}
		}
		free(buf);
	}
	
	return (map);
}
