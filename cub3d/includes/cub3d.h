/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:17:42 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/12 17:42:24 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "minilibx-linux/mlx.h"
# include <stdint.h> // Define integer types, limits, macros
# include <stdlib.h> // Memory allocation
# include <stdio.h> // Standard input and output, perror function / Debugging
# include <math.h> // math functions
# include <unistd.h> // System calls
# include <stdbool.h> // Booleans
# include <string.h> //TODO make my own string functions


# define PI 3.14159265358979323846
# define ANGLE_TOLERANCE 0.001

# define WIDTH 800 //this will define the number of rays we cast
# define HEIGHT 800
# define UNIT_SIZE 16
# define FOV 60
# define MAX_ANGLE 360
# define WALL_COLOR 0xFFFFFF  // White
# define FLOOR_COLOR 0x404040   // Darker gray for floor
# define CEILING_COLOR 0xC0C0C0 // Lighter gray for ceiling

typedef enum e_direction
{
	NORTH = 90,
	SOUTH = 270,
	EAST = 0,
	WEST = 180,
	FLOOR,
	UNKNOWN
}	t_direction;

typedef struct s_coord
{
	double	x;
	double	y;
	//double z;
}	t_coord;

typedef struct s_player
{
	t_coord	pos;
	double	speed;
	double	dir_angle;
	// t_coord	dir;
}	t_player;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len_line;
	int		endian;
}	t_image;

typedef struct s_texture
{
	char	*image_name; //NO SO WE EA C F
	char	*image_path;
	t_image	image_data; //if path, extract to this format
	int		colour; //if no path, try fill with colour
}	t_texture;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_image		img;
}	t_mlx;

/*
** pos_ux  = position unit x
** pos_uy  = position unit y
** ang_dir = angle direction
*/

typedef struct s_pov
{
	double	pos_ux;
	double	pos_uy;
	double	ang_dir;
}	t_pov;

typedef struct s_trig
{
	double	radians[MAX_ANGLE];
	double	tangents[MAX_ANGLE];
	double	sines[MAX_ANGLE];
	double	cosines[MAX_ANGLE];
}	t_trig;

/*
** h_fov       = half field of view
** p_height    = player height
** h_width     = half height
** h_height    = half height
** d_proj      = distance to projection
** height_calc = height calculator
** ray_ang_inc   = ray increment angle
** m_width     = map width
** m_height    = map height
** ray_dist    = ray distances
** wall_height = wall heights
*/
typedef struct s_ray
{
	double	h_width;
	double	h_height;
	double	fov;
	double	h_fov;
	double	p_height;
	double	d_proj;
	double	ray_ang_inc;
	double	height_calc;
	int		m_width;
	int		m_height;
	double	ray_dist[WIDTH];
	double	wall_height[WIDTH];
	t_trig	trign;
	t_pov	pov;
}	t_ray;

typedef struct s_game
{
	t_mlx		*mlx;
	t_player	player;
	t_ray		ray;
	t_texture	texture[6]; // NO SO WE EA C F
	char		**map;
}	t_game;

typedef struct s_data
{
	char	*path_to_map;
	char	*path_to_textures;
	char	*player;
}	t_data;

/******************/
/******************/
/****** GAME ******/
/******************/
/******************/

/* main.c */
t_game	*ft_game();

/* init.c */
void	init_game();

/* ft_free.c */
void	free_game();
void	free_map(char ***map_ptr);
void	free_mlx(t_mlx **mlx_ptr);

/******************/
/******************/
/*** RAYCASTING ***/
/******************/
/******************/

/* raycasting_init.c */
void	init_ray(t_game *game);

/* raycasting_utils.c */
bool	is_ray_cardinal(double ray_angle);
bool	is_ray_horizontal(double ray_angle);
bool	is_ray_vertical(double ray_angle);
bool	is_ray_facing_right(double ray_angle);
bool	is_ray_facing_upwards(double ray_angle);

/* raycasting_trign_utils.c */
int		normalize_angle(int angle);
double	get_radiant(int ray_angle);
double	get_tangent(int ray_angle);
double	get_sine(int ray_angle);
double	get_cosine(int ray_angle);

/* raycasting_math_utils.c */
double	get_vert_dist(double pos_ux, double inter_x, double ray_angle);
double	get_horiz_dist(double pos_ux, double inter_x, double ray_angle);

/* raycasting_vertical.c */
double	cast_ray_vertical(t_game *game, t_ray *ray, double ray_angle, int ray_id);

/* raycasting_horizontal.c */
double	cast_ray_horizontal(t_game *game, t_ray *ray, double ray_angle, int ray_id);

/* raycasting.c */
void	raycasting();

/* draw_utils.c */
void	draw_walls(t_game	*game);
void	my_pixel_put(t_image *img, int x, int y, int colour);

#endif
