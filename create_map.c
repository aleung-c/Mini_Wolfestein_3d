/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 13:21:39 by aleung-c          #+#    #+#             */
/*   Updated: 2014/12/17 10:41:17 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	*turn_space(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!(ft_isdigit(line[i])) && (line[i] != '-'))
			line[i] = ' ';
		if (line[i] == '-' && line[i + 1] == ' ')
			line[i] = ' ';
		i++;
	}
	return (line);
}

int		**ft_create_int_map(char *arg, t_wolf w)
{
	char	***tb;
	int		**map;
	int		x;
	int		y;
	int		l;

	l = 0;
	x = 0;
	y = 0;
	map = (int **)ft_memalloc(w.size_y);
	tb = ft_create_char_map(arg, w);
	while (tb[y])
	{
		map[y] = (int *)malloc(sizeof(int) * w.size_l[l]);
		while (tb[y][x])
		{
			map[y][x] = ft_atoi(tb[y][x]);
			x++;
		}
		x = 0;
		y++;
		l++;
	}
	w.map = map;
	return (map);
}

char	***ft_create_char_map(char *arg, t_wolf w)
{
	int		fd2;
	char	*line;
	char	***tb;
	int		i;

	i = 0;
	fd2 = open(arg, O_RDONLY);
	if (!(tb = (char ***)malloc(sizeof(char) * w.size_y + 1)))
		return (NULL);
	tb[w.size_y] = '\0';
	while (get_next_line(fd2, &line))
	{
		line = turn_space(line);
		tb[i] = ft_strsplit(line, ' ');
		i++;
	}
	tb[i] = '\0';
	return (tb);
}

unsigned int	ft_count_values(char *str, int c)
{
	unsigned int i;
	unsigned int val;

	i = 0;
	val = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			while (str[i] && str[i] == c)
				i++;
		}
		else if (str[i] != c)
		{
			val++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (val);
}

int				ft_measure_map(char *arg, t_wolf *w)
{
	int				fd1;
	int				fd2;
	char			*line;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if ((fd1 = open(arg, O_RDONLY)) == -1)
		return (-1);
	fd2 = open(arg, O_RDONLY);
	while (get_next_line(fd1, &line))
		i++;
	w->size_y = i;
	w->size_l = (unsigned int *)malloc(sizeof(int) * i);
	while (get_next_line(fd2, &line))
	{
		w->size_l[j] = ft_count_values(line, ' ');
		j++;
	}
	if (w->size_y == 0)
		return (-2);
	return (0);
}
