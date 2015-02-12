/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 14:05:23 by aleung-c          #+#    #+#             */
/*   Updated: 2015/02/12 16:46:20 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ray_advances(t_wolf *w)
{
	int		r;
	double	add;
	double	sub;
	double	remainx;
	double	remainy;

	r = 0;
	add = cos((w->angle_min / 180.0) * M_PI) * 0.1;
	sub = sin((w->angle_min / 180.0) * M_PI) * 0.1;
	while (r == 0)
	{
		if (checkinter_xy(w) == 1)
		{
			remainx = fabs(remainder(w->x_wall_check, 64.0));
			remainy = fabs(remainder(w->y_wall_check, 64.0));
			if ((remainx < 0.1) && (remainy < 0.1))
				r = set_r_touch(w, 0);
			else if (remainx < 0.1)
				r = set_r_touch(w, 1);
			else if (remainy < 0.1)
				r = set_r_touch(w, 2);
		}
		w->x_wall_check = w->x_wall_check + add;
		w->y_wall_check = w->y_wall_check - sub;
	}
}

int		checkinter_xy(t_wolf *w)
{
	if ((((int)w->x_wall_check % 64 == 0) || ((int)w->x_wall_check % 64 == 63))
	|| (((int)w->y_wall_check % 64 == 0) || ((int)w->y_wall_check % 64 == 63)))
		return (1);
	return (0);
}

int		set_r_touch(t_wolf *w, int n)
{
	if (w->map[pos_tb(w->y_wall_check)][pos_tb(w->x_wall_check)] == 1)
	{
		w->touch = n;
		return (1);
	}
	return (0);
}

int		pos_tb(double val)
{
	return ((int)val / WALL_SIZE);
}

void	check_2_adv(t_wolf *w)
{
	double add;
	double sub;

	add = cos((angle_check(w->anglemin2) / 180.0) * M_PI) * 2.0;
	sub = sin((angle_check(w->anglemin2) / 180.0) * M_PI) * 2.0;
	while (w->map[pos_tb(w->y_wall_check_2)][pos_tb(w->x_wall_check_2)] == 0)
	{
		w->x_wall_check_2 = w->x_wall_check_2 + add;
		w->y_wall_check_2 = w->y_wall_check_2 - sub;
	}
}
