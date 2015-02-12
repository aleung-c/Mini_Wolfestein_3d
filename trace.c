/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 11:16:58 by aleung-c          #+#    #+#             */
/*   Updated: 2015/02/12 17:03:30 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_trace(t_wolf *w)
{
	w->color = 0x000000;
	init_tracing(w);
	while (w->x_screen != w->wolf_width)
	{
		w->x_wall_check = w->x;
		w->y_wall_check = w->y;
		ray_advances(w);
		w->dist = sqrt(((double)w->x_wall_check - (double)w->x) *
		((double)w->x_wall_check - (double)w->x) + ((double)w->y_wall_check -
		(double)w->y) * ((double)w->y_wall_check - (double)w->y));
		w->dist *= cos(fabs(w->angle_min - w->angle) / 180.0 * M_PI);
		w->color = init_check_nxt_color(w, w->color);
		w->prev_dist = w->dist;
		w->trace_wall_size = ((double)w->wall_size / w->dist) * 290.0;
		while (w->y_screen < w->wolf_height)
		{
			send_to_trace(w, w->color);
			w->y_screen++;
		}
		w->trace_y = 0;
		w->y_screen = 0;
		w->angle_min = angle_check(w->angle_min -= 0.075);
		w->x_screen++;
	}
}

void	send_to_trace(t_wolf *w, int color)
{
	ft_sky_trace(w);
	ft_wall_trace(w, color);
	ft_floor_trace(w, w->wolf_height);
}

void	ft_sky_trace(t_wolf *w)
{
	w->trace_sky_size = (w->wolf_height - w->trace_wall_size) / 2;
	while (w->trace_y < w->trace_sky_size)
	{
		w->img = pixel_put_to_image(w, w->x_screen, w->trace_y, 0x00CCFF);
		w->trace_y++;
	}
}

void	ft_wall_trace(t_wolf *w, int color)
{
	int trace_iny;

	trace_iny = 0;
	if (w->btn_txt == 2)
		ft_txt_trace(w);
	else
	{
		while (trace_iny < w->trace_wall_size && w->trace_y < w->wolf_height)
		{
			w->img = pixel_put_to_image(w, w->x_screen, w->trace_y, color);
			w->trace_y++;
			trace_iny++;
		}
	}
}

void	ft_floor_trace(t_wolf *w, int height)
{
	while (w->trace_y < height)
	{
		w->img = pixel_put_to_image(w, w->x_screen, w->trace_y, 0xFFFFFF);
		w->trace_y++;
	}
}
