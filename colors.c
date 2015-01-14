/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/03 16:23:08 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/14 17:25:40 by aleung-c         ###   ########.fr       */
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

int check_next_color(t_wolf *w)
{
	w->anglemin2 -= 1.0;
	w->x_wall_check_2 = w->x;
	w->y_wall_check_2 = w->y;
	while (w->map[pos_tb(w->y_wall_check_2)][pos_tb(w->x_wall_check_2)] == 0)
	{
		w->x_wall_check_2 = w->x_wall_check_2 + cos((angle_check(w->anglemin2) / 180.0) * M_PI) * 1.0; // modifier pour changer aliasing. 
		w->y_wall_check_2 = w->y_wall_check_2 - sin((angle_check(w->anglemin2) / 180.0) * M_PI) * 1.0;
	}
	w->next_dist = sqrt((w->x_wall_check_2 - w->x) * (w->x_wall_check_2 - w->x) + (w->y_wall_check_2 - w->y) * (w->y_wall_check_2 - w->y));
	w->next_dist = w->next_dist * cos(fabs(angle_check(w->angle - (w->anglemin2))) / 180.0 * M_PI);

	if (((int)w->x_wall_check_2 % 64) == 0 || ((int)w->x_wall_check_2 % 64) == 63 )  // verif x par rapport a la grille imaginaire de 64.
	{
		if (!(((int)w->y_wall_check_2 % 64) == 0 || ((int)w->y_wall_check_2 % 64) == 63))
		{
			if (w->x >= w->x_wall_check_2)
				return (0x0033CC); // bleu
			else
				return (0xFFCC33); // jaune
		}
	}
	else if (((int)w->y_wall_check_2 % 64) == 0 || ((int)w->y_wall_check_2 % 64) == 63) // idem y.
	{
		if (w->y >= w->y_wall_check_2)
			return (0x009933); // vert
		else
			return (0xCC0033); // rouge
	}
	return (check_next_color(w));
}

int check_prev_color(t_wolf *w)
{
	w->anglemin2 += 1.0;
	w->x_wall_check_2 = w->x;
	w->y_wall_check_2 = w->y;
	while (w->map[pos_tb(w->y_wall_check_2)][pos_tb(w->x_wall_check_2)] == 0)
	{
		w->x_wall_check_2 = w->x_wall_check_2 + cos((angle_check(w->anglemin2) / 180.0) * M_PI) * 1.0; // modifier pour changer aliasing. 
		w->y_wall_check_2 = w->y_wall_check_2 - sin((angle_check(w->anglemin2) / 180.0) * M_PI) * 1.0;
	}
		if (((int)w->x_wall_check_2 % 64) == 0 || ((int)w->x_wall_check_2 % 64) == 63 )  // verif x par rapport a la grille imaginaire de 64.
	{
		if (!(((int)w->y_wall_check_2 % 64) == 0 || ((int)w->y_wall_check_2 % 64) == 63))
		{
			if (w->x >= w->x_wall_check_2)
				return (0x0033CC); // bleu
			else
				return (0xFFCC33); // jaune
		}
	}
	else if (((int)w->y_wall_check_2 % 64) == 0 || ((int)w->y_wall_check_2 % 64) == 63) // idem y.
	{
		if (w->y >= w->y_wall_check_2)
			return (0x009933); // vert
		else
			return (0xCC0033); // rouge
	}
	return (check_prev_color(w));
}

int check_wall_color_modulo(t_wolf *w)
{
	double valx;
	double valy;

	valx = fabs(remainder(w->x_wall_check, 64.0));
	valy = fabs(remainder(w->y_wall_check, 64.0));

	//printf("modx %f, mody %f", valx, valy);
	if (valx > 0.01 && valy > 0.01)
	{
		if (valx <= valy)
		{
				if (w->x >= w->x_wall_check)
				{	
					printf("int dist %d, dist %f, modx %f, mody %f bleu\n", (int)w->dist, w->dist, valx, valy);
					return (0x0033CC); // bleu
				}
				else
				{
					printf("int dist %d, dist %f, modx %f, mody %f jaune\n",  (int)w->dist, w->dist, valx, valy);
					return (0xFFCC33); // jaune
				}
		}
		else if (valy <= valx)
		{
				if (w->y >= w->y_wall_check)
				{
					printf("int dist %d, dist %f, modx %f, mody %f vert\n",  (int)w->dist, w->dist, valx, valy);
					return (0x009933); // vert
				}
				else
				{
					printf("int dist %d, dist %f, modx %f, mody %f rouge\n", (int)w->dist, w->dist, valx, valy);
					return (0xCC0033); // rouge
				}
		}
	}
	return (w->prev_color_used);
}

int check_wall_color_simple(t_wolf *w) //determine couleur de maniere simple sans les coins.
{
//	if (((int)w->x_wall_check % 64) == 0 || ((int)w->x_wall_check % 64) == 63 )  // verif x par rapport a la grille imaginaire de 64.
//	{
	if (w->touch == 0)
	{
		if (w->touch == 0 && fabs((int)w->prev_dist - (int)w->dist) > 5)
			return (w->next_color);
		else
			return (w->prev_color_used);
	}
	if (w->touch == 1)//!(((int)w->y_wall_check % 64) == 0 || ((int)w->y_wall_check % 64) == 63))
	{
		if (w->x >= w->x_wall_check)
			return (0x0033CC); // bleu
		else
			return (0xFFCC33); // jaune
	}
//	}
	else if (w->touch == 2)//((int)w->y_wall_check % 64) == 0 || ((int)w->y_wall_check % 64) == 63) // idem y.
	{
		if (w->y >= w->y_wall_check)
			return (0x009933); // vert
		else
			return (0xCC0033); // rouge
	}
	return (0xFFFFFF);//w->prev_color_used);
}


/*int check_wall_color(t_wolf *w) // marche mal, a revoir.
{
	double valx;
	double valy;
		ft_putnbr((int)w->x_wall_check % 64);
		ft_putchar(' ');
	
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
	valx = fabs(remainder(w->x_wall_check, 64.0));
	valy = fabs(remainder(w->y_wall_check, 64.0));
	

	if ((valx < 1.0 && valy < 1.0))// && (valx > 0.01 && valy > 0.01))
	{
		printf("modx %f, mody %f\n", valx, valy);
		
		if(valx < valy)
		{
			if ((valy - valx) < 0.2)
			{
				if (w->x >= w->x_wall_check)
					return (0x0033CC); // bleu
				else
					return (0xFFCC33); // jaune
			}
		}
		else
		{
			if ((valx - valy) < 0.2)
			{
				if (w->y >= w->y_wall_check)
					return (0x009933); // vert
				else
					return (0xCC0033); // rouge
			}
		}
		//return (0xFFFFFFF);
	}
	//return (0xFFFFFFF);
	return (w->prev_color);
}*/


