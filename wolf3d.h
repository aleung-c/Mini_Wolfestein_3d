/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/18 13:44:53 by aleung-c          #+#    #+#             */
/*   Updated: 2015/01/16 17:21:08 by aleung-c         ###   ########.fr       */
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
# define MMAP_WALL_SIZE 20 
# define MMAP_W 700
# define MMAP_H 600

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

	// dir change var
	int				up;
	int				down;
	int				left;
	int				right;

	// Defining coloring variables.

	int				color; 
	int				prev_color;
	int				prev_color_used;
	int				next_color;
	double			dist2;
	int				touch;

	//	Defining space view variables.

	int				wall_size;
	double			angle;
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

	int				trace_y;
	int				x_screen;
	int				y_screen;
	int				trace_sky_size;
	int				trace_wall_size;
	//int trace_iny;

	// minimap
	int				minimap_wall_size;
	int				minimap_width;
	int				minimap_height;
	void			*imgv_minimap;
	char			*img_minimap;
	int				bpp_minimap;
	int				sizeline_minimap;
	int				endian_minimap;
	int				charpos_x;
	int				charpos_y;

	// Defining screen.

	int				screen_width;
	int				screen_height;
	int 			wolf_width;
	int 			wolf_height;

	//	Map size.

	int	size_y;
	int	*size_l;
}						t_wolf;
/*
**	Function prototypes.
*/
char				*turn_space(char *line);
int					**ft_create_int_map(char *arg, t_wolf w);
char				***ft_create_char_map(char *arg, t_wolf w);
unsigned int		ft_count_values(char *str, int c);
int					ft_measure_map(char *arg, t_wolf *w);

void				ft_init_mlx(t_wolf *w);
int					expose_hook(t_wolf *w);

void				wolf_key_check(t_wolf *w);
int					key_press(int keycode, t_wolf *w);
int					key_release(int keycode, t_wolf *w);
void				ft_advance(t_wolf *w);
void				ft_backstep(t_wolf *w);

void				ft_upview_map(t_wolf *w);
void				ft_upview_map_vfield(t_wolf *w);
double				angle_check(double angle);
int					angle_rev(int angle);
void				fill_square(t_wolf *w, int x, int y, int color);
void				put_player_on_mmap(t_wolf *w);

int					pos_tb(double val);
int					pos_tb_less1(double val);
void				ft_trace(t_wolf *w);
void				ft_sky_trace(t_wolf *w);
void				ft_wall_trace(t_wolf *w, int color);
void				ft_floor_trace(t_wolf *w, int height);

//char *ft_line_trace(t_wolf *w, char *img, double dist);

char				*pixel_put_to_image(t_wolf *w, int x, int y, int color);
char				*pixel_put_to_image_minimap(t_wolf *w, int x, int y, int color);

int				init_check_nxt_color(t_wolf *w, int color);
int					color_less_dist(int color, int dist);
int 				check_wall_color_simple(t_wolf *w);
int					check_wall_color_modulo(t_wolf *w);
int					check_next_color(t_wolf *w);
int					check_prev_color(t_wolf *w);
int					check_side_color_x(t_wolf *w);
int					check_side_color_y(t_wolf *w);
int					check_ray_map_pos_xy(t_wolf *w, int dist_adv);
int check_ray_map_pos_x(t_wolf *w, int dist_adv);
int check_ray_map_pos_y(t_wolf *w, int dist_adv);
int					is_corner(t_wolf* w);
void				ray_advances(t_wolf *w);

#endif
