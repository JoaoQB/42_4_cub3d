/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:49:36 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/03 21:00:12 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_mlx(t_mlx **mlx_ptr)
{
	t_mlx	*mlx;

	if (mlx_ptr && *mlx_ptr)
	{
		mlx = *mlx_ptr;
		if (mlx->img.img)
			mlx_destroy_image(mlx->mlx, mlx->img.img);
		mlx->img.img = NULL;
		if (mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		mlx->win = NULL;
		if (mlx->mlx)
			free(mlx->mlx);
		mlx->mlx = NULL;
		free(mlx);
		*mlx_ptr = NULL;
	}
}

// void	free_array(char **array_ptr)
// {

// }

void	free_frases(char **array_ptr)
{
	int		i;

	if (!array_ptr || !*array_ptr)
		return ;
	i = -1;
	while (array_ptr[++i])
	{
		free(array_ptr[i]);
		array_ptr[i] = NULL;
	}
	free(array_ptr[i]);
	free(array_ptr);
	array_ptr = NULL;
}

void	free_map(char ***map_ptr)
{
	char	**map;
	int		i;

	if (!map_ptr || !*map_ptr)
		return ;
	map = *map_ptr;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	*map_ptr = NULL;
}

void	free_game(void)
{
	t_game	*game_s;

	game_s = ft_game();
	if (game_s)
	{
		if (game_s->map)
			free_map(&game_s->map);
		if (game_s->mlx)
			free_mlx(&game_s->mlx);
	}
}
