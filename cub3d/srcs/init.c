/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:52:20 by fandre-b          #+#    #+#             */
/*   Updated: 2024/12/18 15:34:41 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** [0]    [0][1][2][3][4][5][6][7][8][9][10][11][12][13][14][15]
** [1]    [0][1][2][3][4][5][6][7][8][9][10][11][12][13][14][15]
** [2]    [0][1][2][3][4][5][6][7][8][9][10][11][12][13][14][15]
** [3]    [0][1][2][3][4][5][6]   [8][9][10][11][12][13][14][15]
** [4]    [0][1][2][3][4][5][6][7][8][9][10][11][12][13][14][15]
** [5]    [0][1][2][3][4][5][6][7][8][9][10][11][12][13][14][15]
**
*/


static char	**get_test_map()
{
	char	**map;

	map = malloc(sizeof(char *) * 8);
	map[0] = strdup("111111111111111");
	map[1] = strdup("100000111000011");
	map[2] = strdup("100000000010011");
	map[3] = strdup("100000000P10011");
	map[4] = strdup("100000000000011");
	map[5] = strdup("100000000000011");
	map[6] = strdup("111111111111111");
	map[7] = NULL;
	return (map);
}

// TODO init player from .cub file
static void	init_player(t_game *game)
{
	if (!game)
		return ;
	game->player.pos.x = 9;
	game->player.pos.y = 3;
	game->player.dir_angle = EAST;
	game->player.speed = 1;
	printf("!! Player initialized:\n");
	printf("!! Position: (%f, %f)\n", game->player.pos.x, game->player.pos.y);
	printf("!! Direction angle: %f\n", game->player.dir_angle);
	printf("!! Speed: %f\n", game->player.speed);
}

static t_mlx	*init_mlx()
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, \
	&mlx->img.len_line, &mlx->img.endian);
	if (!mlx->mlx || !mlx->img.img || !mlx->img.addr || !mlx->win)
	{
		free_mlx(&mlx);
		return (NULL);
	}
	return (mlx);
}

// TODO init map from .cub file
void	init_game()
{
	t_game	*game_s;

	game_s = ft_game();
	game_s->mlx = init_mlx();
	game_s->map = get_test_map();
	init_player(game_s);
	init_ray(game_s);
}
