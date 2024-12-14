/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:17:42 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/14 18:20:20 by fandre-b         ###   ########.fr       */
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
#include <fcntl.h>
#include <unistd.h> // For close function


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
# define PLAYER_SPEED 5
# define PLAYER_ROTATION 5
# define MINIMAP_SCALE 0.2
# define HASH_TABLE_SIZE 20

typedef enum Direction
{
	EAST = 0,
	NORTH = 90,
	WEST = 180,
	SOUTH = 270,
	FLOOR = 2,
	CEIL = 3,
	UNKNOWN = 1
} e_direction;

typedef enum KEY{
    KEY_W = 0,
    KEY_A = 97,
    KEY_S = 115,
    KEY_D = 100,
	KEY_UP = 65362,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_Q = 113,
	KEY_E = 101,
    KEY_ESC = 65307,
	// KEY_CTRL = 65507,
	// KEY_SHIFT = 65505,
	// KEY_TAB = 65289,
	// KEY_M = 109,
    // KEY_SPACE = 32,
} e_key;

typedef struct s_bucket
{
	int entry;
	void *content;
	struct s_bucket *next;
} t_bucket;

typedef struct s_hash_table
{
	t_bucket	**buckets;
	int size;
} t_hash_table;

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
	e_direction angle;
//
	// t_coord	dir;
}	t_player;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len_line;
	int		endian;
//
	int			width;
	int			height;
}	t_image;

typedef struct s_texture
{
	char	*image_name; //NO SO WE EA C F
	char	*image_path;
	t_image *image_data; //if path, extract to this format
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

typedef struct s_control
{
	t_hash_table *hash_table;
	t_coord move;
	int mv_angle;
	t_coord pos;
	int dir;
} t_control;

typedef struct s_game
{
	t_mlx		*mlx;
	t_player	player;
	//t_player	*player;
	t_control	ctl;
	t_ray		ray;
	t_texture	*texture[6]; // NO SO WE EA C F
	char		**map;
	int			map_width;
	int			map_height;
	int update;
}	t_game;

/******************/
/******************/
/****** GAME ******/
/******************/
/******************/

/* main.c */
t_game	*ft_game();

/* init.c */
void	init_game(char* file_path);

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
void	init_ray(void);

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
double	get_dist_square(t_pov player, t_coord intersection);
double	get_dist(t_pov player, t_coord delta, double ray_angle);

/* raycasting_vertical.c */
double	cast_ray_vertical(t_game *game, t_ray *ray, double ray_angle, int ray_id);

/* raycasting_horizontal.c */
double	cast_ray_horizontal(t_game *game, t_ray *ray, double ray_angle, int ray_id);

/* raycasting.c */
void	raycasting();

/* draw_utils.c */
void	draw_walls(t_game	*game);
void	my_pixel_put(t_image *img, int x, int y, int colour);

/* malloc tools */
void *my_calloc(int num, int size);
char *ft_strdup(char *str);
char	*ft_strnjoin(char *old_str, char *str_add, int size);
char **ft_split(char *str, char c);


/* map generation*/
char	*file_to_str(char *file_name);
e_direction get_direction_struct(const char *str);
void extract_textures(char **lines);

/* map generation tools */
bool is_valid(int y, int x, char *valid_str);
bool		validate_position(int y, int x);


/* str tools*/
bool ft_issapaces(char c);
int ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char* ft_strchr(char *s, int c);
int ft_startswith(const char *s1, const char *s2);
int	ft_wordcount(const char *str, char c);
void ft_putstr_fd(char *str, int fd);

/* hash table*/
t_hash_table *ft_hash_table(void);
int hash_find(int key);
void hash_update(int key, bool value);

/* image read*/
t_image*	xpm_to_binary(char *image_path);
void		extract_map(char **lines);
void	check_map(char **map);
int get_colour(const char *str);
t_texture *extract_info_process(char **words);

/* error handle*/
void	ft_print_error(char *str);
void print_map(char **double_array);

/* controls mlx*/
int	handle_close(void *param);
int	handle_mouse(int button, int x, int y, void *param);
int	key_press(int key, void *param);
int	key_release(int key, void *param);
int mouse_moved(int x, int y, void *param);
int player_moves(void);

/* minimap */
void	draw_minimap(int offset_x, int offset_y);
void draw_by_scale(int x, int y, int scale, int offset_x, int offset_y);

#endif
