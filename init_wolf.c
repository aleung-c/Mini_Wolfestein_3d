/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 15:45:10 by aleung-c          #+#    #+#             */
/*   Updated: 2015/02/17 14:31:58 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_wolf_variables(t_wolf *w)
{
	int i;

	i = 0;
	init_preproc_var(w);
	init_key_var(w);
	w->angle = 0.0;
	w->y = 1.5 * w->wall_size;
	w->x = 1.5 * w->wall_size;
	w->size_y = 10;
	w->minimap_wall_size = 50 - w->size_y;
	w->charpos_x = 0;
	w->charpos_y = 0;
	w->prev_dist = 0.0;
	if (!(w->size_l = (int *)malloc(sizeof(int) * 30)))
		exit(0);
	while (i < 30)
	{
		w->size_l[i] = 30;
		i++;
	}
}

void	init_preproc_var(t_wolf *w)
{
	w->wall_size = WALL_SIZE;
	w->screen_width = SCREEN_W;
	w->screen_height = SCREEN_H;
	w->wolf_width = WOLF_W;
	w->wolf_height = WOLF_H;
	w->minimap_width = MMAP_W;
	w->minimap_height = MMAP_H;
}

void	init_key_var(t_wolf *w)
{
	w->right = 0;
	w->left = 0;
	w->up = 0;
	w->down = 0;
}

void	ft_init_mlx(t_wolf *w)
{
	if (!(w->mlx = mlx_init()))
		exit(0);
	if (!(w->win = mlx_new_window(w->mlx, \
	w->screen_width, w->screen_height, "wolf3d")))
		exit (0);
	w->imgv = mlx_new_image(w->mlx, w->wolf_width, w->wolf_height);
	w->img = mlx_get_data_addr(w->imgv, &w->bpp, &w->sizeline, &w->endian);
	w->imgv_minimap = mlx_new_image(w->mlx, w->minimap_width,
	w->minimap_height);
	w->img_minimap = mlx_get_data_addr(w->imgv_minimap, &w->bpp_minimap,
	&w->sizeline_minimap, &w->endian_minimap);
	ft_wolf(w);
	mlx_expose_hook(w->win, expose_hook, w);
	mlx_hook(w->win, KeyPress, KeyPressMask, key_press, w);
	mlx_hook(w->win, KeyRelease, KeyReleaseMask, key_release, w);
	mlx_loop_hook(w->mlx, ft_wolf, w);
	mlx_loop(w->mlx);
	mlx_destroy_image(w->mlx, w->imgv);
	mlx_destroy_image(w->mlx, w->imgv_minimap);
}

void	init_tracing(t_wolf *w)
{
	w->x_screen = 0;
	w->y_screen = 0;
	w->trace_y = 0;
	w->dist = 0.0;
	w->angle_min = angle_check(w->angle + 30.0);
	w->angle_max = angle_check(w->angle - 30.0);
}
