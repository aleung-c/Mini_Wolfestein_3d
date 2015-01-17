/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 11:16:58 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/15 13:15:07 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void init_tracing(t_wolf *w)
{
	w->x_screen = 0;
	w->y_screen = 0;
	w->trace_y = 0;
	w->dist = 0.0;
<<<<<<< HEAD

=======
>>>>>>> 29301d8802db52516fab8a0089c6c263a7321faf
	w->angle_min = angle_check(w->angle + 30.0);
	w->angle_max = angle_check(w->angle - 30.0);
}

<<<<<<< HEAD
void ft_trace(t_wolf *w) // Pour tracer les rayons
{
	int color;

	color = 0x000000;
	
=======
void ft_trace(t_wolf *w)
{
>>>>>>> 29301d8802db52516fab8a0089c6c263a7321faf
 	init_tracing(w);
	while (w->x_screen != w->wolf_width)
	{
		w->x_wall_check = w->x;
		w->y_wall_check = w->y;
		ray_advances(w);
		w->dist = sqrt((w->x_wall_check - w->x) * (w->x_wall_check - w->x) + (w->y_wall_check - w->y) * (w->y_wall_check - w->y));
		w->dist = w->dist * cos(fabs(angle_check(w->angle - w->angle_min)) / 180.0 * M_PI);
<<<<<<< HEAD
		color = init_check_nxt_color(w, color);
=======
		w->color = init_check_nxt_color(w, w->color);
>>>>>>> 29301d8802db52516fab8a0089c6c263a7321faf
		w->prev_dist = w->dist;
		w->trace_wall_size = (w->wall_size / w->dist) * 290;
		while (w->y_screen < w->wolf_height)
		{
			ft_sky_trace(w);
<<<<<<< HEAD
			// mur
			ft_wall_trace(w, color);
			// sol
=======
			ft_wall_trace(w, w->color);
>>>>>>> 29301d8802db52516fab8a0089c6c263a7321faf
			ft_floor_trace(w, w->wolf_height);
			w->y_screen++;
		}
		w->trace_y = 0;
		w->y_screen = 0;
		w->angle_min = angle_check(w->angle_min -= 0.075);
		w->x_screen++;
	}
}

void ft_sky_trace(t_wolf *w)
{
	w->trace_sky_size = (w->wolf_height - w->trace_wall_size) / 2;
	while (w->trace_y < w->trace_sky_size)
	{
		w->img = pixel_put_to_image(w, w->x_screen, w->trace_y, 0x00CCFF);
		w->trace_y++;
	}
}

void ft_wall_trace(t_wolf *w, int color)
{
	int trace_iny;

	trace_iny = 0;
	while (trace_iny < w->trace_wall_size && w->trace_y < w->wolf_height)
	{
		w->img = pixel_put_to_image(w, w->x_screen, w->trace_y, color);
		w->trace_y++;
		trace_iny++;
	}
}

void ft_floor_trace(t_wolf *w, int height)
{
		while (w->trace_y < height)
		{
			w->img = pixel_put_to_image(w, w->x_screen, w->trace_y, 0xFFFFFF);
			w->trace_y++;
		}
}

int check_ray_map_pos_xy(t_wolf *w, int dist_adv)
{
	if (((fabs(remainder(w->x_wall_check, 64.0)) < dist_adv)) &&
	((fabs(remainder(w->y_wall_check, 64.0)) < dist_adv)))
	{
		if (w->map[pos_tb(w->y_wall_check)][pos_tb(w->x_wall_check)] != 0)
		{
			w->touch = 0;
			return(1);
		}
	}
	return (0);
}

int check_ray_map_pos_x(t_wolf *w, int dist_adv)
{
	if ((fabs(remainder(w->x_wall_check, 64.0)) < dist_adv))
			{
				if (w->map[pos_tb(w->y_wall_check)][pos_tb(w->x_wall_check)] != 0)
				{
					w->touch = 1;
					return (1);
				}
			}
			return (0);
}

int check_ray_map_pos_y(t_wolf *w, int dist_adv)
{
	if ((fabs(remainder(w->y_wall_check, 64.0)) < dist_adv))
	{
		if (w->map[pos_tb(w->y_wall_check)][pos_tb(w->x_wall_check)] != 0)
		{
			w->touch = 2;
			return (1);
		}
	}
	return (0);
}

void ray_advances(t_wolf *w)
{
	int r;
	double dist_adv;

	dist_adv = 0.1;
	r = 0;
	while (r == 0)
	{
<<<<<<< HEAD
		w->x_wall_check = w->x_wall_check + cos((w->angle_min / 180.0) * M_PI) * dist_adv; // modifier pour changer aliasing. Pour moins de cas problematiques, garder multiple de 2. 
		w->y_wall_check = w->y_wall_check - sin((w->angle_min / 180.0) * M_PI) * dist_adv;
		//dist_adv += 0.1;

		if ((((int)w->x_wall_check % 64 == 0) || ((int)w->x_wall_check % 64 == 63)) ||
			(((int)w->y_wall_check % 64 == 0) || ((int)w->y_wall_check % 64 == 63)))
		{
			if (((fabs(remainder(w->x_wall_check, 64.0)) < dist_adv)) &&
				((fabs(remainder(w->y_wall_check, 64.0)) < dist_adv)))
			{
				if (w->map[pos_tb(w->y_wall_check)][pos_tb(w->x_wall_check)] != 0)
				{
					w->touch = 0;
					r = 1;
				}
			}
			else if ((fabs(remainder(w->x_wall_check, 64.0)) < dist_adv))
			{
				if (w->map[pos_tb(w->y_wall_check)][pos_tb(w->x_wall_check)] != 0)
				{
					w->touch = 1;
					r = 1;
				}
			}
			else if ((fabs(remainder(w->y_wall_check, 64.0)) < dist_adv))
			{
				if (w->map[pos_tb(w->y_wall_check)][pos_tb(w->x_wall_check)] != 0)
				{
					w->touch = 2;
					r = 1;
				}
			}
=======
		w->x_wall_check = w->x_wall_check + cos((w->angle_min / 180.0) * M_PI) * dist_adv;
		w->y_wall_check = w->y_wall_check - sin((w->angle_min / 180.0) * M_PI) * dist_adv;
		if ((((int)w->x_wall_check % 64 == 0) || ((int)w->x_wall_check % 64 == 63)) ||
			(((int)w->y_wall_check % 64 == 0) || ((int)w->y_wall_check % 64 == 63)))
		{
			if ((check_ray_map_pos_xy(w, dist_adv)) == 1)
				r = 1;
			else if ((check_ray_map_pos_x(w, dist_adv)) == 1)
				r = 1;
			else if ((check_ray_map_pos_y(w, dist_adv)) == 1)
				r = 1;
>>>>>>> 29301d8802db52516fab8a0089c6c263a7321faf
		}
	}
}
