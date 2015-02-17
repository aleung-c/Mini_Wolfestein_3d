/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/18 13:44:23 by aleung-c          #+#    #+#             */
/*   Updated: 2015/02/17 14:32:09 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	end_check(t_wolf *w)
{
	int next_pos_x;
	int next_pos_y;

	next_pos_x = w->x + cos((w->angle / 180.0) * M_PI) * 8.0;
	next_pos_y = w->y - sin((w->angle / 180.0) * M_PI) * 8.0;
	if (w->map[next_pos_y / w->wall_size][next_pos_x / w->wall_size] == 2)
	{
		ft_putstr("End reached");
		exit(0);
	}
}

int		ft_wolf(t_wolf *w)
{
	wolf_key_check(w);
	end_check(w);
	ft_trace(w);
	mlx_put_image_to_window(w->mlx, w->win, w->imgv, 0, 0);
	ft_upview_map(w, 0, 0, 0);
	put_player_on_mmap(w);
	mlx_put_image_to_window(w->mlx, w->win, w->imgv_minimap, 820, 0);
	return (1);
}

int		expose_hook(t_wolf *w)
{
	int ret;

	ret = 0;
	mlx_put_image_to_window(w->mlx, w->win, w->imgv, 0, 0);
	mlx_put_image_to_window(w->mlx, w->win, w->imgv_minimap, 820, 0);
	return (ret);
}

int		main(void)
{
	t_wolf	w;

	w.map = ft_create_int_map("map.wolf");
	init_wolf_variables(&w);
	ft_init_mlx(&w);
	return (0);
}
