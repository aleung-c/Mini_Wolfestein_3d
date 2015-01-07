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

int check_wall_color(t_wolf *w) // marche mal, a revoir.
{

	if ((w->map[((int)w->y_wall_check / 64)][((int)w->x_wall_check + 32) / 64] == 0) && \
	((w->map[((int)w->y_wall_check + 32) / 64][((int)w->x_wall_check) / 64] == 1) && \
	(w->map[((int)w->y_wall_check - 32) / 64][((int)w->x_wall_check) / 64] == 1)))  // check 32 px a droite
	{
		return (0xFFFF66); // bleu
	}
	/*else if (w->map[(int)w->y_wall_check / 64][((int)w->x_wall_check - 32) / 64] == 0) // check 32 px a gauche
	{
		return (0xFFFF66); // jaune
	}
	else if (w->map[((int)w->y_wall_check + 32) / 64][((int)w->x_wall_check / 64)] == 0) // check 32 px en bas
	{
		return (0x006600); // vert
	}
	else if (w->map[((int)w->y_wall_check - 32) / 64][((int)w->x_wall_check / 64)] == 0) // check 32 px en haut
	{
		return (0xCC0033); // rouge
	}*/
	return(0xFFFFFF);
	/*if (w->y_wall_check <= w->y && ((int)w->x_wall_check % 64) == 0) // Ouest ??
	{
		return (0xFFFF66); // jaune
	}
	else if (w->y_wall_check <= w->y && ((int)w->x_wall_check % 64) != 0) // sud ??
	{
		return (0x006600); // vert
	}
	else if (w->y_wall_check >= w->y && ((int)w->x_wall_check % 64) == 0) // est ??
	{
		return (0xFFFF66); // bleu
	}
	else if (w->y_wall_check >= w->y && ((int)w->x_wall_check % 64) != 0) // nord ??
	{
		return (0xCC0033); // rouge
	}
	return (0x00CCFF);*/
}