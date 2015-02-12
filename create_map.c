/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 13:21:39 by aleung-c          #+#    #+#             */
/*   Updated: 2015/02/12 16:31:27 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_ctoi(char c)
{
	int chiffre;

	chiffre = c - 48;
	return (chiffre);
}

int		**ft_create_int_map(char *arg)
{
	int		fd;
	int		**map;
	char	*buf;
	t_cp	cp;

	cp.i = 0;
	cp.x = 0;
	cp.y = 0;
	cp.ret = 0;
	if (!(fd = open(arg, O_RDONLY)))
		exit(0);
	buf = ft_strnew(4096);
	map = (int **)malloc(sizeof(int *) * 10);
	map = ft_read(map, buf, fd, &cp);
	free(buf);
	return (map);
}

int		**ft_read(int **map, char *buf, int fd, t_cp *cp)
{
	if ((cp->ret = read(fd, buf, 4096)))
	{
		while (buf[cp->i])
		{
			if (!(map[cp->y] = (int *)malloc(sizeof(int) * 15)))
				exit(0);
			while (buf[cp->i] != '\n' && buf[cp->i])
			{
				if (ft_isdigit(buf[cp->i]) == 1)
				{
					map[cp->y][cp->x] = ft_ctoi(buf[cp->i]);
					cp->x++;
				}
				cp->i++;
			}
			if (buf[cp->i] == '\n')
			{
				cp->y++;
				cp->x = 0;
				cp->i++;
			}
		}
	}
	return (map);
}
