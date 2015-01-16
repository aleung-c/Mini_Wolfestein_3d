/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/03 16:23:08 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/14 17:25:40 by aleung-c         ###   ########.fr       */
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
	//color = color_less_dist(color, w->dist);
	return (color);
}

int color_less_dist(int color, int dist)
{
	while (dist)
	{
		color--;
		dist--;
	}
	return (color);
}

int check_side_color_x(t_wolf *w)
{
	if (w->x >= w->x_wall_check_2)
			return (0x0033CC); // bleu
		else
			return (0xFFCC33); // jaune
}

int check_side_color_y(t_wolf *w)
{
	if (w->y >= w->y_wall_check_2)
			return (0x009933); // vert
		else
			return (0xCC0033); // rouge
}

int check_next_color(t_wolf *w)
{
	w->anglemin2 -= 100.0 / w->dist;
	w->x_wall_check_2 = w->x;
	w->y_wall_check_2 = w->y;
	while (w->map[pos_tb(w->y_wall_check_2)][pos_tb(w->x_wall_check_2)] == 0)
	{
		w->x_wall_check_2 = w->x_wall_check_2 + cos((angle_check(w->anglemin2) / 180.0) * M_PI) * 2.0; // modifier pour changer aliasing. 
		w->y_wall_check_2 = w->y_wall_check_2 - sin((angle_check(w->anglemin2) / 180.0) * M_PI) * 2.0;
	}
	w->next_dist = sqrt((w->x_wall_check_2 - w->x) * (w->x_wall_check_2 - w->x) + (w->y_wall_check_2 - w->y) * (w->y_wall_check_2 - w->y));
	w->next_dist = w->next_dist * cos(fabs(angle_check(w->angle - (w->anglemin2))) / 180.0 * M_PI);
	if (((int)w->x_wall_check_2 % 64) == 0 || ((int)w->x_wall_check_2 % 64) == 63 )  // verif x par rapport a la grille imaginaire de 64.
	{
		if (!(((int)w->y_wall_check_2 % 64) == 0 || ((int)w->y_wall_check_2 % 64) == 63))
			return (check_side_color_x(w));
	}
	else if (((int)w->y_wall_check_2 % 64) == 0 || ((int)w->y_wall_check_2 % 64) == 63) // idem y.
		return (check_side_color_y(w));
	return (check_next_color(w));
}

int check_prev_color(t_wolf *w)
{
	w->anglemin2 += 100.0 / w->dist;
	w->x_wall_check_2 = w->x;
	w->y_wall_check_2 = w->y;
	while (w->map[pos_tb(w->y_wall_check_2)][pos_tb(w->x_wall_check_2)] == 0)
	{
		w->x_wall_check_2 = w->x_wall_check_2 + cos((angle_check(w->anglemin2) / 180.0) * M_PI) * 2.0; // modifier pour changer aliasing. 
		w->y_wall_check_2 = w->y_wall_check_2 - sin((angle_check(w->anglemin2) / 180.0) * M_PI) * 2.0;
	}
	w->prev_dist = sqrt((w->x_wall_check_2 - w->x) * (w->x_wall_check_2 - w->x) + (w->y_wall_check_2 - w->y) * (w->y_wall_check_2 - w->y));
	w->prev_dist = w->prev_dist * cos(fabs(angle_check(w->angle - (w->anglemin2))) / 180.0 * M_PI);
	if (((int)w->x_wall_check_2 % 64) == 0 || ((int)w->x_wall_check_2 % 64) == 63 )  // verif x par rapport a la grille imaginaire de 64.
	{
		if (!(((int)w->y_wall_check_2 % 64) == 0 || ((int)w->y_wall_check_2 % 64) == 63))
			return (check_side_color_x(w));
	}
	else if (((int)w->y_wall_check_2 % 64) == 0 || ((int)w->y_wall_check_2 % 64) == 63) // idem y.
		return (check_side_color_y(w));
	return (check_prev_color(w));
}

int check_wall_color_simple(t_wolf *w) //determine couleur de maniere simple sans les coins.
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
			return (0x0033CC); // bleu
		else
			return (0xFFCC33); // jaune
	}
	else if (w->touch == 2)
	{
		if (w->y >= w->y_wall_check)
			return (0x009933); // vert
		else
			return (0xCC0033); // rouge
	}
	return (0xFFFFFF);
}