/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/18 13:44:23 by aleung-c          #+#    #+#             */
/*   Updated: 2014/12/18 13:44:48 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

int angle_rev(int angle)
{
	int angle_rev;

	angle_rev = angle + 180;
	if (angle_rev > 360)
	{
		angle_rev = angle_rev - 360;
	}
	return (angle_rev);
}

void ft_view(t_wolf *w) // A continuer, pb sur la finition du cercle.
{
	w->angle_min = w->angle + (60 / 2);
	w->angle_max = w->angle - (60 / 2);
	if(w->angle_min > 360)
		w->angle_min -= 360;
	if(w->angle_max < 0.0)
		w->angle_max += 360;

	w->x_wall_check = w->x + cos((w->angle_min / 180.0) * M_PI) * 12.0;
	w->y_wall_check = w->y - sin((w->angle_min / 180.0) * M_PI) * 12.0;
	if (w->angle_min > w->angle_max)
	{
		while(w->angle_min > w->angle_max)
		{
			while (w->map[w->y_wall_check / 64][w->x_wall_check / 64] != 1)
			{
				mlx_pixel_put(w->mlx, w->win, w->x_wall_check, w->y_wall_check, 0x00CCFF);
				w->x_wall_check = w->x_wall_check + cos((w->angle_min / 180.0) * M_PI) * 12.0;
				w->y_wall_check = w->y_wall_check - sin((w->angle_min / 180.0) * M_PI) * 12.0;
			}
			w->x_wall_check = w->x + cos((w->angle_min / 180.0) * M_PI) * 12.0;
			w->y_wall_check = w->y - sin((w->angle_min / 180.0) * M_PI) * 12.0;
			w->angle_min -= 1.0;
		}
	}
	else if (w->angle_min < w->angle_max)
	{
		while(w->angle_min < w->angle_max)
		{
			while (w->map[w->y_wall_check / 64][w->x_wall_check / 64] != 1)
			{
				mlx_pixel_put(w->mlx, w->win, w->x_wall_check, w->y_wall_check, 0x00CCFF);
				w->x_wall_check = w->x_wall_check + cos((w->angle_min / 180.0) * M_PI) * 12.0;
				w->y_wall_check = w->y_wall_check - sin((w->angle_min / 180.0) * M_PI) * 12.0;
			}
			w->x_wall_check = w->x + cos((w->angle_min / 180.0) * M_PI) * 12.0;
			w->y_wall_check = w->y - sin((w->angle_min / 180.0) * M_PI) * 12.0;
			w->angle_min -= 1.0;
			if(w->angle_min > 360)
			w->angle_min -= 360;
			if(w->angle_min < 0.0)
			w->angle_min += 360;
		}

	}
}

void 	ft_wolf(t_wolf *w)
{
	unsigned int i;
	unsigned int j;
	int l;

	i = 0;
	j = 0;
	l = 0;
	w->angle_rev = angle_rev(w->angle);
	w->x_seg = w->x + cos((w->angle / 180.0) * M_PI) * 12.0;
	w->y_seg = w->y - sin((w->angle / 180.0) * M_PI) * 12.0;
	w->x_back = w->x + cos((w->angle_rev / 180.0) * M_PI) * 12.0;
	w->y_back = w->y - sin((w->angle_rev / 180.0) * M_PI) * 12.0;
	mlx_pixel_put(w->mlx, w->win, w->x, w->y, 0xFFFFFFF);
	mlx_pixel_put(w->mlx, w->win, w->x_seg, w->y_seg, 0xFF0000);
	mlx_pixel_put(w->mlx, w->win, w->x_seg, w->y_seg, 0xFF0000);
	mlx_pixel_put(w->mlx, w->win, w->x_back, w->y_back, 0x3333FF);
	/*while (i < w->screen_width) // balayage ecran
	{
		while (j < w->screen_height)
		{
			mlx_pixel_put(w->mlx, w->win, i , j, 0xFFFFFFF);
			j++;
		}
		j = 0;
		i++;
	}*/
	while (i < w->size_y)
	{
		while (j < w->size_l[l])
		{
			if(w->map[i][j] == 1)
				mlx_pixel_put(w->mlx, w->win, j * 64, i * 64, 0xFF0000);
			else
				mlx_pixel_put(w->mlx, w->win, j * 64, i * 64, 0xFFFFFF);
			ft_putnbr(w->map[i][j]);
			ft_putchar(' ');
			j++;
		}
		l++;
		i++;
		j = 0;
		ft_putchar('\n');
	}
	ft_view(w);
}

void ft_advance(t_wolf *w)
{
	if (w->map[w->y_seg / 64][w->x_seg / 64] != 1)
	{
		w->x = w->x + cos((w->angle / 180.0) * M_PI) * 8.0;
		w->y = w->y - sin((w->angle / 180.0) * M_PI) * 8.0;
	}
}

void ft_backstep(t_wolf *w)
{
	if (w->map[w->y_back / 64][w->x_back / 64] != 1)
	{
		w->x = w->x - cos((w->angle / 180.0) * M_PI) * 12.0;
		w->y = w->y + sin((w->angle / 180.0) * M_PI) * 12.0;
	}
}

void init_wolf_variables(t_wolf *w)
{
	w->angle = 0.0;
	w->y = 5 * 64;
	w->x = 5 * 64;
	w->y_seg = w->y;
	w->x_seg = w->x;
	w->y_back = w->y;
	w->x_back = w->x;
	w->screen_width = 800;
	w->screen_height = 600;
}

int		expose_hook(t_wolf *w)
{
	int ret;

	ret = 0;
	mlx_clear_window(w->mlx, w->win);
	ft_wolf(w);
	return (ret);
}

int		key_hook(int keycode, t_wolf *w)
{
	if (keycode == 65363) // right
	{
		w->angle -= 8.0;
		if (w->angle < 1)
			w->angle = 360;
	}
	else if (keycode == 65361) // left
	{
		w->angle += 8.0;
		if (w->angle > 360.0)
			w->angle = 0.0;
	}
	else if (keycode == 65362) // up
	{
		ft_advance(w);
	}
	else if (keycode == 65364) // bottom
	{	
		ft_backstep(w);
	}
	else if (keycode == 65307)
	{
		ft_putendl("Exit Wolf3d");
		exit(0);
	}
	ft_putstr("Angle: ");
	ft_putnbr(w->angle);
	ft_putchar('\n');

	ft_putnbr(w->x * 9);
		ft_putstr("x ");
	ft_putnbr(w->y * 9);
		ft_putstr("y ");
	expose_hook(w);
	return (0);
}

void	ft_init_mlx(t_wolf *w)
{
	w->mlx = mlx_init();
	w->win = mlx_new_window(w->mlx, 800, 600, "wolf3d");
	mlx_expose_hook(w->win, expose_hook, w);
	mlx_key_hook(w->win, key_hook, w);
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
	display_int_map(w); //
	init_wolf_variables(&w);
	ft_init_mlx(&w);

	return (0);
}
