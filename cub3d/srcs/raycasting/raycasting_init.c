/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:18:56 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/01/02 19:22:05 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_width(char **map)
{
	int	i;
	int	width;
	int	current_width;

	if (!map)
		return (-1);
	i = 0;
	width = 0;
	while (map[i] != NULL)
	{
		current_width = ft_strlen(map[i]);
		if (current_width > width)
			width = current_width;
		i++;
	}
	return (width);
}

int	get_map_height(char **map)
{
	int	i;

	if (!map)
		return (-1);
	i = 0;
	while (map[i] != NULL)
		i++;
	return (i);
}

void	print_ray(t_ray *ray)
{
	if (!ray)
		return ;
	printf("!! Camera Width: %f\n", ray->cam.width);
	printf("!! Camera Height: %f\n", ray->cam.height);
	printf("!! Camera Half Width: %f\n", ray->cam.hwidth);
	printf("!! Camera Half Height: %f\n", ray->cam.h_height);
	printf("!! Camera FOV: %f\n", ray->cam.fov);
	printf("!! Camera Half FOV: %f\n", ray->cam.hfov);
	printf("!! Camera Position: x = %f, y = %f\n",
		ray->cam.pos.x, ray->cam.pos.y);
	printf("!! Camera Direction: dir_x = %f, dir_y = %f\n",
		ray->cam.dir.x, ray->cam.dir.y);
	printf("!! Camera Plane: plane_x = %f, plane_y = %f\n",
		ray->cam.plane.x, ray->cam.plane.y);
	printf("!! Map Width: %d\n", ray->cam.map_width);
	printf("!! Map Height: %d\n", ray->cam.map_height);
}

void	export_textures(void)
{
	t_texture	**texture;
	int i;

	texture = ft_game()->texture;
	i = -1;
	while (++i < TEXTURE_SIZE)
	{
		texture[i]->image_data = xpm_to_binary(texture[i]->image_path);
		if (texture[i]->image_data == NULL)
		{
			texture[i]->colour = get_colour(texture[i]->image_path);
			if (texture[i]->colour == -1)
				ft_print_error("File: Failed to load image or colour\n");
		}
	}
}

// TODO remove minus from camp.plane.x?
void	init_ray(t_game *game)
{
	t_ray	*ray;

	if (!game)
		return ;
	ray = &game->ray;
	ray->cam.fov = FOV;
	ray->cam.hfov = ray->cam.fov / 2;
	ray->cam.width = WIDTH;
	ray->cam.height = HEIGHT;
	ray->cam.pos.x = game->player.pos.x;
	ray->cam.pos.y = game->player.pos.y;
	ray->cam.dir.x = get_cosine(game->player.dir_angle);
	ray->cam.dir.y = -get_sine(game->player.dir_angle);
	ray->cam.width = WIDTH;
	ray->cam.height = HEIGHT;
	ray->cam.hwidth = ray->cam.width / 2;
	ray->cam.h_height = ray->cam.height / 2;
	ray->cam.map_width = get_map_width(game->map);
	ray->cam.map_height = get_map_height(game->map);
	print_ray(ray);
}
