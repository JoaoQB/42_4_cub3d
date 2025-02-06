/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:49:36 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/06 15:33:08 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_texture(t_texture *texture)
{
	if (!texture)
		return ;
	if (texture->image_name)
		free(texture->image_name);
	if (texture->image_path)
		free(texture->image_path);
	if (texture->image_data)
	{
		if (texture->image_data->img)
		{
			mlx_destroy_image(ft_game()->mlx->mlx, texture->image_data->img);
			texture->image_data->img = NULL;
		}
		free(texture->image_data);
		texture->image_data = NULL;
	}
	free(texture);
}

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
			mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		mlx->mlx = NULL;
		free(mlx);
		*mlx_ptr = NULL;
	}
}

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
	int		i;
	t_game	*game_s;

	game_s = ft_game();
	if (game_s)
	{
		if (game_s->map)
			free_map(&game_s->map);
		if (game_s->door)
		{
			free_texture(game_s->door);
			game_s->door = NULL;
		}
		i = -1;
		while (game_s->texture[++i] != NULL && i < TEXTURE_SIZE)
		{
			if (game_s->texture[i])
			{
				free_texture(game_s->texture[i]);
				game_s->texture[i] = NULL;
			}
		}
		if (game_s->mlx)
			free_mlx(&game_s->mlx);
	}
}
