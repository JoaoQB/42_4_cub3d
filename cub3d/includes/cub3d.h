/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:17:42 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/18 15:37:08 by jqueijo-         ###   ########.fr       */
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

# define WIDTH 800 //this will define the number of rays we cast
# define HEIGHT 800
# define FOV 60
# define MAX_ANGLE 360
# define SCALE 2
# define WALL_NORTH 0xFF0000  // Red for north-facing walls
# define WALL_SOUTH 0x00FF00  // Green for south-facing walls
# define WALL_EAST  0x0000FF  // Blue for east-facing walls
# define WALL_WEST  0xFFFF00  // Yellow for west-facing walls

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
}	t_coord;

typedef struct s_player
{
	t_coord	pos;
	double	speed;
	double	dir_angle;
}	t_player;

typedef struct s_cam
{
	double	fov;
	double	hFov;
	double	width;
	double	height;
	double	hWidth;
	double	hHeight;
	int		mapWidth;
	int		mapHeight;
	t_coord	pos;
	t_coord	dir;
	t_coord	plane;
} t_cam;

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

typedef struct s_trig
{
	double	radians[MAX_ANGLE];
	double	tangents[MAX_ANGLE];
	double	sines[MAX_ANGLE];
	double	cosines[MAX_ANGLE];
}	t_trig;

typedef struct s_ray
{
	int		id;
	int		hit;
	int		side;
	double	camX;
	double	rayDirX;
	double	rayDirY;
	int		gridX;
	int		gridY;
	double	rayNextX;
	double	rayNextY;
	double	rayInterX;
	double	rayInterY;
	int		stepX;
	int		stepY;
	double	ray_dist[WIDTH];
	double	wall_height[WIDTH];
	int		wall_dir[WIDTH];
	t_trig	trign;
	t_cam	cam;
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

/* utils.c */
int		ft_strlen(const char *str);

/******************/
/******************/
/*** RAYCASTING ***/
/******************/
/******************/

/* raycasting_init.c */
void	init_ray(t_game *game);
int		get_map_width(char **map);
int		get_map_height(char **map);
void	print_ray(t_ray *ray);
void	init_trigonometry(t_ray *ray);

/* raycasting_trign_utils.c */
int		normalize_angle(int angle);
double	get_radiant(int ray_angle);
double	get_tangent(int ray_angle);
double	get_sine(int ray_angle);
double	get_cosine(int ray_angle);


/* raycasting.c */
void	raycasting();

/* raycasting_utils.c */
double	get_wall_distance(t_ray *ray);
int		get_wall_direction(t_ray *ray);

/* draw_utils.c */
void	draw_walls(t_game	*game);
void	draw_vertical_line(t_game *game, int x, int wallTop, int wallBottom);
void	my_pixel_put(t_image *img, int x, int y, int colour);

#endif
