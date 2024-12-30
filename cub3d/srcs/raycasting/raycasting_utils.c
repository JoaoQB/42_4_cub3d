/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:24:15 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/29 20:33:03 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_wall_distance(t_ray *ray)
{
	double	distance;

	if (!ray || ray->hit == 0)
		return (-1);
	if (ray->side == 0)
	{
		distance = (ray->rayInter.x - ray->rayNext.x);
		// distance = ray->rayInter.x - ray->cam.pos.x;
		// distance = (ray->grid.x * UNIT_SIZE - ray->cam.pos.x) / ray->rayDir.x;
	}
	else
	{
		distance = (ray->rayInter.y - ray->rayNext.y);
		// distance = ray->rayInter.y - ray->cam.pos.x;
		// distance = (ray->grid.y * UNIT_SIZE - ray->cam.pos.y) / ray->rayDir.y;
	}
	// distance = sqrt(ray->rayInter.x * ray->rayInter.x + ray->rayInter.y * ray->rayInter.y);
	// distance = distance * cos(atan2(ray->rayDir.y, ray->rayDir.x) - atan2(ray->cam.dir.y, ray->cam.dir.x));
	return (distance / (UNIT_SIZE * 2));
}

int	get_wall_direction(t_ray *ray)
{
	if (!ray || ray->hit == 0)
		return (WALL_UNKNOWN);
	if (ray->side == 0)
	{
		if (ray->rayDir.x > 0)
			return (WALL_EAST);
		else
			return (WALL_WEST);
	}
	else
	{
		if (ray->rayDir.y > 0)
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

	printf("\n=== Texture X Debug ===\n");

	// Check pointers
	if (!ray) {
		printf("Error: Ray is NULL\n");
		return (0);
	}
	if (!wall) {
		printf("Error: Wall is NULL\n");
		return (0);
	}
	if (!wall->texture) {
		printf("Error: Wall texture is NULL\n");
		return (0);
	}
	if (!wall->texture->image_data) {
		printf("Error: Image data is NULL\n");
		return (0);
	}
	// Print debug info
	printf("Ray side: %d\n", ray->side);
	printf("Ray direction X: %f\n", ray->rayDirX);
	printf("Ray direction Y: %f\n", ray->rayDirY);
	printf("Wall X: %f\n", wall->wall_x);
	printf("Texture width: %d\n", wall->texture->image_data->width);
	tex_width = wall->texture->image_data->width;
	tex_x = (int)(wall->wall_x * tex_width);
	if ((ray->side == 0 && ray->rayDirX > 0)
		|| (ray->side == 1 && ray->rayDirY < 0))
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}
