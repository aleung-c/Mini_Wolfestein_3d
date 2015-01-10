/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 11:16:58 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/07 15:32:41 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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


	/*ft_putnbr(w->x);
	ft_putchar(' ');
	ft_putnbr(w->y);
	ft_putchar('\n');*/
 	init_view_angles(w);
 	ft_putchar('\n'); //
	while (w->x_screen != w->wolf_width)
	{
		w->x_wall_check = w->x;
		w->y_wall_check = w->y;

		ray_advances(w);

		dist = sqrt((w->x_wall_check - w->x) * (w->x_wall_check - w->x) + (w->y_wall_check - w->y) * (w->y_wall_check - w->y));
		dist = dist * cos(fabs(angle_check(w->angle - w->angle_min)) / 180.0 * M_PI);
		//ft_putnbr(dist * sin((int)w->angle_min));
		//ft_putchar(' ');
		//dist = dist * sin((int)w->angle_min);
		//printf("%lf ", dist);
		color = check_wall_color(w);
		//color = color_less_dist(color, (int)dist / 6);
		w->prev_color = color;
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


/*void ray_advances(t_wolf *w) // version peu precise sur les coins.
{
	while (w->map[(int)w->y_wall_check / 64][(int)w->x_wall_check / 64] == 0)
	{
		w->x_wall_check = w->x_wall_check + cos((w->angle_min / 180.0) * M_PI) * 0.1; // modifier pour changer aliasing. 
		w->y_wall_check = w->y_wall_check - sin((w->angle_min / 180.0) * M_PI) * 0.1;
	}
}
*/


void ray_advances(t_wolf *w) // version tres precise de calcul des coins.
{
	int r;
	double x_approx;
	double y_approx;

	r = 0;
	while (r == 0)
	{
		w->x_wall_check = w->x_wall_check + cos((w->angle_min / 180.0) * M_PI) * 0.1; // modifier pour changer aliasing. 
		w->y_wall_check = w->y_wall_check - sin((w->angle_min / 180.0) * M_PI) * 0.1;
		
		x_approx = (((int)w->x_wall_check / 64) * 64.0);
		y_approx = (((int)w->y_wall_check / 64) * 64.0);

		if ((w->x_wall_check > x_approx - 0.2) && (w->x_wall_check < x_approx + 0.2))
		{
			if (w->x > w->x_wall_check)
			{
				if (w->map[(int)w->y_wall_check / 64][(int)w->x_wall_check / 64 - 1] != 0)
				r = 1;
			}
			else
			{
				if (w->map[(int)w->y_wall_check / 64][(int)w->x_wall_check / 64] != 0)
				r = 1;
			}
		}
		else if ((w->y_wall_check > y_approx - 0.2) && (w->y_wall_check < y_approx + 0.2))
		{
			if (w->y > w->y_wall_check)
			{
				if (w->map[(int)w->y_wall_check / 64 - 1][(int)w->x_wall_check / 64] != 0)
				r = 1;
			}
			else
			{
				if (w->map[(int)w->y_wall_check / 64][(int)w->x_wall_check / 64] != 0)
				r = 1;
			}

		}
	}
}
