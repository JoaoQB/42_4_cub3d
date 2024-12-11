/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_horizontal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:12:14 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/11 18:32:50 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	find_next_horizontal_increment(t_ray *ray, double ray_angle, t_coord *next_intersection, int ray_id)
{
	double	next_y;
	double	next_x;
	double	tangent;

	if (!ray || !next_intersection)
		return ;
	if (is_ray_facing_upwards(ray_angle))
	{
		next_y = -UNIT_SIZE;
	}
	else
	{
		next_y = UNIT_SIZE;
	}
	tangent = get_tangent(ray, (int)ray_angle);
	if (is_ray_vertical(ray_angle))
		next_x = 0;
	else
	{
		// if (is_ray_facing_right(ray_angle))
		// {
		// 	printf("ray_id_%d, is facing right\n", ray_id);
		// 	next_x = next_y / tangent;
		// }
		// else
		// {
		// 	printf("ray_id_%d, is facing left\n", ray_id);
		// 	next_x = next_y / tangent;
		// }
		next_x = next_y / tangent;
	}
	next_intersection->y = next_y;
	next_intersection->x = -next_x;
	printf("ray_id_%d, tangent_%f, Next horizontal increment: ray_angle = %f, next_x = %f, next_y = %f\n", ray_id, tangent, ray_angle, next_x, next_y);
}

static void	find_first_horizontal_intersection(t_ray *ray, double ray_angle, t_coord *horizontal_intersection, int ray_id)
{
	double	intersection_y;
	double	intersection_x;
	double	tangent;

	if (!ray || !horizontal_intersection)
		return ;
	if (is_ray_facing_upwards(ray_angle))
	{
		printf("ray_id_%d, is facing up\n", ray_id);
		intersection_y = floor(ray->pov.pos_uy / UNIT_SIZE) * (UNIT_SIZE) - 1;
	}
	else
	{
		printf("ray_id_%d, is facing down\n", ray_id);
		intersection_y = floor(ray->pov.pos_uy / UNIT_SIZE) * (UNIT_SIZE) + UNIT_SIZE;
	}
	tangent = get_tangent(ray, (int)ray_angle);
	if (is_ray_vertical(ray_angle))
	{
		printf("ray_id_%d, is vertical\n", ray_id);
		intersection_x = ray->pov.pos_ux;
	}
	else
		intersection_x = ray->pov.pos_ux + (ray->pov.pos_uy - intersection_y) / tangent;
	printf("ray_id_%d, tangent_%f, First horizontal intersection: ray_angle = %f, intersection_x = %f, intersection_y = %f\n", ray_id, tangent, ray_angle, intersection_x, intersection_y);
	horizontal_intersection->y = intersection_y;
	horizontal_intersection->x = intersection_x;
}

double	cast_ray_horizontal(t_game *game, t_ray *ray, double ray_angle, int ray_id)
{
	t_coord	horizontal_intersection;
	t_coord	next_intersection;
	double	distance;
	int		grid_x;
	int		grid_y;

	if (!game || !game->map || !ray)
		return (-1);
	find_first_horizontal_intersection(ray, ray_angle, &horizontal_intersection, ray_id);
	find_next_horizontal_increment(ray, ray_angle, &next_intersection, ray_id);
	while (1)
	{
		grid_x = horizontal_intersection.x / UNIT_SIZE;
		grid_y = horizontal_intersection.y / UNIT_SIZE;
		printf("\nray_id_%d, horziontal, at: x = %f, y = %f, grid_x = %d, grid_y = %d\n", ray_id, horizontal_intersection.x, horizontal_intersection.y, grid_x, grid_y);
		if (grid_x < 0 || grid_x >= ray->m_width || grid_y < 0 || grid_y >= ray->m_height)
		{
			printf("ray_id_%d, horizontal, Out of bounds: grid_x = %d, grid_y = %d, intersection_x = %f, intersection_y = %f\n",
					ray_id, grid_x, grid_y, horizontal_intersection.x, horizontal_intersection.y);
			break ;
		}
		if (game->map[grid_y][grid_x] == '1')
		{
			distance = fabs(ray->pov.pos_ux - horizontal_intersection.x) / fabs(get_cosine(ray, (int)ray_angle));
			printf("ray_id_%d, horizontal, Hit wall: grid_x = %d, grid_y = %d, intersection_x = %f, intersection_y = %f, distance = %f\n",
					ray_id, grid_x, grid_y, horizontal_intersection.x, horizontal_intersection.y, distance);
			return (distance);
		}
		horizontal_intersection.x += next_intersection.x;
		horizontal_intersection.y += next_intersection.y;
	}
	return (-1);
}
