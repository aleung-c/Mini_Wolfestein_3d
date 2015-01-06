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

char *pixel_put_to_image(t_wolf *w, int x, int y, int color)
{
	w->img[(y * w->sizeline) + (x * (w->bpp / 8))] = color & 0x0000FF;
	w->img[(y * w->sizeline) + (x * (w->bpp / 8)) + 1] = \
	(color & 0x00FF00) >> 8;
	w->img[(y * w->sizeline) + (x * (w->bpp / 8)) + 2] = \
	(color & 0xFF0000) >> 16;
	return (w->img);
}

char *pixel_put_to_image_minimap(t_wolf *w, int x, int y, int color)
{
	w->img_minimap[(y * w->sizeline_minimap) + \
	(x * (w->bpp_minimap / 8))] = color & 0x0000FF;
	w->img_minimap[(y * w->sizeline_minimap) + \
	(x * (w->bpp_minimap / 8)) + 1] = (color & 0x00FF00) >> 8;
	w->img_minimap[(y * w->sizeline_minimap) + \
	(x * (w->bpp_minimap / 8)) + 2] = (color & 0xFF0000) >> 16;
	return (w->img_minimap);
}