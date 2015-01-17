/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/18 13:44:23 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/16 15:08:30 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int pos_tb(double val)
{
	int wall_size;

	wall_size = WALL_SIZE;
	return ((int)val  / wall_size);
}

void display_int_map(t_wolf w)
{
	int y;
	int x;
	int l;

	l = 0;
	y = 0;
	x = 0;
	while (y < w.size_y)
	{
		while (x < w.size_l[l])
		{
			ft_putnbr(w.map[y][x]);
			ft_putchar(' ');
			x++;
		}
		ft_putchar('\n');
		x = 0;
		l++;
		y++;
	}
}

void 	ft_wolf(t_wolf *w)
{
	wolf_key_check(w);	

	w->imgv = mlx_new_image(w->mlx, w->wolf_width, w->wolf_height);
	w->img = mlx_get_data_addr(w->imgv, &w->bpp, &w->sizeline, &w->endian);

	w->imgv_minimap = mlx_new_image(w->mlx, w->minimap_width, w->minimap_height);
	w->img_minimap = mlx_get_data_addr(w->imgv_minimap, &w->bpp_minimap, &w->sizeline_minimap, &w->endian_minimap);

	ft_trace(w);
	mlx_put_image_to_window(w->mlx, w->win, w->imgv, 0, 0);

	ft_upview_map(w);
	put_player_on_mmap(w);
	mlx_put_image_to_window(w->mlx, w->win, w->imgv_minimap, 820, 0);

	mlx_destroy_image(w->mlx, w->imgv);
	mlx_destroy_image(w->mlx, w->imgv_minimap);
}

void 	init_wolf_variables(t_wolf *w)
{
	w->angle = 0.0;
	w->wall_size = WALL_SIZE;
	w->y = 1.5 * w->wall_size;
	w->x = 1.5 * w->wall_size;
	w->screen_width = SCREEN_W;
	w->screen_height = SCREEN_H;
	w->wolf_width = WOLF_W;
	w->wolf_height = WOLF_H;
<<<<<<< HEAD

	w->minimap_wall_size = 50 -  w->size_y;
	w->minimap_width = MMAP_W;
	w->minimap_height = MMAP_H;
	//w->charpos_x = 0;
	//w->charpos_y = 0;
=======
	
	w->minimap_wall_size = 50 -  w->size_y;
	w->minimap_width = MMAP_W;
	w->minimap_height = MMAP_H;
	w->charpos_x = 0;
	w->charpos_y = 0;
>>>>>>> 29301d8802db52516fab8a0089c6c263a7321faf

	w->right = 0;
	w->left = 0;
	w->up = 0;
	w->down = 0;

	w->prev_dist = 0.0;
}

int		expose_hook(t_wolf *w)
{
	int ret;

	ret = 0;
	//mlx_clear_window(w->mlx, w->win);
	ft_wolf(w);
	return (ret);
}



void	ft_init_mlx(t_wolf *w)
{
	w->mlx = mlx_init();
	w->win = mlx_new_window(w->mlx, w->screen_width, w->screen_height, "wolf3d");
	mlx_expose_hook(w->win, expose_hook, w);

	mlx_hook(w->win, KeyPress, KeyPressMask, key_press, w);
	mlx_hook(w->win, KeyRelease, KeyReleaseMask, key_release, w);
	mlx_loop_hook(w->win, key_press, w);
	mlx_loop(w->mlx);
}

int main(void)
{
	t_wolf 	w;

	if ((ft_measure_map("map.wolf", &w)) == -1)
	{
		perror("map.wolf");
		return (0);
	}
	w.map = ft_create_int_map("map.wolf", w);
	//display_int_map(w); //
	init_wolf_variables(&w);
	ft_init_mlx(&w);

	return (0);
}
