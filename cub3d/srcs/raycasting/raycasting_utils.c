/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:24:15 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/31 11:34:48 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_wall_distance(t_ray *ray)
{
	double	distance;

	if (!ray || ray->hit == 0)
		return (-1);
	if (ray->side == 0)
		distance = (ray->delta_x - ray->next_x);
	else
		distance = (ray->delta_y - ray->next_y);
	return (distance);
}

int	get_wall_direction(t_ray *ray)
{
	if (!ray || ray->hit == 0)
		return (WALL_UNKNOWN);
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (WALL_EAST);
		else
			return (WALL_WEST);
	}
	else
	{
		if (ray->dir_y > 0)
			return (WALL_SOUTH);
		else
			return (WALL_NORTH);
	}
}

double	get_wall_x(t_ray *ray)
{
	double	wall_x;

	if (!ray)
		return (-1);
	if (ray->side == 0)
		wall_x = ray->cam.pos.y + ray->walls[ray->id].ray_dist * ray->dir_y;
	else
		wall_x = ray->cam.pos.x + ray->walls[ray->id].ray_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	get_texture_x(t_ray *ray, t_wall *wall)
{
	int	tex_x;
	int	tex_width;

	// printf("\n=== Texture X Debug ===\n");
	if (!ray || !wall || !wall->texture || !wall->texture->image_data)
	{
		return (0);
	}
	// printf("Ray side: %d\n", ray->side);
	// printf("Ray direction X: %f\n", ray->dir_x);
	// printf("Ray direction Y: %f\n", ray->dir_y);
	// printf("Wall X: %f\n", wall->wall_x);
	// printf("Texture width: %d\n", wall->texture->image_data->width);
	tex_width = wall->texture->image_data->width;
	tex_x = (int)(wall->wall_x * tex_width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}
