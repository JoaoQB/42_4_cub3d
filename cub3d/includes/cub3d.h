/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:17:42 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/08 15:18:27 by fandre-b         ###   ########.fr       */
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
#include <stdbool.h>
#include <fcntl.h> // For O_RDONLY


#define PI 3.14159265358979323846
#define CHUNK_SIZE 16

#define FOV 120.0
# define HEIGHT 800
# define WIDTH 800 //this will define the number of rays we cast
# define TILE_SIZE 64
# define PLAYER_SIZE 12
# define PLAYER_SPEED 5
# define PLAYER_ROTATION 5
# define WALL_HEIGHT 64
# define MINIMAP_SCALE 0.2

enum Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST,
    FLOOR,
	CEIL,
    UNKNOWN
};

typedef struct s_coord
{
	double x;
	double y;
	//double z;
}	t_coord;

typedef struct s_player
{
	t_coord pos;
	t_coord dir;
	double speed;
	enum Direction angle;
}	t_player;


typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bpp;
	int			len_line;
	int			endian;
	int			width;
	int			height;
}	t_image;


typedef struct s_texture
{
	char *image_name; //NO SO WE EA C F
	char *image_path;
	t_image *image_data; //if path, extract to this format
	int colour; //if no path, try fill with colour
} t_texture;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_image		img;
}	t_mlx;


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

typedef struct s_game
{
	t_mlx		*mlx;
	t_player	*player;
	t_ray		ray[800]; // 
	t_texture	texture[6]; // NO SO WE EA C F
	char		**map;
	int			map_width;
	int			map_height;
} t_game;

// typedef struct s_data
// {
// 	char	*path_to_map;
// 	char	*path_to_textures;
// 	char	*player;
// } t_data;

int main(int argc, char **argv);
t_game *ft_game(void);

t_image*	xpm_to_binary(char *image_path);
void	init_struct();
void	init_mlx();
void	my_pixel_put(t_image *img, int x, int y, int colour);
void	draw_minimap(int offset_x, int offset_y);
void draw_by_scale(int x, int y, int scale, int offset_x, int offset_y);
void *my_calloc(int num, int size);

enum Direction get_direction_struct(const char *str);
void get_player_direction(const char *str);
char *file_to_str(char *file_name);
void clear_empty_lines(char *file_str);
void remove_line(char *file_str);
void extract_images(char *file_str);
void		extract_map(char *file_str);
bool		check_map(char **map);
bool		validate_position(int y, int x);
bool is_valid(int x, int y, char *valid_str);

char **ft_split(char *str, char c);
char* ft_strchr(char *s, int c);
char	*ft_strcat(char *dest, const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int ft_strlen(const char *str);
char	*ft_strnjoin(char *old_str, char *str_add, int size);
int	ft_strcmp(const char *s1, const char *s2);
bool ft_issapaces(char c);

char *get_name(const char *str, int i);
char *get_path(const char *str, int i);
int get_colour(const char *str, int i);
int	ft_atoi(const char *nptr);



#endif
