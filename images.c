/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/03 16:43:08 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/03 16:44:49 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char *pixel_put_to_image(t_wolf *w, int x, int y)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	r = w->color[1];
	g = w->color[2];
	b = w->color[3];

	w->img[(y * w->sizeline) + (x * (w->bpp / 8))] = b;
	w->img[(y * w->sizeline) + (x * (w->bpp / 8)) + 1] = g;
	w->img[(y * w->sizeline) + (x * (w->bpp / 8)) + 2] = r;
	return (w->img);
}

char *pixel_put_to_image_minimap(t_wolf *w, int x, int y)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	r = w->color[1];
	g = w->color[2];
	b = w->color[3];

	w->img_minimap[(y * w->sizeline_minimap) + (x * (w->bpp_minimap / 8))] = b;
	w->img_minimap[(y * w->sizeline_minimap) + (x * (w->bpp_minimap / 8)) + 1] = g;
	w->img_minimap[(y * w->sizeline_minimap) + (x * (w->bpp_minimap / 8)) + 2] = r;
	return (w->img_minimap);
}
