/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/03 16:43:08 by aleung-c          #+#    #+#             */
/*   Updated: 2015/02/12 14:52:02 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char *pixel_put_to_image(t_wolf *w, int x, int y, int color)
{
	ft_memcpy(&w->img[(y * w->sizeline) + (x * (w->bpp / 8))], &color, \
		sizeof(int));
	return (w->img);
}

char *pixel_put_to_image_minimap(t_wolf *w, int x, int y, int color)
{
	ft_memcpy(&w->img_minimap[(y * w->sizeline_minimap) + (x * \
		(w->bpp_minimap / 8))], &color, sizeof(int));
	return (w->img_minimap);
}
