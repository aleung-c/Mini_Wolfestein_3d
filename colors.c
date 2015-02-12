/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/03 16:23:08 by aleung-c          #+#    #+#             */
/*   Updated: 2015/02/12 15:57:09 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int init_check_nxt_color(t_wolf *w, int color)
{
	w->anglemin2 = w->angle_min;
	w->next_color = check_next_color(w);
	w->anglemin2 = w->angle_min;
	w->prev_color = check_prev_color(w);
	color = check_wall_color_simple(w);
	w->prev_color_used = color;
	return (color);
}

int check_color_orientation(t_wolf *w)
{
	if (((int)w->x_wall_check_2 % 64) == 0 || ((int)w->x_wall_check_2 % 64)
	== 63)
	{
		if (!(((int)w->y_wall_check_2 % 64) == 0 ||
		((int)w->y_wall_check_2 % 64) == 63))
		{
			if (w->x >= w->x_wall_check_2)
				return (0x0033CC);
			else
				return (0xFFCC33);
		}
	}
	else if (((int)w->y_wall_check_2 % 64) == 0 ||
		((int)w->y_wall_check_2 % 64) == 63)
	{
		if (w->y >= w->y_wall_check_2)
			return (0x009933);
		else
			return (0xCC0033);
	}
	return (check_next_color(w));
}

int check_next_color(t_wolf *w)
{
	w->anglemin2 -= 100.0 / w->dist;
	w->x_wall_check_2 = w->x;
	w->y_wall_check_2 = w->y;
	check_2_adv(w);
	w->next_dist = sqrt((w->x_wall_check_2 - w->x) * (w->x_wall_check_2
	- w->x)
	+ (w->y_wall_check_2 - w->y) * (w->y_wall_check_2 - w->y));
	w->next_dist = w->next_dist * cos(fabs(angle_check(w->angle -
	(w->anglemin2))) / 180.0 * M_PI);
	return (check_color_orientation(w));
}

int check_prev_color(t_wolf *w)
{
	w->anglemin2 += 100.0 / w->dist;
	w->x_wall_check_2 = w->x;
	w->y_wall_check_2 = w->y;
	check_2_adv(w);
	w->prev_dist = sqrt((w->x_wall_check_2 - w->x) * (w->x_wall_check_2 - w->x)
	+ (w->y_wall_check_2 - w->y) * (w->y_wall_check_2 - w->y));
	w->prev_dist = w->prev_dist * cos(fabs(angle_check(w->angle -
	(w->anglemin2))) / 180.0 * M_PI);
	return (check_color_orientation(w));
}

int check_wall_color_simple(t_wolf *w)
{
	if (w->touch == 0)
	{
		if (w->touch == 0 && fabs((int)w->prev_dist - (int)w->dist) > 20)
			return (w->next_color);
		else
			return (w->prev_color_used);
	}
	if (w->touch == 1)
	{
		if (w->x >= w->x_wall_check)
			return (0x0033CC);
		else
			return (0xFFCC33);
	}
	else if (w->touch == 2)
	{
		if (w->y >= w->y_wall_check)
			return (0x009933);
		else
			return (0xCC0033);
	}
	return (0xFFFFFF);
}
