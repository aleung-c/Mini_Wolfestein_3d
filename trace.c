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

	w->angle_min = angle_check(w->angle + 30.0);
	w->angle_max = angle_check(w->angle - 30.0);
}

void ft_trace(t_wolf *w) // Pour tracer les rayons
{
	int color;

	color = 0x000000;
	
 	init_tracing(w);
	while (w->x_screen != w->wolf_width)
	{
		w->x_wall_check = w->x;
		w->y_wall_check = w->y;
		ray_advances(w);
		w->dist = sqrt((w->x_wall_check - w->x) * (w->x_wall_check - w->x) + (w->y_wall_check - w->y) * (w->y_wall_check - w->y));
		w->dist = w->dist * cos(fabs(angle_check(w->angle - w->angle_min)) / 180.0 * M_PI);
		color = init_check_nxt_color(w, color);
		w->prev_dist = w->dist;
		w->trace_wall_size = (w->wall_size / w->dist) * 290;
		while (w->y_screen < w->wolf_height)
		{
			// ciel
			ft_sky_trace(w);
			// mur
			ft_wall_trace(w, color);
			// sol
			ft_floor_trace(w, w->wolf_height);
			w->y_screen++;
		}
		w->trace_y = 0;
		w->y_screen = 0;
		w->angle_min = angle_check(w->angle_min -= 0.075); //0.075
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
		//mlx_pixel_put(w->mlx, w->win, x_screen, trace_y + 200, 0x00CCFF);
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


/*void ray_advances(t_wolf *w) // version peu precise sur les coins. lag moins.
{
	while (w->map[(int)w->y_wall_check / 64][(int)w->x_wall_check / 64] == 0)
	{
		w->x_wall_check = w->x_wall_check + cos((w->angle_min / 180.0) * M_PI) * 0.5; // modifier pour changer aliasing. 
		w->y_wall_check = w->y_wall_check - sin((w->angle_min / 180.0) * M_PI) * 0.5;
	}
}*/

void ray_advances(t_wolf *w) // version tres precise de calcul des coins. Fonctionne
{
	int r;
	double dist_adv;

	dist_adv = 0.1;
	r = 0;
	while (r == 0)
	{
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
		}
	}
}
