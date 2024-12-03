/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:10:09 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/03 15:43:20 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_ray_facing_right(double ray_angle)
{
	if ((ray_angle > 0 && ray_angle < 90)
		|| (ray_angle < 360 && ray_angle > 270))
		return (true);
	else
		return (false);
}

bool	is_ray_facing_upwards(double ray_angle)
{
	if (ray_angle > 0 && ray_angle < 180)
		return (true);
	else
		return (false);
}

double	get_distance(double x1, double y1, double x2, double y2)
{
	double	distance;

	distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	return (distance);
}

double	get_radiant(t_ray *ray, int ray_angle)
{
	double	radiant;

	if (!ray)
		return (-1);
	radiant = ray->radians[ray_angle % MAX_ANGLE];
	return (radiant);
}

double	get_tangent(t_ray *ray, int ray_angle)
{
	double	tangent;

	if (!ray)
		return (-1);
	tangent = ray->tangents[ray_angle % MAX_ANGLE];
	return (tangent);
}
