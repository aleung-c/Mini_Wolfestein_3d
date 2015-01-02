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

double angle_check(double angle)
{
	if (angle > 360.0)
		angle -= 360.0;
	if (angle < 0.0)
		angle += 360.0;
	return (angle);
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

char *pixel_put_to_image(/*unsigned long img_color,*/ t_wolf *w, int x, int y)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	b = 255;
	g = 200;
	r = 0;

// (screen_width * bits per pixel(pas sur)) * position dans la colonne (y) + (x * bits per pixels)

	w->img[(y * w->sizeline) + (x * (w->bpp / 8))] = b;
	w->img[(y * w->sizeline) + (x * (w->bpp / 8)) + 1] = g;
	w->img[(y * w->sizeline) + (x * (w->bpp / 8)) + 2] = r;
	return (w->img);
}

void ft_wall_trace(t_wolf *w) // Pour tracer les rayons
{
	int x_screen;
	int y_screen;
	double dist;
	int trace_y;
	int trace_iny;

	x_screen = 0;
	y_screen = 0;
	dist = 0.0;
	trace_y = 0;
	trace_iny = 0;


	w->x_wall_check = w->x;
	w->y_wall_check = w->y;
	w->angle_min = angle_check(w->angle + (60.0 / 2.0));
	w->angle_max = angle_check(w->angle - (60.0 / 2.0));
	while (x_screen != w->screen_width)
	{
		while (w->map[(int)w->y_wall_check / 64][(int)w->x_wall_check / 64] == 0) // recup distance to wall
		{
	//		dist += 1.0;
			w->x_wall_check = w->x_wall_check + cos((w->angle_min / 180.0) * M_PI) * 1.0;
			w->y_wall_check = w->y_wall_check - sin((w->angle_min / 180.0) * M_PI) * 1.0;
		}
//		dist = dist * cos(fabs(w->angle - w->angle_min) / 180 * M_PI);
		dist = sqrt((w->x_wall_check - w->x) * (w->x_wall_check - w->x) + (w->y_wall_check - w->y) * (w->y_wall_check - w->y));
		printf("%lf ", dist);
		while (y_screen < w->screen_height)
		{
			while (trace_y < (400.0 -  (64.0 / dist) * 290) / 2)
				trace_y++;
			while (trace_iny < (64.0 / dist) * 290 && trace_y < w->screen_height)
			{
				//mlx_pixel_put(w->mlx, w->win, x_screen, trace_y + 200, 0x00CCFF);
				w->img = pixel_put_to_image(w, x_screen, trace_y);
				trace_y++;
				trace_iny++;
			}
			y_screen++;
		}
		dist = 0.0;
		trace_y = 0;
		trace_iny = 0;
		y_screen = 0;

		w->x_wall_check = w->x;
		w->y_wall_check = w->y;

		w->angle_min = angle_check(w->angle_min -= 0.075); //0.075
		x_screen++;
	}
}

void ft_upview_map(t_wolf *w)
{
	unsigned int i;
	unsigned int j;
	int l;

	l = 0;
	i = 0;
	j = 0;
	// display map points upview et display int** map dans console.
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
}

void ft_upview_map_vfield(t_wolf *w) // Semble Ok. Peut poser pb sur l'ordre de tracage des colonnes
{
	int color;

	color = 0x00CCFF;
	w->angle_min = w->angle + (60 / 2);
	w->angle_max = w->angle - (60 / 2);
	if (w->angle_min > 360)
		w->angle_min -= 360;
	if (w->angle_max < 0.0)
		w->angle_max += 360;

	w->x_wall_check = w->x;
	w->y_wall_check = w->y;

	while (w->angle_min != w->angle_max)
	{
		while (w->map[(int)w->y_wall_check / 64][(int)w->x_wall_check / 64] != 1)
		{
			mlx_pixel_put(w->mlx, w->win, w->x_wall_check, w->y_wall_check, color);
			w->x_wall_check = w->x_wall_check + cos((w->angle_min / 180.0) * M_PI) * 6.0;
			w->y_wall_check = w->y_wall_check - sin((w->angle_min / 180.0) * M_PI) * 6.0;
		}
		color++;
		w->x_wall_check = w->x;
		w->y_wall_check = w->y;
		w->angle_min -= 1.0;
		if(w->angle_min > 360)
		w->angle_min -= 360;
		if(w->angle_min < 0.0)
		w->angle_min += 360;
	}
}

void 	ft_wolf(t_wolf *w)
{
// les images :
	w->imgv = mlx_new_image(w->mlx, 800, 600); // declarer nouvelle image
	w->img = mlx_get_data_addr(w->imgv, &w->bpp, &w->sizeline, &w->endian); // initialise char* de l'image.
// obtenir adresse de la string de l'image avec mlx get data addr.
// dessiner dans la string en se positionnant avec la formule suivante :

// (screen_width * bits per pixel(pas sur)) * position dans la colonne (y) + (x * bits per pixels)

// en effet, pour se deplacer en pixel dans l'image, il faut se deplacer en bits par rapports aux char de
// la string, en connaissant la taille de la largeur de l'ecran.

	w->angle_rev = angle_rev(w->angle);
	w->x_seg = w->x + cos((w->angle / 180.0) * M_PI) * 6.0;
	w->y_seg = w->y - sin((w->angle / 180.0) * M_PI) * 6.0;
	w->x_back = w->x + cos((w->angle_rev / 180.0) * M_PI) * 6.0;
	w->y_back = w->y - sin((w->angle_rev / 180.0) * M_PI) * 6.0;
	mlx_pixel_put(w->mlx, w->win, w->x, w->y, 0xFFFFFFF);
	mlx_pixel_put(w->mlx, w->win, w->x_seg, w->y_seg, 0xFF0000);
	mlx_pixel_put(w->mlx, w->win, w->x_seg, w->y_seg, 0xFF0000);
	mlx_pixel_put(w->mlx, w->win, w->x_back, w->y_back, 0x3333FF);


	ft_wall_trace(w);
	mlx_put_image_to_window(w->mlx, w->win, w->imgv, 0, 0);
	mlx_destroy_image(w->mlx, w->imgv);
	ft_upview_map(w);
	ft_upview_map_vfield(w);
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
		w->x = w->x - cos((w->angle / 180.0) * M_PI) * 8.0;
		w->y = w->y + sin((w->angle / 180.0) * M_PI) * 8.0;
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
		w->angle = angle_check(w->angle - 2.0);
	}
	else if (keycode == 65361) // left
	{
		w->angle = angle_check(w->angle + 2.0);
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

int key_release(int keycode, t_wolf *w)
{
	if(w)
	{
		if (keycode == 65307)
		{
			ft_putendl("Exit Wolf3d");
			exit(0);
		}
	}
	return (0);
}

void	ft_init_mlx(t_wolf *w)
{
	w->mlx = mlx_init();
	w->win = mlx_new_window(w->mlx, 800, 600, "wolf3d");
	mlx_expose_hook(w->win, expose_hook, w);
	//mlx_key_hook(w->win, key_hook, w); // ft pour keyhook seul.

	// fonctions pour le KEY PRESS - KEY RELEASE
	mlx_hook(w->win, KeyPress, KeyPressMask, key_hook, w);
	mlx_hook(w->win, KeyRelease, KeyReleaseMask, key_release, w);
	mlx_loop_hook(w->win, key_hook, w);
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
