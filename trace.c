/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 11:16:58 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/06 11:17:10 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void ft_trace(t_wolf *w) // Pour tracer les rayons
{
	int x_screen;
	int y_screen;
	double dist;
	int color;
	int trace_iny;

trace_iny = 0;
	color = 0x00CCFF;
	x_screen = 0;
	y_screen = 0;
	w->trace_y = 0;

 	init_view_angles(w);
	while (x_screen != w->wolf_width)
	{
		w->x_wall_check = w->x;
		w->y_wall_check = w->y;

		ray_advances(w);
		//	dist = dist * cos(fabs(w->angle - w->angle_min) / 180 * M_PI);
		dist = sqrt((w->x_wall_check - w->x) * (w->x_wall_check - w->x) + (w->y_wall_check - w->y) * (w->y_wall_check - w->y));
		//dist = dist  * cos((int)w->angle);
		//printf("%lf ", dist);
		color = color_less_dist(color, (int)dist / 6);
		while (y_screen < w->wolf_height)
		{
			//ciel
			while (w->trace_y < ((w->wolf_height) -  (w->wall_size / dist) * 290) / 2)
			{
				w->img = pixel_put_to_image(w, x_screen, w->trace_y, 0x00CCFF);
				w->trace_y++;
			}
			//mur
			//ft_wall_trace(w, x_screen, dist);
			while (trace_iny < (w->wall_size / dist) * 290 && w->trace_y < w->wolf_height)
			{
				//mlx_pixel_put(w->mlx, w->win, x_screen, trace_y + 200, 0x00CCFF);
				w->img = pixel_put_to_image(w, x_screen, w->trace_y, color);
				w->trace_y++;
				trace_iny++;
			}
			// sol
			while (w->trace_y < w->wolf_height)
			{
				w->img = pixel_put_to_image(w, x_screen, w->trace_y, 0xFFFFFF);
				w->trace_y++;
			}
			y_screen++;
		}
		//dist = 0.0;
		w->trace_y = 0;
		trace_iny = 0;
		y_screen = 0;
		color = 0x00FF00;
		w->angle_min = angle_check(w->angle_min -= 0.075); //0.075
		x_screen++;
	}
}

void ft_wall_trace(t_wolf *w, int x_screen, int dist)
{
	int trace_iny;

	trace_iny = 0;
	while (trace_iny < (w->wall_size / dist) * 290 && w->trace_y < w->wolf_height)
	{
		//mlx_pixel_put(w->mlx, w->win, x_screen, trace_y + 200, 0x00CCFF);
		w->img = pixel_put_to_image(w, x_screen, w->trace_y, 0x006633);
		w->trace_y++;
		trace_iny++;
	}
}
