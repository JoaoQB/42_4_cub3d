/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:53:21 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/09 17:03:47 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	cast_ray(t_game *game, t_ray *ray, double ray_angle)
{
	double	horizontal_distance;
	double	vertical_distance;
	double	distance;
	double	beta;
	double	corrected_distance;

	horizontal_distance = cast_ray_horizontal(game, ray, ray_angle);
	vertical_distance = cast_ray_vertical(game, ray, ray_angle);
	beta = ray_angle - ray->pov.ang_dir;
	if (horizontal_distance < vertical_distance)
		distance = horizontal_distance;
	else
		distance = vertical_distance;
	corrected_distance = distance * get_cosine(ray, (int)beta);
	return (corrected_distance);
}

void	raycasting()
{
	t_game	*game;
	t_ray	*ray;
	int		i;
	double	ray_angle;

	game = ft_game();
	ray = &game->ray;
	ray_angle = ray->pov.ang_dir - ray->h_fov;
	i = 0;
	while (i < WIDTH)
	{
		ray->ray_dist[i] = cast_ray(game, ray, ray_angle);
		ray_angle += ray->ray_ang_inc;
		printf("ray angle: %f\n", ray_angle);
		i++;
	}
	i = 0;
	while (i < WIDTH)
	{
		ray->wall_height[i] = ray->ray_dist[i] * ray->height_calc;
		printf("wall_distance: %f\n", ray->ray_dist[i]);
		printf("wall_height: %f\n", ray->wall_height[i]);
		i++;
	}
	draw_walls(game);
}
