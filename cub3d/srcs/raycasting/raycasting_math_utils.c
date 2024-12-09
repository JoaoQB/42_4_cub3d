/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_math_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:57:25 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/09 22:58:45 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	normalize_angle(int angle)
{
	angle = angle % MAX_ANGLE;
	if (angle < 0)
		angle += MAX_ANGLE;
	return angle;
}

double	get_cosine(t_ray *ray, int ray_angle)
{
	double	cosine;

	if (!ray)
		return (-1);
	ray_angle = normalize_angle(ray_angle);
	cosine = ray->trign.cosines[ray_angle];
	printf("ray_angle: %d, cosine %f\n", ray_angle, cosine);
	return (cosine);
}

double	get_sine(t_ray *ray, int ray_angle)
{
	double	sine;

	if (!ray)
		return (-1);
	ray_angle = normalize_angle(ray_angle);
	sine = ray->trign.sines[ray_angle];
	return (sine);
}

double	get_tangent(t_ray *ray, int ray_angle)
{
	double	tangent;

	if (!ray)
		return (-1);
	ray_angle = normalize_angle(ray_angle);
	tangent = ray->trign.tangents[ray_angle];
	// printf("ray_angle: %d, tangent result: %f\n", ray_angle, tangent);
	return (tangent);
}

double	get_radiant(t_ray *ray, int ray_angle)
{
	double	radiant;

	if (!ray)
		return (-1);
	ray_angle = normalize_angle(ray_angle);
	radiant = ray->trign.radians[ray_angle];
	return (radiant);
}
