/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/03 16:40:22 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/03 16:40:54 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void ft_upview_map(t_wolf *w)
{
	unsigned int i;
	unsigned int j;
	int l;

	l = 0;
	i = 0;
	j = 0;
	// display map points upview et display int** map dans console.
	while (i < w->size_y) 
	{
		while (j < w->size_l[l])
		{
			if ((w->map[i][j] == 1 && (j * w->wall_size) < w->minimap_width) && (i * w->wall_size) < w->minimap_height)
			{
				fill_square(w, j * w->wall_size, i * w->wall_size, 0xC8C8C8);
			}
			else if ((j * w->wall_size) < w->minimap_width && (i * w->wall_size) < w->minimap_height)
			{
				w->img_minimap = pixel_put_to_image_minimap(w, j * w->wall_size, i * w->wall_size, 0xFFFFFF);
				fill_square(w, j * w->wall_size, i * w->wall_size, 0x000000);
			}
			//ft_putnbr(w->map[i][j]);
			//ft_putchar(' ');
			j++;
		}
		l++;
		i++;
		j = 0;
		//ft_putchar('\n');
	}
}

void fill_square(t_wolf *w, unsigned int x, unsigned int y, int color)
{
	int size_y;
	int size_x;

	size_y = w->wall_size;
	size_x = w->wall_size;
	while (size_y && y < w->minimap_height)
	{
		while (size_x && x < w->minimap_width)
		{
			w->img_minimap = pixel_put_to_image_minimap(w, x, y, color);
			size_x--;
			x++;
		}
		x -= w->wall_size;
		size_y--;
		size_x = w->wall_size;
		y++;
	}
}

void ft_upview_map_vfield(t_wolf *w)
{
	int color;

	color = 0x00CCFF;
	//mlx_pixel_put(w->mlx, w->win, w->x + 910, w->y, 0xFFFFFFF);
	w->img_minimap = pixel_put_to_image_minimap(w, w->x, w->y, 0xFFFFFF);
	//mlx_pixel_put(w->mlx, w->win, w->x_seg + 910, w->y_seg, 0xFF0000);
	w->img_minimap = pixel_put_to_image_minimap(w, w->x_seg, w->y_seg, 0xFF0000);
	//mlx_pixel_put(w->mlx, w->win, w->x_back + 910, w->y_back, 0x3333FF);
	//w->img_minimap = pixel_put_to_image_minimap(w, w->x_back, w->y_back, 0x0000CC);

	w->angle_min_map = angle_check(w->angle + 30.0);
	w->angle_max_map = angle_check(w->angle - 30.0);

	w->x_wall_check = w->x;
	w->y_wall_check = w->y;

	while (w->angle_min_map != w->angle_max_map)
	{
		while ((w->map[(int)w->y_wall_check / w->wall_size][(int)w->x_wall_check / w->wall_size] != 1) \
			&& (w->x_wall_check < w->minimap_width && w->y_wall_check < w->minimap_height))
		{
			//mlx_pixel_put(w->mlx, w->win, w->x_wall_check + 910, w->y_wall_check, color);
			w->img_minimap = pixel_put_to_image_minimap(w, w->x_wall_check, w->y_wall_check, 0x00CC33);
			w->x_wall_check = w->x_wall_check + cos((w->angle_min_map / 180.0) * M_PI) * 12.0;
			w->y_wall_check = w->y_wall_check - sin((w->angle_min_map / 180.0) * M_PI) * 12.0;
		}
		color++;
		w->x_wall_check = w->x;
		w->y_wall_check = w->y;
		w->angle_min_map = angle_check(w->angle_min_map -= 4.0);
	}
}
