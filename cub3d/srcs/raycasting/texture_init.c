/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:07:42 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/02 17:29:19 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_texture_info(t_texture *texture, int index)
{
	printf("\n=== TEXTURE[%d] ===\n", index);
	printf("Name: %s\n", texture->image_name);
	printf("Path: %s\n", texture->image_path);
	printf("Color: %d\n", texture->colour);
	if (texture->image_data)
	{
		printf("Image data exists\n");
		if (texture->image_data->img)
		{
			printf("Image loaded: Yes\n");
			printf("Dimensions: %dx%d\n",
				texture->image_data->width, texture->image_data->height);
			printf("Address: %p\n", texture->image_data->addr);
			printf("BPP: %d\n", texture->image_data->bpp);
			printf("Line Length: %d\n", texture->image_data->len_line);
			printf("Endian: %d\n", texture->image_data->endian);
		}
	}
	else
		printf("Image not loaded\n");
	printf("================\n");
}

static void	print_all_textures(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	printf("\nDEBUG: Texture Information\n");
	while (i < TEXTURE_SIZE)
	{
		if (game->texture[i])
			print_texture_info(game->texture[i], i);
		else
			printf("no texture[%d]\n", i);
		i++;
	}
	print_texture_info(game->door, TEXTURE_SIZE);
}

void	init_texture(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < WIDTH)
	{
		game->ray.walls[i].texture = NULL;
		i++;
	}
	game->door = (t_texture *)my_calloc(1, sizeof(t_texture));
	game->door->image_path = "./includes/textures/wall_tiles.xpm";
	game->door->image_name = "DOOR";
	game->door->image_data = xpm_to_binary(game->door->image_path);
	if (game->door->image_data == NULL)
	{
		game->door->colour = get_colour(game->door->image_path);
		if (game->door->colour == -1)
			ft_print_error("File: Failed to load image or colour\n");
	}
	print_all_textures(game);
	return ;
}
