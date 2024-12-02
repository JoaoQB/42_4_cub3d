/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:53:21 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/02 20:16:26 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	get_radiant(double angle)
{
	double	radiant;

	radiant = angle * (PI / 180);
	return (radiant);
}

double	get_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

t_ray	*init_ray(t_game *game)
{
	t_ray	*new_ray;

	new_ray = malloc(sizeof(t_ray));
	if (!new_ray)
		return (NULL);
	new_ray->half_fov = FOV / 2;
	new_ray->player_height = BLOCK_SIZE / 2;
	new_ray->half_width = WIDTH / 2;
	new_ray->half_height = HEIGHT / 2;
	new_ray->distance_to_projection = new_ray->half_width / tan(get_radiant(new_ray->half_fov));
	new_ray->ray_increment_angle = FOV / WIDTH;
	new_ray->pov.direction_angle = NORTH;
	new_ray->pov.x = game->player.dir.x;
	new_ray->pov.y = game->player.dir.y;
	return (new_ray);
}

double	cast_ray(t_game *game, t_ray *ray, double ray_angle)
{
	double	ray_x;
	double	ray_y;
	int		map_x;
	int		map_y;
	double	dir_x;
	double	dir_y;

	dir_x = cos(get_radiant(ray_angle));
	dir_y = sin(get_radiant(ray_angle));
	ray_x = ray->pov.x;
	ray_y = ray->pov.y;
	while (1)
	{
		map_x = ray_x / BLOCK_SIZE;
		map_y = ray_y / BLOCK_SIZE;
		if (map_x < 0 || map_x >= WIDTH || map_y < 0 || map_y >= HEIGHT)
			return -1;
		if (game->map[map_y][map_x] == 1)
			return (get_distance(game->player.pos.x, game->player.pos.y, ray_x, ray_y));
		ray_x += dir_x;
		ray_y += dir_y;
	}
}

double	ray_casting(t_game *game, t_ray *ray)
{
	int		i;
	double	ray_angle;
	double	distance;

	ray_angle = ray->pov.direction_angle - 30;
	i = 0;
	while (i < WIDTH)
	{
		distance = cast_ray(game, ray, ray_angle);
		ray_angle += ray->ray_increment_angle;
		i++;
	}
}
