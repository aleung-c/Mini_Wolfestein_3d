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

/*void ft_trace(t_wolf *w) // Pour tracer les rayons
{
	int x_screen;
	int y_screen;
	double dist;
	int color;
	int trace_iny;

	trace_iny = 0; //
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
}*/

void ft_trace(t_wolf *w) // Pour tracer les rayons
{
	//int x_screen;
	//int y_screen;
	double dist;
	int color;
	//int trace_iny;

	//trace_iny = 0; //
	color = 0x00CCFF;
	w->x_screen = 0;
	w->y_screen = 0;
	w->trace_y = 0;

 	init_view_angles(w);
	while (w->x_screen != w->wolf_width)
	{
		w->x_wall_check = w->x;
		w->y_wall_check = w->y;

		ray_advances(w);
		
		dist = sqrt((w->x_wall_check - w->x) * (w->x_wall_check - w->x) + (w->y_wall_check - w->y) * (w->y_wall_check - w->y));
		dist = dist * cos(fabs(w->angle - w->angle_min) / 180.0 * M_PI);
		//ft_putnbr(dist * sin((int)w->angle_min));
		//ft_putchar(' ');
		//dist = dist * sin((int)w->angle_min);
		//printf("%lf ", dist);
		color = color_less_dist(color, (int)dist / 6);
		
		//w->img = ft_line_trace(w, w->img, dist);
		while (w->y_screen < w->wolf_height)
		{
			//ciel
			ft_sky_trace(w, dist);
			//mur
			ft_wall_trace(w, dist, color);
			// sol
			ft_floor_trace(w);
			w->y_screen++;
		}
		//dist = 0.0;
		
			//ft_putnbr(w->trace_y);
			//ft_putchar(' ');
		w->trace_y = 0;
		//trace_iny = 0;
		w->y_screen = 0;
		color = 0x00FF00;
		w->angle_min = angle_check(w->angle_min -= 0.075); //0.075
		w->x_screen++;
	}
}

/*char *ft_line_trace(t_wolf *w, char *img, double dist)
{
	int trace_iny;
	int color;

	color = 0x00FF00;
	color = color_less_dist(color, (int)dist / 6);
	trace_iny = 0;
	while (w->y_screen < w->wolf_height)
	{
		//ciel
		while (w->trace_y < ((w->wolf_height) -  (w->wall_size / dist) * 290) / 2)
		{
			img = pixel_put_to_image(w, w->x_screen, w->trace_y, 0x00CCFF);
			w->trace_y++;
		}
		//mur
		while (trace_iny < (w->wall_size / dist) * 290 && w->trace_y < w->wolf_height)
		{
			//mlx_pixel_put(w->mlx, w->win, x_screen, trace_y + 200, 0x00CCFF);
			img = pixel_put_to_image(w, w->x_screen, w->trace_y, color);
			w->trace_y++;
			trace_iny++;
		}
		// sol
		while (w->trace_y < w->wolf_height)
		{
			img = pixel_put_to_image(w, w->x_screen, w->trace_y, 0xFFFFFF);
			w->trace_y++;
		}
		w->y_screen++;
	}
	return(img);
}*/

void ft_sky_trace(t_wolf *w, double dist)
{
	while (w->trace_y < ((w->wolf_height) - (w->wall_size / dist) * 290) / 2)
	{
		w->img = pixel_put_to_image(w, w->x_screen, w->trace_y, 0x00CCFF);
		w->trace_y++;
	}
}

void ft_wall_trace(t_wolf *w, double dist, int color)
{
	int trace_iny;

	trace_iny = 0;
	while (trace_iny < (w->wall_size / dist) * 290 && w->trace_y < w->wolf_height)
	{
		//mlx_pixel_put(w->mlx, w->win, x_screen, trace_y + 200, 0x00CCFF);
		w->img = pixel_put_to_image(w, w->x_screen, w->trace_y, color);
		w->trace_y++;
		trace_iny++;
	}
}

void ft_floor_trace(t_wolf *w)
{
		while (w->trace_y < w->wolf_height)
			{
				w->img = pixel_put_to_image(w, w->x_screen, w->trace_y, 0xFFFFFF);
				w->trace_y++;
			}
}