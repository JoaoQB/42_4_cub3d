/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:17:42 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/03 17:13:58 by jqueijo-         ###   ########.fr       */
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

# define FOV 60
# define UNIT_SIZE 16
# define MAX_ANGLE 360
# define WIDTH 800 //this will define the number of rays we cast
# define HEIGHT 800

typedef enum e_direction
{
	NORTH = 90,
	SOUTH = 270,
	EAST = 180,
	WEST = 0,
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
	t_coord	dir;
	double	speed;
	double	dir_angle;
}	t_player;

typedef struct s_trig
{
	double	radians[MAX_ANGLE];
	double	tangents[MAX_ANGLE];
	double	sines[MAX_ANGLE];
	double	cosines[MAX_ANGLE];
}	t_trig;

typedef struct s_pov
{
	double	pos_unit_x;
	double	pos_unit_y;
	double	direction_angle;
}	t_pov;

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

typedef struct s_ray
{
	double	half_fov;
	double	player_height;
	double	half_width;
	double	half_height;
	double	distance_to_projection;
	double	ray_increment_angle;
	double	map_width;
	double	map_height;
	t_pov	pov;
	t_trig	trign;
}	t_ray;

typedef struct s_game
{
	t_mlx		mlx;
	t_player	player;
	t_ray		ray;
	t_texture	texture[6]; // NO SO WE EA C F
	char		**map;
	double		ray_distances[WIDTH];
}	t_game;

typedef struct s_data
{
	char	*path_to_map;
	char	*path_to_textures;
	char	*player;
}	t_data;

/******************/
/******************/
/*** RAYCASTING ***/
/******************/
/******************/

/* raycasting_utils.c */
bool	is_ray_facing_right(double ray_angle);
bool	is_ray_facing_upwards(double ray_angle);

/* raycasting_math_utils.c */
double	get_radiant(t_ray *ray, int ray_angle);
double	get_tangent(t_ray *ray, int ray_angle);
double	get_sine(t_ray *ray, int ray_angle);
double	get_cosine(t_ray *ray, int ray_angle);

/* raycasting_init.c */
void	init_trigonometry(t_ray *ray);
t_ray	*init_ray(t_game *game);

/* raycasting_vertical.c */
double	cast_ray_vertical(t_game *game, t_ray *ray, double ray_angle);

/* raycasting_horizontal.c */
double	cast_ray_horizontal(t_game *game, t_ray *ray, double ray_angle);

/* raycasting.c */
double	raycasting(t_game *game, t_ray *ray);

#endif
