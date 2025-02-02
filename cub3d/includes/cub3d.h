/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:18:58 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/02 17:18:26 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include <stdint.h> // Define integer types, limits, macros
# include <stdlib.h> // Memory allocation
# include <stdio.h> // Standard input and output, perror function / Debugging
# include <math.h> // math functions, including fabs for modulus
# include <unistd.h> // System calls
# include <stdbool.h> // Booleans
# include <string.h> //TODO make my own string functions
# include <fcntl.h>
# include <unistd.h> // For close function
# include <linux/limits.h> //debug
# include <time.h> //debug
# include <errno.h> //debug

# define PI 3.14159265358979323846

# define WIDTH 800
# define HEIGHT 800
# define UNIT_SIZE 16
# define COLISION 0.2
# define FOV 60
# define MAX_ANGLE 360
# define SCALE 2
// From 0.1 slow to 1 fast
# define SPEED 0.1
# define TEXTURE_SIZE 6
# define COLOR 0xFF0000 // Red

// # define PLAYER_SPEED 100
// # define PLAYER_ROTATION 0.2
# define MINIMAP_SCALE 0.2

# define FLOOR_COLOR 0x404040 // Darker gray for floor
# define CEILING_COLOR 0xC0C0C0 // Lighter gray for ceiling
# define RED_COLOR 0xFF0000 // Red color
# define GREEN_COLOR 0x00FF00 // Green color
# define WHITE_COLOR 0xFFFFFF // White color
# define BLACK_COLOR 0x000000 // Black color
# define PINK_COLOR 0xFFC0CB // Pink color
# define YELLOW_COLOR 0xFFFF00 // Yellow color
# define BLUE_COLOR 0x0000FF // Blue color


typedef enum WALL_TEXTURE
{
	WALL_EAST,
	WALL_NORTH,
	WALL_WEST,
	WALL_SOUTH,
	WALL_UNKNOWN
}	t_wall_texture;

typedef enum DIRECTION
{
	EAST = 0,
	NORTH = 90,
	WEST = 180,
	SOUTH = 270,
	FLOOR = 360,
	CEIL = 450,
	UNKNOWN = 540
}	t_direction;

typedef enum KEY
{
	KEY_W = 119,
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
}	t_key;

typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct s_cam
{
	double	fov;
	double	hfov;
	double	width;
	double	height;
	double	hwidth;
	double	h_height;
	int		map_width;
	int		map_height;
	t_coord	pos;
	t_coord	dir;
	t_coord	plane;
}	t_cam;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len_line;
	int		endian;
//
	int		width;
	int		height;
}	t_image;

/*
** image_name: NO SO WE EA C F
** image_data: if path, extract to this format
** colour:	   if no path, try fill with colour
*/
typedef struct s_texture
{
	char	*image_name;
	char	*image_path;
	t_image	*image_data;
	int		colour;
}	t_texture;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_image	img;
}	t_mlx;

typedef struct s_wall
{
	double		ray_dist;
	int			dir;
	int			height;
	int			half_height;
	int			bottom;
	int			top;
	double		wall_x;
	int			tex_x;
	t_texture	*texture;
}	t_wall;

typedef struct s_ray
{
	int			id;
	int			hit;
	int			side;
	double		cam_x;
	t_coord		dir;
	t_coord		next;
	t_coord		delta;
	t_coord		step;
	int			grid_x;
	int			grid_y;
	t_wall		walls[WIDTH];
	t_cam		cam;
}	t_ray;

typedef struct s_player
{
	t_coord		pos;
	double		dir_angle;
	t_direction	angle;
}	t_player;

typedef struct s_control
{
	t_coord		move;
	int			mv_angle;
	t_coord		pos;
	int			dir;
}	t_control;

typedef struct s_game
{
	t_mlx		*mlx;
	t_player	player;
	t_control	ctl;
	t_ray		ray;
	t_texture	*texture[TEXTURE_SIZE]; // NO SO WE EA C F
	t_texture	*door;
	char		**map;
	int			map_width;
	int			map_height;
	int			update;
}	t_game;

/******************/
/******************/
/****** GAME ******/
/******************/
/******************/

/* main.c */
int			render(void);
t_game		*ft_game(void);

/* init.c */
void		init_game(char *file_path);

/* ft_free.c */
void		free_game(void);
void		free_map(char ***map_ptr);
void		free_mlx(t_mlx **mlx_ptr);

/******************/
/******************/
/*** RAYCASTING ***/
/******************/
/******************/

/* raycasting_init.c */
void		init_ray(t_game *game);
int			get_map_width(char **map);
int			get_map_height(char **map);

/* raycasting_trign_utils.c */
int			normalize_angle(int angle);
double		get_radiant(int ray_angle);
double		get_tangent(int ray_angle);
double		get_sine(int ray_angle);
double		get_cosine(int ray_angle);

/* raycasting.c */
void		raycasting(void);

/* raycasting_debug.c */
void		print_ray(t_ray *ray);
void		debug_start(t_ray *ray);
void		debug_aim(t_ray *ray);
void		debug_wall_info(t_ray *ray, t_wall *wall);
void		debug_cast(t_ray *ray);

/* raycasting_utils.c */
double		get_wall_distance(t_ray *ray);
int			get_wall_direction(t_ray *ray);
double		get_wall_x(t_ray *ray);
int			get_texture_x(t_ray *ray, t_wall *wall);

/* draw_utils.c */
void		draw_walls(t_game	*game);
void		draw_solid_line(int x, int start, int end, int color);
void		draw_text_line(t_game *game, t_wall *wall, t_image *data, int x);
void		my_pixel_put(t_image *img, int x, int y, int colour);

/* malloc tools */
void		*my_calloc(int num, int size);
char		*ft_strdup(char *str);
char		*ft_strnjoin(char *old_str, char *str_add, int size);
char		**ft_split(char *str, char c);

/* map generation*/
char		*file_to_str(char *file_name);
t_direction	get_direction_struct(const char *str);
void		extract_textures(char **lines);

/* map generation tools */
bool		is_valid(int y, int x, char *valid_str);
bool		validate_position(int y, int x);

/* str tools*/
bool		ft_isspaces(char c);
int			ft_atoi(const char *nptr);
int			ft_strlen(const char *str);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_strchr(char *s, int c);
int			ft_startswith(const char *s1, const char *s2);
int			ft_wordcount(const char *str, char c);
void		ft_putstr_fd(char *str, int fd);
char		*str_trim_and_free(char *str);

/* hash table*/
int			hash_find(int key);
void		hash_update(int key, bool value);

/* image read*/
t_image		*xpm_to_binary(char *image_path);
void		extract_map(t_game *game, char **lines);
void		check_map(char **map);
int			get_colour(const char *str);
t_texture	*extract_info_process(char **words);

/* error handle*/
void		ft_print_error(char *str);

/* testing*/
// void		print_map(char **double_array);
// void		init_test_player(void);
// void		init_test_textures(t_game *game);

/* controls mlx*/
int			handle_close(void *param);
int			handle_mouse(int button, int x, int y, void *param);
int			key_press(int key, void *param);
int			key_release(int key, void *param);
int			mouse_moved(int x, int y, void *param);
t_coord		get_coord(t_coord ref);
// int			player_moves(void);
void		door_switch(t_game *game);
t_direction	get_direction();

/* minimap */
void		draw_minimap(int offset_x, int offset_y);
void		draw_by_scale(int x, int y, int offset_x, int offset_y);

/* texture_init.c */
void		init_texture(t_game *game);
void		export_textures(void);

#endif
