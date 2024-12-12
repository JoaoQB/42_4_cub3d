/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_math_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:35:07 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/12 19:06:21 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	get_dist_square(t_pov player, t_coord intersection)
{
	double	delta_x;
	double	delta_y;

	delta_x = fabs(player.pos_ux - intersection.x);
	delta_y = fabs(player.pos_uy - intersection.y);
	return (sqrt(pow(delta_x, 2) + pow(delta_y, 2)));
}

double	get_dist(t_pov player, t_coord delta, double ray_angle)
{
	double	delta_x;
	double	delta_y;

	delta_x = fabs(player.pos_ux - delta.x);
	delta_y = fabs(player.pos_uy - delta.y);

	delta_x = delta_x / fabs(get_cosine((int)ray_angle));
	delta_y = delta_y / fabs(get_sine((int)ray_angle));
	return (delta_x + delta_y);
}
