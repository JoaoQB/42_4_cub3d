/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_trign_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:28:32 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/06 16:52:11 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	normalize_angle(int angle)
{
	angle = angle % MAX_ANGLE;
	if (angle < 0)
		angle += MAX_ANGLE;
	return (angle);
}

// Replaced M_PI with PI
double	get_radiant(int ray_angle)
{
	double	radiant;

	radiant = ray_angle * (PI / 180);
	return (radiant);
}

double	get_cosine(int ray_angle)
{
	double	cosine;

	ray_angle = normalize_angle(ray_angle);
	cosine = cos(get_radiant(ray_angle));
	return (cosine);
}

double	get_sine(int ray_angle)
{
	double	sine;

	ray_angle = normalize_angle(ray_angle);
	sine = sin(get_radiant(ray_angle));
	return (sine);
}

double	get_tangent(int ray_angle)
{
	double	tangent;

	ray_angle = normalize_angle(ray_angle);
	tangent = tan(get_radiant(ray_angle));
	return (tangent);
}
