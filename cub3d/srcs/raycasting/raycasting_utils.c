/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:10:09 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/11 17:33:16 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool is_ray_cardinal(double ray_angle)
{
	if (fabs(ray_angle - 0) < ANGLE_TOLERANCE
		|| fabs(ray_angle - 90) < ANGLE_TOLERANCE
		|| fabs(ray_angle - 180) < ANGLE_TOLERANCE
		|| fabs(ray_angle - 270) < ANGLE_TOLERANCE
		|| fabs(ray_angle - 360) < ANGLE_TOLERANCE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool	is_ray_horizontal(double ray_angle)
{
	double	east;
	double	west;

	east = 0;
	west = 180;
	if (fabs(ray_angle - east) < ANGLE_TOLERANCE
		|| fabs(ray_angle - west) < ANGLE_TOLERANCE)
		return (true);
	else
		return (false);
}

bool	is_ray_vertical(double ray_angle)
{
	double	north;
	double	south;

	north = 90;
	south = 270;
	if (fabs(ray_angle - north) < ANGLE_TOLERANCE
		|| fabs(ray_angle - south) < ANGLE_TOLERANCE)
		return (true);
	else
		return (false);
}

bool	is_ray_facing_right(double ray_angle)
{
	if ((ray_angle >= 0 && ray_angle < 90)
		|| (ray_angle > 270 && ray_angle <= 360))
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

bool	is_ray_facing_upwards(double ray_angle)
{
	if (ray_angle > 0 && ray_angle < 180)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}
