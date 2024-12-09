/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_vertical.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:20:54 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/09 23:03:29 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	find_next_vertical_increment(t_ray *ray, double ray_angle, t_coord *next_intersection)
{
	double	next_x;
	double	next_y;

	if (!ray || !next_intersection)
		return ;
	if (is_ray_facing_right(ray_angle))
		next_x = UNIT_SIZE;
	else
		next_x = -UNIT_SIZE;
	next_y = UNIT_SIZE * get_tangent(ray, (int)ray_angle);
	next_intersection->x = next_x;
	next_intersection->y = next_y;
	printf("Next vertical increment: x = %f, y = %f\n", next_x, next_y);
}

static void	find_first_vertical_intersection(t_ray *ray, double ray_angle, t_coord *vertical_intersection)
{
	double	intersection_x;
	double	intersection_y;

	if (!ray || !vertical_intersection)
		return ;
	if (is_ray_facing_upwards(ray_angle))
	{
		intersection_x = floor(ray->pov.pos_ux / UNIT_SIZE) * (UNIT_SIZE) + UNIT_SIZE;
	}
	else
	{
		intersection_x = floor(ray->pov.pos_ux / UNIT_SIZE) * (UNIT_SIZE) - 1;
	}
	vertical_intersection->x = intersection_x;
	intersection_y = ray->pov.pos_uy + (ray->pov.pos_ux - intersection_x) / get_tangent(ray, (int)ray_angle);
	vertical_intersection->y = intersection_y;
	printf("First vertical intersection: x = %f, y = %f\n", intersection_x, intersection_y);
}

double	cast_ray_vertical(t_game *game, t_ray *ray, double ray_angle)
{
	t_coord	vertical_intersection;
	t_coord	next_intersection;
	double	distance;
	int		grid_x;
	int		grid_y;

	if (!game || !ray)
		return (-1);
	find_first_vertical_intersection(ray, ray_angle, &vertical_intersection);
	find_next_vertical_increment(ray, ray_angle, &next_intersection);
	while (1)
	{
		grid_x = vertical_intersection.x / UNIT_SIZE;
		grid_y = vertical_intersection.y / UNIT_SIZE;
		printf("Ray at: x = %f, y = %f, grid_x = %d, grid_y = %d\n", vertical_intersection.x, vertical_intersection.y, grid_x, grid_y);
		if (grid_x < 0 || grid_x >= ray->m_width || grid_y < 0 || grid_y >= ray->m_height)
			break ;
		if (game->map[grid_y][grid_x] == '1')
		{
			distance = fabs(ray->pov.pos_uy - vertical_intersection.y) / fabs(get_sine(ray, (int)ray_angle));
			printf("Hit wall at: x = %f, y = %f, distance = %f\n", vertical_intersection.x, vertical_intersection.y, distance);
			return (distance);
		}
		vertical_intersection.x += next_intersection.x;
		vertical_intersection.y += next_intersection.y;
		printf("Next intersection: x = %f, y = %f\n", vertical_intersection.x, vertical_intersection.y);
	}
	return (-1);
}
