/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:18:56 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/30 12:21:38 by jqueijo-         ###   ########.fr       */
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
	while(map[i] != NULL)
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
	while(map[i] != NULL)
		i++;
	return (i);
}

void	print_ray(t_ray *ray)
{
	if (!ray)
		return;
	printf("!! Camera Width: %f\n", ray->cam.width);
	printf("!! Camera Height: %f\n", ray->cam.height);
	printf("!! Camera Position: x = %f, y = %f\n", ray->cam.pos.x, ray->cam.pos.y);
	printf("!! Camera Direction: dir_x = %f, dir_y = %f\n", ray->cam.dir.x, ray->cam.dir.y);
	printf("!! Camera Plane: plane_x = %f, plane_y = %f\n", ray->cam.plane.x, ray->cam.plane.y);
	printf("!! Map Width: %d\n", ray->cam.mapWidth);
	printf("!! Map Height: %d\n", ray->cam.mapHeight);
}

void	init_ray(t_game *game)
{
	t_ray	*ray;

	if (!game)
		return ;
	ray = &game->ray;
	ray->cam.fov = FOV;
	ray->cam.hFov = ray->cam.fov / 2;
	ray->cam.width = WIDTH;
	ray->cam.height = HEIGHT;
	ray->cam.pos.x = game->player.pos.x;
	ray->cam.pos.y = game->player.pos.y;
	ray->cam.dir.x = get_cosine(game->player.dir_angle);
	ray->cam.dir.y = -get_sine(game->player.dir_angle);
	// remove minus?
	ray->cam.plane.x = -ray->cam.dir.y * get_tangent(ray->cam.hFov);
	ray->cam.plane.y = ray->cam.dir.x * get_tangent(ray->cam.hFov);
	ray->cam.width = WIDTH;
	ray->cam.height = HEIGHT;
	ray->cam.hWidth = ray->cam.width / 2;
	ray->cam.hHeight = ray->cam.height / 2;
	ray->cam.mapWidth = get_map_width(game->map);
	ray->cam.mapHeight = get_map_height(game->map);

	// print_ray(ray);
}
