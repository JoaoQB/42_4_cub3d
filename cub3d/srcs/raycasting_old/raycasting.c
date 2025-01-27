/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:53:21 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/18 14:45:34 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	normalise_ray_angle(double ray_angle)
{
	// printf("normalise_ray_angle: input ray_angle = %f\n", ray_angle);
	ray_angle = fmod(ray_angle, MAX_ANGLE); // Wrap angle to (-MAX_ANGLE, MAX_ANGLE)
	if (ray_angle < 0)
		ray_angle += MAX_ANGLE; // Ensure angle is non-negative
	// printf("normalise_ray_angle: normalized ray_angle = %f\n", ray_angle);
	return ray_angle;
}

// static double	cast_ray_cardinal(t_game *game, t_ray *ray, double ray_angle, int ray_id)
// {
// 	if (is_ray_horizontal(ray_angle))
// 		return (cast_ray_vertical(game, ray, ray_angle, ray_id));
// 	else
// 		return (cast_ray_horizontal(game, ray, ray_angle, ray_id));
// }

static double	cast_ray(t_game *game, t_ray *ray, double ray_angle, int ray_id)
{
	double	horizontal_distance;
	double	vertical_distance;
	double	distance;
	double	beta;
	double	corrected_distance;

	printf("ray_id_%d, ray_angle: %f, pov.ang_dir: %f\n", ray_id, ray_angle, ray->pov.ang_dir);
	beta = ray_angle - ray->pov.ang_dir;
	// if (is_ray_cardinal(ray_angle))
	// {
	// 	printf("ray_id_%d, ray_angle: %f, is cardinal\n", ray_id, ray_angle);
	// 	distance = cast_ray_cardinal(game, ray, ray_angle, ray_id);
	// 	corrected_distance = distance * get_cosine((int)beta);
	// 	return (corrected_distance);
	// }
	printf("ray_id_%d, ray_angle: %f, checking horizontal and vertical\n", ray_id, ray_angle);
	horizontal_distance = cast_ray_horizontal(game, ray, ray_angle, ray_id);
	vertical_distance = cast_ray_vertical(game, ray, ray_angle, ray_id);
	if (horizontal_distance == -1)
		distance = vertical_distance;
	else if (vertical_distance == -1)
		distance = horizontal_distance;
	else
		distance = fmin(horizontal_distance, vertical_distance);
	corrected_distance = distance * get_cosine((int)beta);
	printf("ray_id_%d, ray_angle: %f, pov.ang_dir: %f, horizontal_distance: %f, vertical_distance: %f, corrected_distance: %f, beta %f, beta cosine%f\n",
		ray_id, ray_angle, ray->pov.ang_dir, horizontal_distance, vertical_distance, corrected_distance, beta, get_cosine((int)beta));
	return (corrected_distance);
}

void	raycasting_old()
{
	t_game	*game;
	t_ray	*ray;
	int		i;
	double	ray_angle;
	double	last_angle;

	game = ft_game();
	ray = &game->ray;
	ray_angle = ray->pov.ang_dir - ray->h_fov;
	ray_angle = normalise_ray_angle(ray_angle);
	last_angle = ray_angle + ray->fov;
	printf("!! first angle: %f, middle angle: %f, last angle: %f, ray_ang_inc: %f\n", ray_angle, ray->pov.ang_dir , last_angle,ray->ray_ang_inc);
	i = 0;
	while (i < WIDTH)
	{
		ray->ray_dist[i] = cast_ray(game, ray, ray_angle, i);
		// if (ray->ray_dist[i] <= 5 || ray->ray_dist[i] > 1000)
		// 	ray->ray_dist[i] = ray->ray_dist[i - 1];
		ray->wall_height[i] = ray->height_calc / ray->ray_dist[i];
		printf("\n\nray_id_%d, ray_angle %f, distance: %f, height: %f\n", i, ray_angle, ray->ray_dist[i], ray->wall_height[i]);
		ray_angle += ray->ray_ang_inc;
		ray_angle = normalise_ray_angle(ray_angle);
		i++;
	}
	draw_walls(game);
}
