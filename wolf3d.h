/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/18 13:44:53 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/14 16:58:21 by aleung-c         ###   ########.fr       */
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

	int color; 
	int prev_color;
	int prev_color_used;
	int next_color;
	double dist2;
	int		touch;

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
	double			x_wall_check_2;
	double			y_wall_check_2;

	double 			dist;
	double 			prev_dist;
	double 			next_dist;

	double			anglemin2;
	// tracing

	int trace_y;
	int x_screen;
	int y_screen;
	//int trace_iny;

	// minimap
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

void				ft_upview_map(t_wolf *w);
void				ft_upview_map_vfield(t_wolf *w);
double				angle_check(double angle);
int					angle_rev(int angle);
void				fill_square(t_wolf *w, int x, int y, int color);

int pos_tb(double val);
int pos_tb_less1(double val);
void				ft_trace(t_wolf *w);
void				ft_sky_trace(t_wolf *w, double dist);
void				ft_wall_trace(t_wolf *w, double dist, int color);
void				ft_floor_trace(t_wolf *w);

//char *ft_line_trace(t_wolf *w, char *img, double dist);

char				*pixel_put_to_image(t_wolf *w, int x, int y, int color);
char				*pixel_put_to_image_minimap(t_wolf *w, int x, int y, int color);

int					color_less_dist(int color, int dist);
int 				check_wall_color_simple(t_wolf *w);
int check_wall_color_modulo(t_wolf *w);
int check_next_color(t_wolf *w);
int check_prev_color(t_wolf *w);

int is_corner(t_wolf* w);
void				init_view_angles(t_wolf *w);
void				ray_advances(t_wolf *w);

#endif
