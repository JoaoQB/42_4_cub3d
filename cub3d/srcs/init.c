/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:18:50 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/31 13:28:22 by jqueijo-         ###   ########.fr       */
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
	printf("!! Position: (%f, %f)\n",
		ft_game()->player.pos.x, ft_game()->player.pos.y);
	printf("!! Direction angle: %f\n", ft_game()->player.dir_angle);
	printf("!! Speed: %f\n", ft_game()->player.speed);
}

// jqueijo: changed syntax for normi
static void	init_hash_table(void)
{
	t_hash_table	*table;

	table = ft_hash_table();
	if (!table)
		return ;
	ft_game()->ctl.hash_table = ft_hash_table();
	table->size = HASH_TABLE_SIZE;
	table->buckets = (t_bucket **)my_calloc(table->size, sizeof(t_bucket *));
	// ft_bzero(table->buckets, table->size * sizeof(t_bucket *));
	// memset(table->buckets, 0, table->size * sizeof(t_bucket *));
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

void	init_game(char *file_path)
{
	t_game	*game;
	char	**lines;
	char	*file_str;

	// ft_game()->player = (t_player *) my_calloc(1, sizeof(t_player));
	// ft_game()->player.angle = UNKNOWN;
	game = ft_game();
	init_mlx();
	if (game->update == 1)
		init_player();
	else if (game->update == 0)
	{
		file_str = file_to_str(file_path);
		lines = ft_split(file_str, '\n');
		extract_textures(lines);
		extract_map(game, lines);
		print_map (game->map);
		free(lines);
		game->player.dir_angle = game->player.angle;
	}
	init_hash_table();
	init_ray(game);
	init_texture(game);
}
