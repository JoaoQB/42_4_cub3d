/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:24:15 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/18 12:13:02 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_wall_distance(t_ray *ray)
{
	double	distance;

	if (!ray || ray->hit == 0)
		return (-1);
	if (ray->side == 0)
	{
		distance = (ray->rayInter.x - ray->rayNext.x);
		// distance = ray->rayInter.x - ray->cam.pos.x;
		// distance = (ray->grid.x * UNIT_SIZE - ray->cam.pos.x) / ray->rayDir.x;
	}
	else
	{
		distance = (ray->rayInter.y - ray->rayNext.y);
		// distance = ray->rayInter.y - ray->cam.pos.x;
		// distance = (ray->grid.y * UNIT_SIZE - ray->cam.pos.y) / ray->rayDir.y;
	}
	// distance = sqrt(ray->rayInter.x * ray->rayInter.x + ray->rayInter.y * ray->rayInter.y);
	// distance = distance * cos(atan2(ray->rayDir.y, ray->rayDir.x) - atan2(ray->cam.dir.y, ray->cam.dir.x));
	return (distance / (UNIT_SIZE * 2));
}

int	get_wall_direction(t_ray *ray)
{
	if (!ray || ray->hit == 0)
		return (-1);
	if (ray->side == 0)
	{
		if (ray->rayDir.x > 0)
			return (WALL_EAST);
		else
			return (WALL_WEST);
	}
	else
	{
		if (ray->rayDir.y > 0)
			return (WALL_SOUTH);
		else
			return (WALL_NORTH);
	}
}
