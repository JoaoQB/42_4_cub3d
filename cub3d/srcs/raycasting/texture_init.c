/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:07:42 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/05 10:39:12 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_textures(t_game *game)
{
	int	y;

	if (!game)
		return ;
	// print_all_textures(game);
	y = 0;
	while (y < TEXTURE_SIZE && game->texture[y] != NULL)
	{
		// printf("%d\n", y);
		// printf("Texture pointer: %p\n", (void *)game->texture[y]);
		y++;
	}
	// printf("Final y value: %d\n", y);
	if (y < 6)
	{
		// printf("Y: %d, TEXTURE_SIZE: %d\n", y, TEXTURE_SIZE);
		return (ft_print_error("File: Textures not loaded"));
	}
	if (!game->door || !game->door->image_data)
	{
		return (ft_print_error("File: Door texture not loaded"));
	}
}

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

void	print_all_textures(t_game *game)
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
	game->door->image_path = ft_strdup("./includes/textures/wall_tiles.xpm");
	game->door->image_name = ft_strdup("DOOR");
	game->door->image_data = xpm_to_binary(game->door->image_path);
	if (game->door->image_data == NULL)
	{
		game->door->colour = get_colour(game->door->image_path);
		if (game->door->colour == -1)
			ft_print_error("File: Failed to load image or colour\n");
	}
	return ;
}
