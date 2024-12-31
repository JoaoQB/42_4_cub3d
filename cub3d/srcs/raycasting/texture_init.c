/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:07:42 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/31 13:05:43 by jqueijo-         ###   ########.fr       */
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
}

void	init_texture(t_game *game)
{
	int	i;

	if (!game)
		return ;
	print_all_textures(game);
	i = 0;
	while (i < WIDTH)
	{
		game->ray.walls[i].texture = NULL;
		i++;
	}
	return ;
}
