/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:52:20 by fandre-b          #+#    #+#             */
/*   Updated: 2024/12/29 23:06:55 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO init player from .cub file
void	init_player(void)
{
	char	**map;

	if (!ft_game())
		return ;
	map = malloc(sizeof(char *) * 8);
	map[0] = strdup("111111111111111");
	map[1] = strdup("100000000000001");
	map[2] = strdup("110110000001011");
	map[3] = strdup("1110000P0000011");
	map[4] = strdup("110000000000011");
	map[5] = strdup("110000101000011");
	map[6] = strdup("111111111111111");
	map[7] = NULL;
	ft_game()->map = map;
	ft_game()->player.pos.x = 7;
	ft_game()->player.pos.y = 3;
	ft_game()->player.dir_angle = SOUTH;
	ft_game()->player.speed = 1;
	printf("!! Player initialized:\n");
	printf("!! Position: (%f, %f)\n", ft_game()->player.pos.x, ft_game()->player.pos.y);
	printf("!! Direction angle: %f\n", ft_game()->player.dir_angle);
	printf("!! Speed: %f\n", ft_game()->player.speed);
}

static void init_hash_table(void)
{
	ft_game()->ctl.hash_table = ft_hash_table();
	ft_hash_table()->size = HASH_TABLE_SIZE;
	ft_hash_table()->buckets = (t_bucket **) my_calloc(ft_hash_table()->size , sizeof(t_bucket *));
	// ft_bzero(ft_hash_table()->buckets, ft_hash_table()->size * sizeof(t_bucket *));
	// memset(ft_hash_table()->buckets, 0, ft_hash_table()->size * sizeof(t_bucket *));
}

void	init_mlx(void)
{
	t_mlx	*mlx;

	mlx = my_calloc(1, sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, \
	&mlx->img.len_line, &mlx->img.endian);
	if (!mlx->mlx || !mlx->img.img || !mlx->img.addr || !mlx->win)
	{
		free_mlx(&mlx);
		mlx = NULL;
	}
	ft_game()->mlx = mlx;
	return ;
}

// TODO init map from .cub file
//void	init_game()
//{
	//t_game	*game_s;

//	game_s = ft_game();
	//game_s->mlx = init_mlx();
	//game_s->map = get_test_map();
	//init_player(game_s);
	//init_ray(game_s);
//}

void	init_game(char* file_path)
{
	char **lines;
	char *file_str;

	// ft_game()->player = (t_player *) my_calloc(1, sizeof(t_player));
	// ft_game()->player.angle = UNKNOWN;
	init_mlx();
	if (ft_game()->update == 1)
		init_player();
	else if (ft_game()->update == 0)
	{
		file_str = file_to_str(file_path);
		lines = ft_split(file_str, '\n');
		extract_textures(lines);
		extract_map(lines);
		print_map (ft_game()->map);
		free(lines);
		ft_game()->player.dir_angle = ft_game()->player.angle;
	}
	init_hash_table();
	init_ray(ft_game());
	init_texture(ft_game());
}

t_texture *extract_info_process(char **words)
{
	t_texture *texture;

	texture = (t_texture *) my_calloc(1, sizeof(t_texture));
	texture->image_name = str_trim_and_free(ft_strdup(words[0]));
	texture->image_path = str_trim_and_free(ft_strdup(words[1]));
	texture->image_data = xpm_to_binary(texture->image_path);
	if (texture->image_data == NULL) // check for path existence and permissions
	{
		texture->colour = get_colour(words[1]);
		if (texture->colour == -1)
			ft_print_error("Failed to load image or colour\n");
	}
	return (texture);
}

int get_colour(const char *str)
{//TODO this one aint working
	// clour is passed as R,G,B
	//so i want con convert this into the int
	int colour;

	colour = 0; // 0xRRGGBB
	while (*str && ft_issapaces(*str))
		str++;

	return (colour);
}

t_image*	xpm_to_binary(char *image_path)
{
	t_image	*img;

	// Debug output
	printf("\n=== Texture Loading Debug ===\n");
	printf("Original path: %s\n", image_path);
	// MLX validation
	if (!ft_game() || !ft_game()->mlx || !ft_game()->mlx->mlx)
	{
		printf("Error: MLX not properly initialized\n");
		return NULL;
	}
	// File existence check
	if (access(image_path, F_OK | R_OK) == -1)
	{
		printf("File access error for '%s': %s\n", image_path, strerror(errno));
		return NULL;
	}
	printf("Debug: Loading texture from: %s\n", image_path);
	// MLX loading
	img = (t_image *)my_calloc(1, sizeof(t_image));
	if (!img)
	{
		printf("Memory allocation failed\n");
		return NULL;
	}
	img->img = mlx_xpm_file_to_image(ft_game()->mlx->mlx, image_path, &img->width, &img->height);
	if (!img->img)
	{
		printf("MLX XPM loading failed for: %s\n", image_path);
		free(img);
		return NULL;
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len_line, &img->endian);
	if (!img->addr)
	{
		printf("MLX get data address failed\n");
		mlx_destroy_image(ft_game()->mlx->mlx, img->img);
		free(img);
		return NULL;
	}
	return (img);
}


