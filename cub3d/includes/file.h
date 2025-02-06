
////// MLX = USER Interface //////

int	handle_mouse(int button, int x, int y, void *param);
int	handle_close(void *param);
int	key_press(int key, void *param);
int	key_release(int key, void *param);

////// GAME CONTROLS ////// DONE?

int	mouse_moved(int x, int y, void *param);
void	player_walk(void);
int	render(void);

////// MLX UTILS ////// DONE

void	my_pixel_put(t_image *img, int x, int y, int colour);
int	get_colour(const char *str);
t_image	*xpm_to_binary(char *image_path);

////// Drawing ////// DONE

void	draw_minimap(int offset_x, int offset_y);
void	draw_solid_line(int x, int start, int end, int color);
void	draw_text_line(t_game *game, t_wall *wall, t_image *data, int x);
void	draw_walls(t_game *game);

///----------------------------------------------

//////// PARSING //////// DONE

void	extract_map(t_game *game, char **lines);
void	extract_textures(char **lines);
t_texture	*extract_info_process(char **words);

////// PARSING CHECKS ////// DONE

bool	validate_position(int y, int x);
void	check_map(char **map);
void	check_textures(t_game *game);

//DOORS
void	door_switch(t_game *game);
static bool	is_door_valid(char **map, int y, int x);
void	check_doors(t_game *game, char **map);

////// PARSING UTILS ////// DONE

char	*file_to_str(char *file_name);
t_direction	get_direction_struct(const char *str);
bool	get_player_direction(int y, int x);
void	export_textures(t_texture	*texture);

t_coord	get_coord(t_coord ref);

//----------------------------------------------

////// RAYCASTING ////// DONE

// static void	start_ray(t_ray *ray, int ray_id);
// static void	aim_ray(t_ray *ray);
void	cast_ray(t_game*game, t_ray *ray, char *str_block);
static void	calculate_wall_info(t_game *game, t_ray *ray);
void	raycasting(void);

////// RAYCASTING UTILS ////// DONE

double	get_wall_distance(t_ray *ray);
int	get_wall_direction(t_ray *ray);
double	get_wall_x(t_ray *ray);
int	get_texture_x(t_ray *ray, t_wall *wall);

////// FREE ////// DONE

void	free_texture(t_texture *texture);
void	free_map(char ***map_ptr);
void	free_mlx(t_mlx **mlx_ptr);
void	free_frases(char **array_ptr);
void	free_game(void);

//////// INIT //////// DONE

void	init_mlx(void);
void	init_parsing(char *file_path);
void	init_control(void);
void	init_ray(t_game *game);
void	init_texture(t_game *game);

////// STRUCTS ////// DONE

t_game	*ft_game(void);
void	init_game(char *file_path);
int	main(int argc, char **argv);


////// UTILS //////

int	ft_strlen(const char *str);
char	*ft_strcat(char *dest, const char *src);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strchr(char *s, int c);
int	ft_strcmp(const char *s1, const char *s2);
char	*str_trim_and_free(char *str);
int	ft_startswith(const char *s1, const char *s2);

//////// MEMORY ////////

void	*my_calloc(int num, int size);
char	*ft_strdup(char *str);
char	*ft_strnjoin(char *old_str, char *str_add, int size);
char	**ft_split(char *str, char c);

//////// MATH ////////

int	normalize_angle(int angle);
double	get_radiant(int ray_angle);
double	get_cosine(int ray_angle);
double	get_sine(int ray_angle);
double	get_tangent(int ray_angle);

int	ft_atoi(const char *nptr);

bool	ft_isspaces(char c);
int	ft_wordcount(const char *str, char c);

////// Game UTILS //////

void	ft_putstr_fd(char *str, int fd);
void	ft_print_error(char *str);
bool	is_out_of_bounds(int x, int y);
bool	is_valid(int y, int x, char *valid_str);


////// DEBUG ////// DONE

void	print_ray(t_ray *ray);
void	debug_start(t_ray *ray);
void	debug_aim(t_ray *ray);
void	debug_wall_info(t_ray *ray, t_wall *wall);
void	debug_cast(t_ray *ray);
static void	print_texture_info(t_texture *texture, int index);
void	print_all_textures(t_game *game);
void	print_map(char **double_array);

//DO I NEED THESE?
// int	get_map_width(char **map);
// int	get_map_height(char **map);

