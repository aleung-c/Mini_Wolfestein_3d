/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/03 16:23:08 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/03 16:33:25 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int color_less_dist(int color, int dist)
{
	while (dist)
	{
		color--;
		dist--;
	}
	return (color);
}

int is_corner(t_wolf *w)
{
	if ((((int)w->x_wall_check % 64) == 0 || ((int)w->x_wall_check % 64) == 63) && \
		(((int)w->y_wall_check % 64) == 0 || ((int)w->y_wall_check % 64) == 63))
		return (1);
	return (0);
}

int check_wall_color(t_wolf *w) // marche mal, a revoir.
{
		/*ft_putnbr((int)w->x_wall_check % 64);
		ft_putchar(' ');*/
	//	ft_putnbr((int)w->y_wall_check % 64);
	//	ft_putchar(' ');

	if (((int)w->x_wall_check % 64) == 0 || ((int)w->x_wall_check % 64) == 63 )  // verif x par rapport a la grille imaginaire de 64.
	{
		if (!(((int)w->y_wall_check % 64) == 0 || ((int)w->y_wall_check % 64) == 63))
		{
			if (w->x >= w->x_wall_check)
			{
				return (0x0033CC); // bleu
			}
			else
			{
				return (0xFFCC33); // jaune
			}
		}
	}
	else if (((int)w->y_wall_check % 64) == 0 || ((int)w->y_wall_check % 64) == 63) // idem y.
	{
		if (w->y >= w->y_wall_check)
			return (0x009933); // vert
		else
			return (0xCC0033); // rouge
	}

	if (is_corner(w) == 1)
	{
	/*	w->x_wall_check = w->x;
		w->y_wall_check = w->y;
		while (w->map[(int)w->y_wall_check / 64][(int)w->x_wall_check / 64] == 0) // recup distance to wall
		{
			w->x_wall_check = w->x_wall_check + cos((angle_check(w->angle_min - 1.0) / 180.0) * M_PI) * 0.5; // modifier pour changer escaliers. 
			w->y_wall_check = w->y_wall_check - sin((angle_check(w->angle_min - 1.0) / 180.0) * M_PI) * 0.5; // 0.5 a la base
		}
		if (((int)w->x_wall_check % 64) == 0 || ((int)w->x_wall_check % 64) == 63 )  // verif x par rapport a la grille imaginaire de 64.
		{
			if (!(((int)w->y_wall_check % 64) == 0 || ((int)w->y_wall_check % 64) == 63))
			{
				if (w->x >= w->x_wall_check)
				{
					return (0x0033CC); // bleu
				}
				else
				{
					return (0xFFCC33); // jaune
				}
			}
		}
		else if (((int)w->y_wall_check % 64) == 0 || ((int)w->y_wall_check % 64) == 63) // idem y.
		{
			if (w->y >= w->y_wall_check)
				return (0x009933); // vert
			else
				return (0xCC0033); // rouge
		}*/
			return (0xFFFFFFF);
	}

	return (w->prev_color);
}


