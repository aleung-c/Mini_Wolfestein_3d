/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/03 16:34:02 by aleung-c          #+#    #+#             */
/*   Updated: 2015/02/12 16:32:37 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	angle_check(double angle)
{
	if (angle > 360.0)
		angle -= 360.0;
	if (angle < 0.0)
		angle += 360.0;
	return (angle);
}

int		angle_rev(int angle)
{
	int angle_rev;

	angle_rev = angle + 180.0;
	if (angle_rev > 360.0)
		angle_rev = angle_rev - 360.0;
	return (angle_rev);
}
