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

void	color_plus_one(t_wolf *w)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (w->color[i] < 255)
			w->color[i] += 1;
		i++;
	}
}

void	color_less_one(t_wolf *w)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (w->color[i] > 0)
			w->color[i] -= 1;
		i++;
	}
}

void	color_less_dist(t_wolf *w, int dist)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (w->color[i] > 1)
			w->color[i] -= dist;
		if (w->color[i] < 0)
			w->color[i] = 0;
		i++;
	}
}

void	set_color(t_wolf *w, int r, int g, int b)
{
	w->color = (int *)malloc(sizeof(int) * 3);
	w->color[1] = r;
	w->color[2] = g;
	w->color[3] = b;
}
