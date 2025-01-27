/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:18:50 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/01/02 20:11:33 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// jqueijo: changed syntax for normi
static void	init_hash_table(void)
{
	t_hashtable	*table;

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

	printf("Parsing file: %s\n", file_path);
	file_str = file_to_str(file_path);
	lines = ft_split(file_str, '\n');
	extract_textures(lines);
	extract_map(game, lines);
	check_map(game->map);
	// print_map (game->map);
	free(lines);
	game->player.dir_angle = game->player.angle;
	init_hash_table(); //TODO remove
	init_ray(game);
	init_texture(game);
}
