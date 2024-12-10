/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:53:21 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/10 21:43:45 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	normalise_ray_angle(double ray_angle)
{
	printf("normalise_ray_angle: input ray_angle = %f\n", ray_angle);
	ray_angle = fmod(ray_angle, MAX_ANGLE); // Wrap angle to (-MAX_ANGLE, MAX_ANGLE)
	if (ray_angle < 0)
		ray_angle += MAX_ANGLE; // Ensure angle is non-negative
	printf("normalise_ray_angle: normalized ray_angle = %f\n", ray_angle);
	return ray_angle;
}

static double	cast_ray(t_game *game, t_ray *ray, double ray_angle, int ray_id)
{
	double	horizontal_distance;
	double	vertical_distance;
	double	distance;
	double	beta;
	double	corrected_distance;

	printf("ray_id_%d, ray_angle: %f, pov.ang_dir: %f\n", ray_id, ray_angle, ray->pov.ang_dir);
	horizontal_distance = cast_ray_horizontal(game, ray, ray_angle, ray_id);
	vertical_distance = cast_ray_vertical(game, ray, ray_angle, ray_id);
	printf("ray_id_%d, horizontal_distance: %f, vertical distance: %f\n", ray_id, horizontal_distance, vertical_distance);
	beta = ray_angle - ray->pov.ang_dir;
	printf("ray_id_%d, beta: %f\n", ray_id, beta);
    if (horizontal_distance == -1)
        distance = vertical_distance;
	else if (vertical_distance == -1)
		distance = horizontal_distance;
	else if (horizontal_distance < vertical_distance)
		distance = horizontal_distance;
	else
		distance = vertical_distance;
	corrected_distance = distance * get_cosine(ray, (int)beta);
	printf("ray_id_%d, corrected_distance: %f, beta cosine: %f\n", ray_id, corrected_distance, get_cosine(ray, (int)beta));
	printf("ray_id_%d, ray_angle: %f, pov.ang_dir: %f, horizontal_distance: %f, vertical_distance: %f, corrected_distance: %f\n",
		ray_id, ray_angle, ray->pov.ang_dir, horizontal_distance, vertical_distance, corrected_distance);
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
	ray_angle = ray->pov.ang_dir + ray->h_fov;
	ray_angle = normalise_ray_angle(ray_angle);
	printf("!! first angle: %f, last angle: %d, ray_ang_inc: %f\n", ray_angle, normalize_angle(ray_angle - ray->fov) ,ray->ray_ang_inc);
	i = 0;
	while (i < WIDTH)
	{
		ray->ray_dist[i] = cast_ray(game, ray, ray_angle, i);
		ray->wall_height[i] = ray->height_calc / ray->ray_dist[i];
		printf("\n\nray_id_%d, ray_angle %f, distance: %f, height: %f\n", i, ray_angle, ray->ray_dist[i], ray->wall_height[i]);
		ray_angle -= ray->ray_ang_inc;
		ray_angle = normalise_ray_angle(ray_angle);
		i++;
	}
	draw_walls(game);
}
