/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:10:09 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/09 21:52:01 by jqueijo-         ###   ########.fr       */
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
