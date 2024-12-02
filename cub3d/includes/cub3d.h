/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:17:42 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/01 17:52:31 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_h
#define CUB3d_H

# include "minilibx-linux/mlx.h"
# include <stdint.h> // Define integer types, limits, macros
# include <stdlib.h> // Memory allocation
# include <stdio.h> // Standard input and output, perror function / Debugging
# include <math.h> // math functions
# include <unistd.h> // System calls
#include <string.h> //TODO make my own string functions


#define PI 3.14159265358979323846
#define CHUNK_SIZE 16

#define FOV 120.0
# define WIDTH 800 //this will define the number of rays we cast
# define HEIGHT 800

enum Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST,
    FLOOR,
    UNKNOWN
};

struct s_coord
{
	double x;
	double y;
	//double z;
}	t_coord;

struct s_player
{
	t_coord pos;
	t_coord dir;
	double speed;
}	t_player;


typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bpp;
	int			len_line;
	int			endian;
}	t_image;


typedef struct s_texture
{
	char *image_name; //NO SO WE EA C F
	char *image_path;
	t_image image_data; //if path, extract to this format
	int colour; //if no path, try fill with colour
} t_texture;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_image		img;
}	t_mlx;

typedef struct s_game
{
	t_mlx		mlx;
	t_player	player;
	t_ray		ray[num_rays]; 
	t_texture	texture[6]; // NO SO WE EA C F
	char		**map;
} t_game;

typedef struct s_data
{
	char	*path_to_map;
	char	*path_to_textures;
	char	*player;
} t_data;

typedef struct s_ray
{
	t_coord		dir;
	t_coord		plane;
	t_coord		pos;
	t_coord		side_dist;
	t_coord		delta_dist;
	t_coord		step;
	double		perp_wall_dist;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
} t_ray;

#endif
