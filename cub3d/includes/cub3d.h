/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:18:58 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/06 14:40:44 by jqueijo-         ###   ########.fr       */
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

//math const
# define PI 3.14159265358979323846
# define MAX_ANGLE 360

// Map Size
# define WIDTH 800
# define HEIGHT 800
// Dimentions variables
# define UNIT_SIZE 16
# define TEXTURE_SIZE 6
// raycast variables
# define FOV 60
// Control variables
# define FADE_VALUE 0.5
# define COLISION 0.2 //0-0.5
# define MOVE_SPEED 0.10 //0-1
# define ROTATION_SPEED 1 //~2
# define SCALE 2
# define MINIMAP_SCALE 0.2

// Default Map Colors
# define FLOOR_COLOR 0x808080 // Darker gray for floor
# define CEILING_COLOR 0xC0C0C0 // Lighter gray for ceiling
// Colors
# define RED_COLOR 0xFF0000 // Red color
# define GREEN_COLOR 0x00FF00 // Green color
# define WHITE_COLOR 0xFFFFFF // White color
# define BLACK_COLOR 0x000000 // Black color
# define PINK_COLOR 0xFFC0CB // Pink color
# define YELLOW_COLOR 0xFFFF00 // Yellow color
# define BLUE_COLOR 0x0000FF // Blue color
# define CYAN_COLOR 0x00FFFF // Cyan color
# define BROWN_COLOR 0xA52A2A // Brown color
# define GREY_COLOR 0x808080 // Grey color

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

typedef struct s_control
{
	t_coord		pos;
	double		dir_angle; //
	int			dir;
	t_direction	angle;
	t_coord		move; //
	int			mv_angle; //
	double		mv_speed;
	double		rot_speed;
	double		fade;
	double		map_scale;
	// player speed
	// mouse speed
	// minimap zoom
	// minimap size ???
	// game darkness for fog/ambience/fading
}	t_control;

typedef struct s_game
{
	t_mlx		*mlx;
	t_control	ctl;
	t_ray		ray;
	t_texture	*texture[TEXTURE_SIZE]; // NO SO WE EA C F
	t_texture	*door;
	char		**map;
	//do i need this size they are in header also
	int			map_width;
	int			map_height;
	//i may ditch update
	int			update;
}	t_game;

// /******************/
// /******************/
// /****** GAME ******/
// /******************/
// /******************/

// /* main.c */
// int			render(void);
// t_game		*ft_game(void);

// /* init.c */
// void		init_game(char *file_path);

// /* ft_free.c */
// void		free_game(void);
// void		free_map(char ***map_ptr);
// void		free_mlx(t_mlx **mlx_ptr);

// /******************/
// /******************/
// /*** RAYCASTING ***/
// /******************/
// /******************/

// /* raycasting_init.c */
// void		init_ray(t_game *game);
// int			get_map_width(char **map);
// int			get_map_height(char **map);

// /* raycasting_trign_utils.c */
// int			normalize_angle(int angle);
// double		get_radiant(int ray_angle);
// double		get_tangent(int ray_angle);
// double		get_sine(int ray_angle);
// double		get_cosine(int ray_angle);

// /* raycasting.c */
// void		cast_ray(t_game*game, t_ray *ray, char *str_block);
// void		raycasting(void);

// /* raycasting_debug.c */
// void		print_ray(t_ray *ray);
// void		debug_start(t_ray *ray);
// void		debug_aim(t_ray *ray);
// void		debug_wall_info(t_ray *ray, t_wall *wall);
// void		debug_cast(t_ray *ray);

// /* raycasting_utils.c */
// bool		is_out_of_bounds(int x, int y);
// double		get_wall_distance(t_ray *ray);
// int			get_wall_direction(t_ray *ray);
// double		get_wall_x(t_ray *ray);
// int			get_texture_x(t_ray *ray, t_wall *wall);

// /* draw_utils.c */
// void		draw_walls(t_game	*game);
// void		draw_solid_line(int x, int start, int end, int color);
// void		draw_text_line(t_game *game, t_wall *wall, t_image *data, int x);
// void		my_pixel_put(t_image *img, int x, int y, int colour);

// /* malloc tools */
// void		*my_calloc(int num, int size);
// char		*ft_strdup(char *str);
// char		*ft_strnjoin(char *old_str, char *str_add, int size);
// char		**ft_split(char *str, char c);

// /* map generation*/
// char		*file_to_str(char *file_name);
// t_direction	get_direction_struct(const char *str);
// void		extract_textures(char **lines);

// /* map generation tools */
// bool		is_valid(int y, int x, char *valid_str);
// bool		validate_position(int y, int x);

// /* str tools*/
// bool		ft_isspaces(char c);
// int			ft_atoi(const char *nptr);
// int			ft_strlen(const char *str);
// size_t		ft_strlcpy(char *dest, const char *src, size_t size);
// char		*ft_strchr(char *s, int c);
// int			ft_startswith(const char *s1, const char *s2);
// int			ft_wordcount(const char *str, char c);
// void		ft_putstr_fd(char *str, int fd);
// char		*str_trim_and_free(char *str);

// /* hash table*/
// int			hash_find(int key);
// void		hash_update(int key, bool value);

// /* image read*/
// t_image		*xpm_to_binary(char *image_path);
// void		extract_map(t_game *game, char **lines);
// void		check_map(char **map);
// int			get_colour(const char *str);
// t_texture	*extract_info_process(char **words);

// /* error handle*/
// void		ft_print_error(char *str);

// /* testing*/
// void		print_map(char **double_array);
// void		print_all_textures(t_game *game);
// // void		init_test_player(void);
// // void		init_test_textures(t_game *game);

// /* controls mlx*/
// int			handle_close(void *param);
// int			handle_mouse(int button, int x, int y, void *param);
// int			key_press(int key, void *param);
// int			key_release(int key, void *param);
// int			mouse_moved(int x, int y, void *param);
// t_coord		get_coord(t_coord ref);
// void		door_switch(t_game *game);
// void		check_doors(t_game *game, char **map);

// /* minimap */
// void		draw_minimap(int offset_x, int offset_y);

// /* texture_init.c */
// void		check_textures(t_game *game);
// void		init_texture(t_game *game);
// void		export_textures(void);
// void		free_frases(char **array_ptr);

////// MLX = USER Interface //////

int			handle_mouse(int button, int x, int y, void *param);
int			handle_close(void *param);
int			key_press(int key, void *param);
int			key_release(int key, void *param);

////// GAME CONTROLS ////// DONE?

int			mouse_moved(int x, int y, void *param);
void		player_walk(void);
int			render(void);

////// MLX UTILS ////// DONE

void		my_pixel_put(t_image *img, int x, int y, int colour);
int			get_colour(const char *str);
t_image		*xpm_to_binary(char *image_path);

////// Drawing ////// DONE

void		draw_minimap(int offset_x, int offset_y);
void		draw_solid_line(int x, int start, int end, int color);
void		draw_text_line(t_game *game, t_wall *wall, t_image *data, int x);
void		draw_walls(t_game *game);

///----------------------------------------------

//////// PARSING //////// DONE

void		extract_map(t_game *game, char **lines);
void		extract_textures(char **lines);
t_texture	*extract_info_process(char **words);

////// PARSING CHECKS ////// DONE

bool		validate_position(int y, int x);
void		check_map(char **map);
void		check_textures(t_game *game);

//DOORS
void		door_switch(t_game *game);
bool		is_door_valid(char **map, int y, int x);
void		check_doors(t_game *game, char **map);

////// PARSING UTILS ////// DONE

char		*file_to_str(char *file_name);
t_direction	get_direction_struct(const char *str);
bool		get_player_direction(int y, int x);
void		export_textures(t_texture	*texture);

t_coord		get_coord(t_coord ref);

//----------------------------------------------

////// RAYCASTING ////// DONE

// static void	start_ray(t_ray *ray, int ray_id);
// static void	aim_ray(t_ray *ray);
void		cast_ray(t_game*game, t_ray *ray, char *str_block);
void		calculate_wall_info(t_game *game, t_ray *ray);
void		raycasting(void);

////// RAYCASTING UTILS ////// DONE

double		get_wall_distance(t_ray *ray);
int			get_wall_direction(t_ray *ray);
double		get_wall_x(t_ray *ray);
int			get_texture_x(t_ray *ray, t_wall *wall);

////// FREE ////// DONE

void		free_texture(t_texture *texture);
void		free_map(char ***map_ptr);
void		free_mlx(t_mlx **mlx_ptr);
void		free_frases(char **array_ptr);
void		free_game(void);

//////// INIT //////// DONE

void		init_mlx(void);
void		init_parsing(char *file_path);
void		init_control(void);
void		init_ray(t_game *game);
void		init_texture(t_game *game);

////// STRUCTS ////// DONE

t_game		*ft_game(void);
void		init_game(char *file_path);
int			main(int argc, char **argv);

////// UTILS //////

int			ft_strlen(const char *str);
char		*ft_strcat(char *dest, const char *src);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_strchr(char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*str_trim_and_free(char *str);
int			ft_startswith(const char *s1, const char *s2);

//////// MEMORY ////////

void		*my_calloc(int num, int size);
char		*ft_strdup(char *str);
char		*ft_strnjoin(char *old_str, char *str_add, int size);
char		**ft_split(char *str, char c);

//////// MATH ////////

int			normalize_angle(int angle);
double		get_radiant(int ray_angle);
double		get_cosine(int ray_angle);
double		get_sine(int ray_angle);
double		get_tangent(int ray_angle);

int			ft_atoi(const char *nptr);

bool		ft_isspaces(char c);
int			ft_wordcount(const char *str, char c);

////// Game UTILS //////

void		ft_putstr_fd(char *str, int fd);
void		ft_print_error(char *str);
bool		is_out_of_bounds(int x, int y);
bool		is_valid(int y, int x, char *valid_str);

////// DEBUG ////// DONE

void		print_ray(t_ray *ray);
void		debug_start(t_ray *ray);
void		debug_aim(t_ray *ray);
void		debug_wall_info(t_ray *ray, t_wall *wall);
void		debug_cast(t_ray *ray);
void		print_texture_info(t_texture *texture, int index);
void		print_all_textures(t_game *game);
void		print_map(char **double_array);

#endif
