/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_trign_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:57:25 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/10 22:59:41 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	normalize_angle(int angle)
{
	angle = angle % MAX_ANGLE;
	if (angle < 0)
		angle += MAX_ANGLE;
	return angle;
}

double	get_cosine(int ray_angle)
{
	double	cosine;
	t_ray	*ray;

	ray = &ft_game()->ray;
	if (!ray)
		return (-1);
	ray_angle = normalize_angle(ray_angle);
	cosine = ray->trign.cosines[ray_angle];
	printf("!! ray_angle: %d, cosine %f\n", ray_angle, cosine);
	return (cosine);
}

double	get_sine(int ray_angle)
{
	double	sine;
	t_ray	*ray;

	ray = &ft_game()->ray;
	if (!ray)
		return (-1);
	ray_angle = normalize_angle(ray_angle);
	sine = ray->trign.sines[ray_angle];
	printf("!! ray_angle: %d, sine %f\n", ray_angle, sine);
	return (sine);
}

double	get_tangent(int ray_angle)
{
	double	tangent;
	t_ray	*ray;

	ray = &ft_game()->ray;
	if (!ray)
		return (-1);
	ray_angle = normalize_angle(ray_angle);
	tangent = ray->trign.tangents[ray_angle];
	printf("!! ray_angle: %d, tangent result: %f\n", ray_angle, tangent);
	return (tangent);
}

double	get_radiant(int ray_angle)
{
	double	radiant;
	t_ray	*ray;

	ray = &ft_game()->ray;
	if (!ray)
		return (-1);
	ray_angle = normalize_angle(ray_angle);
	radiant = ray->trign.radians[ray_angle];
	printf("!! ray_angle: %d, radiant result: %f\n", ray_angle, radiant);
	return (radiant);
}
