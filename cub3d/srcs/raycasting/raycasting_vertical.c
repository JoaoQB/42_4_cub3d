/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_vertical.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:20:54 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/12 19:17:36 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	find_next_vertical_increment(t_ray *ray, double ray_angle, t_coord *next_intersection, int ray_id)
{
	double	next_x;
	double	next_y;
	double	tangent;

	if (!ray || !next_intersection)
		return ;
	if (is_ray_facing_right(ray_angle))
	{
		printf("ray_id_%d, is facing right\n", ray_id);
		next_x = UNIT_SIZE;
	}
	else
	{
		printf("ray_id_%d, is facing left\n", ray_id);
		next_x = -UNIT_SIZE;
	}
	tangent = get_tangent((int)ray_angle);
	if (is_ray_horizontal(ray_angle))
		next_y = 0;
	else
	{
		if (is_ray_facing_upwards(ray_angle))
		{
			printf("ray_id_%d, is facing up\n", ray_id);
			next_y = -UNIT_SIZE * tangent;
		}
		else
		{
			printf("ray_id_%d, is facing down\n", ray_id);
			next_y = UNIT_SIZE * tangent;
		}
	}
	next_intersection->x = next_x;
	next_intersection->y = next_y;
	printf("ray_id_%d, tangent_%f, Next vertical increment: ray_angle = %f, next_x = %f, next_y = %f\n"
		, ray_id, tangent, ray_angle, next_x, next_y);
}

static void	find_first_vertical_intersection(t_ray *ray, double ray_angle, t_coord *inter, int ray_id)
{
	double	a_x;
	double	a_y;
	double	tangent;

	if (!ray || !inter)
		return ;
	if (is_ray_facing_right(ray_angle))
	{
		printf("ray_id_%d, is facing right\n", ray_id);
		a_x = floor(ray->pov.pos_ux / UNIT_SIZE) * (UNIT_SIZE) + UNIT_SIZE;
	}
	else
	{
		printf("ray_id_%d, is facing left\n", ray_id);
		a_x = floor(ray->pov.pos_ux / UNIT_SIZE) * (UNIT_SIZE) - 1;
	}
	tangent = get_tangent((int)ray_angle);
	if (is_ray_horizontal(ray_angle))
	{
		printf("ray_id_%d, is horizontal\n", ray_id);
		a_y = ray->pov.pos_uy;
	}
	else
		a_y = ray->pov.pos_uy + (ray->pov.pos_ux - a_x) * tangent;
	inter->x = a_x;
	inter->y = a_y;
	printf("ray_id_%d, tangent_%f, First vertical intersection: ray_angle = %f, intersection_x = %f, intersection_y = %f\n", ray_id, tangent, ray_angle, inter->x, inter->y);
}

double	cast_ray_vertical(t_game *game, t_ray *ray, double ray_angle, int ray_id)
{
	t_coord	delta;
	t_coord	next_inter;
	double	distance;
	int		grid_x;
	int		grid_y;

	if (!game || !ray)
		return (-1);
	find_first_vertical_intersection(ray, ray_angle, &delta, ray_id);
	find_next_vertical_increment(ray, ray_angle, &next_inter, ray_id);
	while (1)
	{
		grid_x = delta.x / UNIT_SIZE;
		grid_y = delta.y / UNIT_SIZE;
		printf("ray_id_%d, vertical, Ray at: x = %f, y = %f, grid_x = %d, grid_y = %d\n", ray_id, delta.x, delta.y, grid_x, grid_y);
		if (grid_x < 0 || grid_x >= ray->m_width || grid_y < 0 || grid_y >= ray->m_height)
		{
			printf("ray_id_%d, vertical, Out of bounds: grid_x = %d, grid_y = %d, intersection_x = %f, intersection_y = %f\n",
					ray_id, grid_x, grid_y, delta.x, delta.y);
			break ;
		}
		if (game->map[grid_y][grid_x] == '1')
		{
			distance = get_dist(ray->pov, delta, ray_angle);
			printf("ray_id_%d, vertical, Hit wall: grid_x = %d, grid_y = %d, intersection_x = %f, intersection_y = %f, distance = %f\n",
					ray_id, grid_x, grid_y, delta.x, delta.y, distance);
			return (distance);
		}
		delta.x += next_inter.x;
		delta.y += next_inter.y;
	}
	return (-1);
}
