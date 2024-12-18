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

#include "../../includes/cub3d.h"

double	get_wall_distance(t_ray *ray)
{
	double	distance;

	if (!ray || ray->hit == 0)
		return (-1);
	if (ray->side == 0)
		distance = (ray->rayInterX - ray->rayNextX);
	else
		distance = (ray->rayInterY - ray->rayNextY);
	return (distance);
}

int	get_wall_direction(t_ray *ray)
{
	if (!ray || ray->hit == 0)
		return (-1);
	if (ray->side == 0)
	{
		if (ray->rayDirX > 0)
			return (WALL_EAST);
		else
			return (WALL_WEST);
	}
	else
	{
		if (ray->rayDirY > 0)
			return (WALL_SOUTH);
		else
			return (WALL_NORTH);
	}
}
