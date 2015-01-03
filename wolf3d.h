/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/18 13:44:53 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/03 17:58:05 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "./libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <X11/X.h>

# define SCREEN_W 1450
# define SCREEN_H 600
# define WOLF_W 800
# define WOLF_H 600
# define WALL_SIZE 64

typedef struct			s_wolf
{
	//	Mlx starting variables.
	void			*mlx;
	void			*win;
	void			*imgv;
	char			*img;
	int				bpp;
	int				sizeline;
	int				endian;

	int				**map;

	//	Defining space positionning variables.
	int				x;
	int				y;

	int				x_back;
	int				y_back;

	// dir change var
	int up;
	int down;
	int left;
	int right;

	// Defining coloring variables.

	int *color; 

	//	Defining space view variables.

	int				wall_size;
	double			angle;
	double			angle_rev;
	int				x_seg;
	int				y_seg;
	double			angle_min;
	double			angle_max;

	double			angle_min_map;
	double			angle_max_map;
	double			x_wall_check;
	double			y_wall_check;
	
	void			*imgv_minimap;
	char			*img_minimap;
	int				bpp_minimap;
	int				sizeline_minimap;
	int				endian_minimap;

	// Defining screen.

	int				screen_width;
	int				screen_height;
	int 			wolf_width;
	int 			wolf_height;

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
void				color_plus_one(t_wolf *w);
void				color_less_one(t_wolf *w);
void				color_less_dist(t_wolf *w, int dist);
void				set_color(t_wolf *w, int r, int g, int b);
void				ft_upview_map(t_wolf *w);
void				ft_upview_map_vfield(t_wolf *w);
double				angle_check(double angle);
int					angle_rev(int angle);
char				*pixel_put_to_image(t_wolf *w, int x, int y);
char				*pixel_put_to_image_minimap(t_wolf *w, int x, int y);
void				init_view_angles(t_wolf *w);
void				ray_advances(t_wolf *w);

#endif
