/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_math_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:57:25 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/03 17:13:44 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	get_cosine(t_ray *ray, int ray_angle)
{
	double	cosine;

	if (!ray)
		return (-1);
	cosine = ray->trign.cosines[ray_angle % MAX_ANGLE];
	return (cosine);
}

double	get_sine(t_ray *ray, int ray_angle)
{
	double	sine;

	if (!ray)
		return (-1);
	sine = ray->trign.sines[ray_angle % MAX_ANGLE];
	return (sine);
}

double	get_tangent(t_ray *ray, int ray_angle)
{
	double	tangent;

	if (!ray)
		return (-1);
	tangent = ray->trign.tangents[ray_angle % MAX_ANGLE];
	return (tangent);
}

double	get_radiant(t_ray *ray, int ray_angle)
{
	double	radiant;

	if (!ray)
		return (-1);
	radiant = ray->trign.radians[ray_angle % MAX_ANGLE];
	return (radiant);
}
