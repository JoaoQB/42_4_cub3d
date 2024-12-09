/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:53:21 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/09 23:14:35 by jqueijo-         ###   ########.fr       */
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

	printf("Casting ray:\n");
	printf("ray_angle: %f\n", ray_angle);
	printf("pov.ang_dir: %f\n", ray->pov.ang_dir);
	horizontal_distance = cast_ray_horizontal(game, ray, ray_angle);
	vertical_distance = cast_ray_vertical(game, ray, ray_angle);
	printf("horizontal_distance: %f\n", horizontal_distance);
	printf("vertical_distance: %f\n", vertical_distance);
	beta = ray_angle - ray->pov.ang_dir;
	printf("beta: %f\n", beta);
    if (horizontal_distance == -1)
        distance = vertical_distance;
	else if (vertical_distance == -1)
		distance = horizontal_distance;
	else if (horizontal_distance < vertical_distance)
		distance = horizontal_distance;
	else
		distance = vertical_distance;
	corrected_distance = distance * get_cosine(ray, (int)beta);
	printf("corrected_distance: %f\n", corrected_distance);
	printf("ray_angle: %f, pov.ang_dir: %f, horizontal_distance: %f, vertical_distance: %f, corrected_distance: %f\n",
		ray_angle, ray->pov.ang_dir, horizontal_distance, vertical_distance, corrected_distance);
	return (corrected_distance);
}

void	raycasting()
{
	t_game	*game;
	t_ray	*ray;
	int		i;
	double	ray_angle;
	double	height;
	double	distance;

	game = ft_game();
	ray = &game->ray;
	ray_angle = ray->pov.ang_dir - ray->h_fov;
	distance = cast_ray(game, ray, ray_angle);
	height = distance * ray->height_calc;
	printf("Final distance: %f\n", distance);
	printf("wall_height: %f\n", height);
	i = 0;
	while (i < WIDTH)
	{
		ray->ray_dist[i] = cast_ray(game, ray, ray_angle);
		ray->wall_height[i] = ray->ray_dist[i] * ray->height_calc;
		printf("wall_height: %f\n", ray->wall_height[i]);
		ray_angle += ray->ray_ang_inc;
		i++;
	}
	draw_walls(game);
}
