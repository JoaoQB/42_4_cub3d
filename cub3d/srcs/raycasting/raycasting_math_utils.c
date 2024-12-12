/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_math_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:35:07 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/12 14:17:54 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	get_vert_dist(double pos_ux, double inter_x, double ray_angle)
{
	double	distance;

	distance = fabs(pos_ux - inter_x) / fabs(get_cosine((int)ray_angle));
	return (distance);
}

double	get_horiz_dist(double pos_uy, double inter_y, double ray_angle)
{
	double	distance;

	distance = fabs(pos_uy - inter_y) / fabs(get_sine((int)ray_angle));
	return (distance);
}
