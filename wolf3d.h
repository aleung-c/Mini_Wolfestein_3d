/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/18 13:44:53 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/02 17:47:52 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "./libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <X11/X.h>

typedef struct			s_wolf
{
	//	Mlx starting variables.
	void			*mlx;
	void			*win;
	void			*imgv;
	char *img;
	int bpp;
	int sizeline;
	int endian;

	int				**map;

	//	Defining space positionning variables.
	int				x;
	int				y;

	int				x_back;
	int				y_back;

	//	Defining space view variables.

	double			angle;
	double			angle_rev;
	int				x_seg;
	int				y_seg;
	double			angle_min;
	double			angle_max;
	double			x_wall_check;
	double			y_wall_check;

	// Defining screen.

	int				screen_width;
	int				screen_height;

	//	Map size.

	unsigned int	size_y;
	unsigned int	*size_l;
}						t_wolf;
/*
**	Function prototypes.
*/
char				*turn_space(char *line);
int					**ft_create_int_map(char *arg, t_wolf w);
char				***ft_create_char_map(char *arg, t_wolf w);
unsigned int		ft_count_values(char *str, int c);
int					ft_measure_map(char *arg, t_wolf *w);

#endif
