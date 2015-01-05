/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/03 16:34:02 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/03 16:40:09 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	angle_check(double angle)
{
	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return (angle);
}

int		angle_rev(int angle)
{
	int angle_rev;

	angle_rev = angle + 180;
	if (angle_rev > 360)
	{
		angle_rev = angle_rev - 360;
	}
	return (angle_rev);
}

void init_view_angles(t_wolf *w)
{
	w->angle_min = angle_check(w->angle + 30);
	w->angle_max = angle_check(w->angle - 30);
}

void ray_advances(t_wolf *w)
{
	while (w->map[(int)w->y_wall_check / 64][(int)w->x_wall_check / 64] == 0) // recup distance to wall
		{
			w->x_wall_check = w->x_wall_check + cos((w->angle_min / 180) * M_PI) * 1;
			w->y_wall_check = w->y_wall_check - sin((w->angle_min / 180) * M_PI) * 1;
		}
}