/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 16:45:14 by aleung-c          #+#    #+#             */
/*   Updated: 2015/02/12 16:45:50 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_strafe(t_wolf *w, char c)
{
	int next_pos_x;
	int next_pos_y;
	int mod_angle;

	mod_angle = 0;
	if (c == 'r')
		mod_angle = angle_check(w->angle - 90);
	else if (c == 'l')
		mod_angle = angle_check(w->angle + 90);
	next_pos_x = w->x + cos((mod_angle / 180.0) * M_PI) * 12.0;
	next_pos_y = w->y - sin((mod_angle / 180.0) * M_PI) * 12.0;
	if (w->map[next_pos_y / w->wall_size][next_pos_x / w->wall_size] != 1)
	{
		w->x = w->x + cos((mod_angle / 180.0) * M_PI) * 6.0;
		w->y = w->y - sin((mod_angle / 180.0) * M_PI) * 6.0;
	}
}
