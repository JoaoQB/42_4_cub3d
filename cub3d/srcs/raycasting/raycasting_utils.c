/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:24:15 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/31 11:14:48 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_wall_distance(t_ray *ray)
{
	double	distance;

	if (!ray || ray->hit == 0)
		return (-1);
	if (ray->side == 0)
		distance = (ray->rayInterX - ray->rayNextX);
	else
		distance = (ray->rayInterY - ray->rayNextY);
	return (distance);
}

int	get_wall_direction(t_ray *ray)
{
	if (!ray || ray->hit == 0)
		return (WALL_UNKNOWN);
	if (ray->side == 0)
	{
		if (ray->rayDirX > 0)
			return (WALL_EAST);
		else
			return (WALL_WEST);
	}
	else
	{
		if (ray->rayDirY > 0)
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
		wall_x = ray->cam.pos.y + ray->walls[ray->id].ray_dist * ray->rayDirY;
	else
		wall_x = ray->cam.pos.x + ray->walls[ray->id].ray_dist * ray->rayDirX;
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
	// printf("Ray direction X: %f\n", ray->rayDirX);
	// printf("Ray direction Y: %f\n", ray->rayDirY);
	// printf("Wall X: %f\n", wall->wall_x);
	// printf("Texture width: %d\n", wall->texture->image_data->width);
	tex_width = wall->texture->image_data->width;
	tex_x = (int)(wall->wall_x * tex_width);
	if ((ray->side == 0 && ray->rayDirX > 0)
		|| (ray->side == 1 && ray->rayDirY < 0))
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}
