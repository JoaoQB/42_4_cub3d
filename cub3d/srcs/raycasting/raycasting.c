/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:53:21 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/07 17:58:23 by jqueijo-         ###   ########.fr       */
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
	beta = ray_angle - ray->pov.direction_angle;
	if (horizontal_distance < vertical_distance)
		distance = horizontal_distance;
	else
		distance = vertical_distance;
	corrected_distance = distance * get_cosine(ray, (int)beta);
	return (corrected_distance);
}

double	raycasting(t_game *game, t_ray *ray)
{
	int		i;
	double	ray_angle;

	ray_angle = ray->pov.direction_angle - ray->half_fov;
	i = 0;
	while (i < WIDTH)
	{
		game->ray_distances[i] = cast_ray(game, ray, ray_angle);
		ray_angle += ray->ray_increment_angle;
		i++;
	}
	i = 0;
	while (i < WIDTH)
	{
		game->wall_heights[i] = game->ray_distances[i] * game->ray.height_calc;
		i++;
	}
	draw_walls(game);
	// For compiler
	return (-1);
}
