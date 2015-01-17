/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/03 16:40:22 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/16 13:39:29 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void ft_upview_map(t_wolf *w)
{
	int i;
	int j;
	int l;

	l = 0;
	i = 0;
	j = 0;
	while (i < w->size_y) 
	{
		while (j < w->size_l[l])
		{
			if (w->map[i][j] == 1 && (((j * w->minimap_wall_size)) < w->minimap_width) && (((i * w->minimap_wall_size)) < w->minimap_height))
				fill_square(w, ((j * w->minimap_wall_size)), ((i * w->minimap_wall_size)), 0xC8C8C8);
			else if (((j * w->minimap_wall_size)) < w->minimap_width && ((i * w->minimap_wall_size)) < w->minimap_height)
			{
				w->img_minimap = pixel_put_to_image_minimap(w, (j * w->minimap_wall_size), (i * w->minimap_wall_size), 0x000000);
				fill_square(w, (j * w->minimap_wall_size), (i * w->minimap_wall_size), 0x000000);
			}
			j++;
		}
		l++;
		i++;
		j = 0;
	}
}

void put_player_on_mmap(t_wolf *w)
{
	w->angle_min_map = angle_check(w->angle + 30.0);
	w->angle_max_map = angle_check(w->angle - 30.0);
	w->x_wall_check = (w->x / w->wall_size) * w->minimap_wall_size + (w->minimap_wall_size / 2);
	w->y_wall_check = (w->y / w->wall_size) * w->minimap_wall_size + (w->minimap_wall_size / 2);
	while (w->angle_min_map != w->angle_max_map)
	{
		while ((w->map[(int)w->y_wall_check / w->minimap_wall_size][(int)w->x_wall_check / w->minimap_wall_size] != 1) \
			&& (w->x_wall_check < w->minimap_width && w->y_wall_check < w->minimap_height))
		{
			//mlx_pixel_put(w->mlx, w->win, w->x_wall_check + 910, w->y_wall_check, color);
			w->img_minimap = pixel_put_to_image_minimap(w, w->x_wall_check, w->y_wall_check, 0x00CC33);
			w->x_wall_check = w->x_wall_check + cos((w->angle_min_map / 180.0) * M_PI) * 8.0;
			w->y_wall_check = w->y_wall_check - sin((w->angle_min_map / 180.0) * M_PI) * 8.0;
		}
		w->x_wall_check = (w->x / w->wall_size) * w->minimap_wall_size + (w->minimap_wall_size / 2);
		w->y_wall_check = (w->y / w->wall_size) * w->minimap_wall_size + (w->minimap_wall_size / 2);
		w->angle_min_map = angle_check(w->angle_min_map -= 4.0);
	}
}

void fill_square(t_wolf *w, int x, int y, int color)
{
	int size_y;
	int size_x;

	size_y = w->minimap_wall_size;
	size_x = w->minimap_wall_size;
	while (size_y && y < w->minimap_height)
	{
		while (size_x && x < w->minimap_width)
		{
			w->img_minimap = pixel_put_to_image_minimap(w, x, y, color);
			size_x--;
			x++;
		}
		x -= w->minimap_wall_size;
		size_y--;
		size_x = w->minimap_wall_size;
		y++;
	}
}