/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/18 13:44:23 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/02 17:56:55 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void ft_advance(t_wolf *w)
{
	if (w->map[w->y_seg / w->wall_size][w->x_seg / w->wall_size] == 0)
	{
		w->x = w->x + cos((w->angle / 180) * M_PI) * 6;
		w->y = w->y - sin((w->angle / 180) * M_PI) * 6;
	}
}

void ft_backstep(t_wolf *w)
{
	if (w->map[w->y_back / w->wall_size][w->x_back / w->wall_size] == 0)
	{
		w->x = w->x - cos((w->angle / 180) * M_PI) * 6;
		w->y = w->y + sin((w->angle / 180) * M_PI) * 6;
	}
}

void display_int_map(t_wolf w)
{
	unsigned int y;
	unsigned int x;
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
	if (w->right == 1) // right
	{
		w->angle = angle_check(w->angle - 2.0);
	}
	else if (w->left == 1) // left
	{
		w->angle = angle_check(w->angle + 2.0);
	}
	else if (w->up == 1) // up
	{
		ft_advance(w);
	}
	else if (w->down == 1) // bottom
	{	
		ft_backstep(w);
	}

	// les images :
	w->imgv = mlx_new_image(w->mlx, w->wolf_width, w->wolf_height); // declarer nouvelle image
	w->img = mlx_get_data_addr(w->imgv, &w->bpp, &w->sizeline, &w->endian); // initialise char* de l'image.
	// obtenir adresse de la string de l'image avec mlx get data addr.
	
	// Pour se deplacer en pixel dans l'image, il faut se deplacer en bits par rapports aux char de
	// la string, en connaissant la taille de la largeur de l'ecran.

	w->imgv_minimap = mlx_new_image(w->mlx, 700, 720);
	w->img_minimap = mlx_get_data_addr(w->imgv_minimap, &w->bpp_minimap, &w->sizeline_minimap, &w->endian_minimap);

	w->angle_rev = angle_rev(w->angle);
	w->x_seg = w->x + cos((w->angle / 180) * M_PI) * 6;
	w->y_seg = w->y - sin((w->angle / 180) * M_PI) * 6;
	w->x_back = w->x + cos((w->angle_rev / 180) * M_PI) * 6;
	w->y_back = w->y - sin((w->angle_rev / 180) * M_PI) * 6;

	ft_trace(w);
	mlx_put_image_to_window(w->mlx, w->win, w->imgv, 0, 0);

	ft_upview_map(w);
	ft_upview_map_vfield(w);
	mlx_put_image_to_window(w->mlx, w->win, w->imgv_minimap, 820, 0);

	mlx_destroy_image(w->mlx, w->imgv);
	mlx_destroy_image(w->mlx, w->imgv_minimap);
}

void init_wolf_variables(t_wolf *w)
{
	w->angle = 0.0;
	w->wall_size = WALL_SIZE;
	w->y = 5 * w->wall_size;
	w->x = 5 * w->wall_size;
	w->y_seg = w->y;
	w->x_seg = w->x;
	w->y_back = w->y;
	w->x_back = w->x;
	w->screen_width = SCREEN_W;
	w->screen_height = SCREEN_H;
	w->wolf_width = WOLF_W;
	w->wolf_height = WOLF_H;
	w->right = 0;
	w->left = 0;
	w->up = 0;
	w->down = 0;
}

int		expose_hook(t_wolf *w)
{
	int ret;

	ret = 0;
	//mlx_clear_window(w->mlx, w->win);
	ft_wolf(w);
	return (ret);
}

int		key_press(int keycode, t_wolf *w)
{
	if (keycode == 65363) // right
	{
		w->right = 1;
	//	w->angle = angle_check(w->angle - 2.0);
	}
	else if (keycode == 65361) // left
	{
		w->left = 1;
		//w->angle = angle_check(w->angle + 2.0);
	}
	else if (keycode == 65362) // up
	{
		w->up = 1;
		//ft_advance(w);
	}
	else if (keycode == 65364) // bottom
	{	
		w->down = 1;
		//ft_backstep(w);
	}
	else if (keycode == 65307)
	{
		ft_putendl("Exit Wolf3d");
		exit(0);
	}
	/*ft_putstr("Angle: ");
	ft_putnbr(w->angle);
	ft_putchar('\n');
	ft_putnbr(w->x);
	ft_putstr("x ");
	ft_putnbr(w->y);
	ft_putstr("y ");*/
	expose_hook(w);
	return (0);
}

int key_release(int keycode, t_wolf *w)
{
	if(w)
	{
			if (keycode == 65363) // right
			{
				w->right = 0;
			//	w->angle = angle_check(w->angle - 2.0);
			}
			else if (keycode == 65361) // left
			{
				w->left = 0;
				//w->angle = angle_check(w->angle + 2.0);
			}
			else if (keycode == 65362) // up
			{
				w->up = 0;
				//ft_advance(w);
			}
			else if (keycode == 65364) // bottom
			{	
				w->down = 0;
				//ft_backstep(w);
			}
	}
	return (0);
}

void	ft_init_mlx(t_wolf *w)
{
	w->mlx = mlx_init();
	w->win = mlx_new_window(w->mlx, w->screen_width, w->screen_height, "wolf3d");
	mlx_expose_hook(w->win, expose_hook, w);
	//mlx_key_hook(w->win, key_hook, w); // ft pour keyhook seul.

	// fonctions pour le KEY PRESS - KEY RELEASE
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
