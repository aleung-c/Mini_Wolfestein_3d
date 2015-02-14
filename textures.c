/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 16:30:04 by aleung-c          #+#    #+#             */
/*   Updated: 2015/02/14 16:42:52 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_txt_trace(t_wolf *w)
{
	int trace_iny;

	trace_iny = 0;
	while (trace_iny < w->trace_wall_size && w->trace_y < w->wolf_height)
	{
		if (w->touch == 1)
			ft_memcpy(&w->img[(w->trace_y * w->sizeline) +
				(w->x_screen * (w->bpp / 8))], &w->img_txt[((trace_iny) *
				w->sizeline) % 64 + (((int)w->x_wall_check / 64) *
				(w->bpp / 8))], sizeof(int));
		else if (w->touch == 2)
			ft_memcpy(&w->img[(w->trace_y * w->sizeline) + (w->x_screen *
			(w->bpp / 8))], &w->img_txt[((trace_iny) * w->sizeline) % 64
			+ (((int)w->y_wall_check / 64) * (w->bpp / 8))], sizeof(int));
		w->trace_y++;
		trace_iny++;
	}
}
