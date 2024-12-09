/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_horizontal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:12:14 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/09 23:04:14 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	find_next_horizontal_increment(t_ray *ray, double ray_angle, t_coord *next_intersection)
{
	double	next_y;
	double	next_x;

	if (!ray || !next_intersection)
		return ;
	if (is_ray_facing_upwards(ray_angle))
		next_y = -UNIT_SIZE;
	else
		next_y = UNIT_SIZE;
	next_x = UNIT_SIZE / get_tangent(ray, (int)ray_angle);
	next_intersection->y = next_y;
	next_intersection->x = next_x;
}

static void	find_first_horizontal_intersection(t_ray *ray, double ray_angle, t_coord *horizontal_intersection)
{
	double	intersection_y;
	double	intersection_x;

	if (!ray || !horizontal_intersection)
		return ;
	if (is_ray_facing_upwards(ray_angle))
	{
		intersection_y = floor(ray->pov.pos_uy / UNIT_SIZE) * (UNIT_SIZE) - 1;
	}
	else
	{
		intersection_y = floor(ray->pov.pos_uy / UNIT_SIZE) * (UNIT_SIZE) + UNIT_SIZE;
	}
	horizontal_intersection->y = intersection_y;
	intersection_x = ray->pov.pos_ux + (ray->pov.pos_uy - intersection_y) / get_tangent(ray, (int)ray_angle);
	horizontal_intersection->x = intersection_x;
	printf("First horizontal intersection: x = %f, y = %f\n", intersection_x, intersection_y);
}

double	cast_ray_horizontal(t_game *game, t_ray *ray, double ray_angle)
{
	t_coord	horizontal_intersection;
	t_coord	next_intersection;
	double	distance;
	int		grid_x;
	int		grid_y;

	if (!game || !game->map || !ray)
		return (-1);
	find_first_horizontal_intersection(ray, ray_angle, &horizontal_intersection);
	find_next_horizontal_increment(ray, ray_angle, &next_intersection);
	while (1)
	{
		grid_x = horizontal_intersection.x / UNIT_SIZE;
		grid_y = horizontal_intersection.y / UNIT_SIZE;
		printf("Ray at: x = %f, y = %f, grid_x = %d, grid_y = %d\n", horizontal_intersection.x, horizontal_intersection.y, grid_x, grid_y);
		if (grid_x < 0 || grid_x >= ray->m_width || grid_y < 0 || grid_y >= ray->m_height)
			break ;
		if (game->map[grid_y][grid_x] == '1')
		{
			distance = fabs(ray->pov.pos_ux - horizontal_intersection.x) / fabs(get_cosine(ray, (int)ray_angle));
			printf("Hit wall at: x = %f, y = %f, distance = %f, cosine_value = %f\n", horizontal_intersection.x, horizontal_intersection.y, distance, fabs(get_cosine(ray, (int)ray_angle)));
			return (distance);
		}
		horizontal_intersection.x += next_intersection.x;
		horizontal_intersection.y += next_intersection.y;
		printf("Next horizontal increment: x = %f, y = %f\n", next_intersection.x, next_intersection.y);
		printf("Next intersection: x = %f, y = %f\n", horizontal_intersection.x, horizontal_intersection.y);
	}
	return (-1);
}
