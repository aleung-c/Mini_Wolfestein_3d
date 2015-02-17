/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 16:20:52 by aleung-c          #+#    #+#             */
/*   Updated: 2015/02/17 14:14:49 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	wolf_key_check(t_wolf *w)
{
	if (w->right == 1)
		w->angle = angle_check(w->angle - 2);
	else if (w->left == 1)
		w->angle = angle_check(w->angle + 2);
	else if (w->sleft == 1)
		ft_strafe(w, 'l');
	else if (w->sright == 1)
		ft_strafe(w, 'r');
	else if (w->up == 1)
		ft_advance(w);
	else if (w->down == 1)
		ft_backstep(w);
}

int		key_press(int keycode, t_wolf *w)
{
	if (keycode == 65363)
		w->right = 1;
	else if (keycode == 65361)
		w->left = 1;
	else if (keycode == 65362 || keycode == 119)
		w->up = 1;
	else if (keycode == 65364 || keycode == 115)
		w->down = 1;
	else if (keycode == 97)
		w->sleft = 1;
	else if (keycode == 100)
		w->sright = 1;
	else if (keycode == 65307)
	{
		ft_putendl("Exit Wolf3d");
		exit(0);
	}
	return (0);
}

int		key_release(int keycode, t_wolf *w)
{
	if (keycode == 65363)
		w->right = 0;
	else if (keycode == 65361)
		w->left = 0;
	else if (keycode == 65362 || keycode == 119)
		w->up = 0;
	else if (keycode == 65364 || keycode == 115)
		w->down = 0;
	else if (keycode == 97)
		w->sleft = 0;
	else if (keycode == 100)
		w->sright = 0;
	return (0);
}

void	ft_advance(t_wolf *w)
{
	int next_pos_x;
	int next_pos_y;

	next_pos_x = w->x + cos((w->angle / 180.0) * M_PI) * 12.0;
	next_pos_y = w->y - sin((w->angle / 180.0) * M_PI) * 12.0;
	if (w->map[next_pos_y / w->wall_size][next_pos_x / w->wall_size] != 1)
	{
		w->x = w->x + cos((w->angle / 180.0) * M_PI) * 6.0;
		w->y = w->y - sin((w->angle / 180.0) * M_PI) * 6.0;
	}
}

void	ft_backstep(t_wolf *w)
{
	int back_pos_x;
	int back_pos_y;

	back_pos_x = w->x - cos((w->angle / 180.0) * M_PI) * 4.0;
	back_pos_y = w->y + sin((w->angle / 180.0) * M_PI) * 4.0;
	if (w->map[back_pos_y / w->wall_size][back_pos_x / w->wall_size] == 0)
	{
		w->x = back_pos_x;
		w->y = back_pos_y;
	}
}
