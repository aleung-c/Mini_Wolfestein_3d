/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measure_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 10:14:51 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/15 11:20:37 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			ft_check_map_size(t_axis *axis)
{
	if (axis->size_y > 20)
	{
		axis->scale_user -= 8;
		axis->pos_x_user += 200;
	}
	if (axis->size_y > 40)
	{
		axis->scale_user -= 4;
		axis->pos_x_user += 400;
	}
	if (axis->size_y > 80)
	{
		axis->scale_user -= 4;
		axis->pos_x_user += 100;
	}
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

int				ft_measure_map(char *arg, t_axis *axis)
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
	axis->size_y = i;
	if(!(axis->size_l = (unsigned int *)malloc(sizeof(int) * i)))
		return (NULL);
	while (get_next_line(fd2, &line))
	{
		axis->size_l[j] = ft_count_values(line, ' ');
		j++;
	}
	if (axis->size_y == 0)
		return (-2);
	return (0);
}
