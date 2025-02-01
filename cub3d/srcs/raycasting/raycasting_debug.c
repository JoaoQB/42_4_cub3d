/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_debug.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:25:32 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/01 17:09:50 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_ray(t_ray *ray)
{
	if (!ray)
		return ;
	printf("!! Camera Width: %f\n", ray->cam.width);
	printf("!! Camera Height: %f\n", ray->cam.height);
	printf("!! Camera Half Width: %f\n", ray->cam.hwidth);
	printf("!! Camera Half Height: %f\n", ray->cam.h_height);
	printf("!! Camera FOV: %f\n", ray->cam.fov);
	printf("!! Camera Half FOV: %f\n", ray->cam.hfov);
	printf("!! Camera Position: x = %f, y = %f\n",
		ray->cam.pos.x, ray->cam.pos.y);
	printf("!! Camera Direction: dir_x = %f, dir_y = %f\n",
		ray->cam.dir.x, ray->cam.dir.y);
	printf("!! Camera Plane: plane_x = %f, plane_y = %f\n",
		ray->cam.plane.x, ray->cam.plane.y);
	printf("!! Map Width: %d\n", ray->cam.map_width);
	printf("!! Map Height: %d\n", ray->cam.map_height);
}

void	debug_start(t_ray *ray)
{
	if (!ray)
		return ;
	printf("ray_id_%d: cam_x = %f (normalized ray pos on camera plane)\n",
		ray->id, ray->cam_x);
	printf("ray_id_%d: Final Direction Vector (dir_x: %f, dir_y: %f)\n",
		ray->id, ray->dir_x, ray->dir_y);
	printf("ray_id_%d: Starting grid position -> grid_x: %d, grid_y: %d\n",
		ray->id, ray->grid_x, ray->grid_y);
	printf("ray_id_%d: next_x = %f (distance between vertical grid lines)\n",
		ray->id, ray->next_x);
	printf("ray_id_%d: next_y = %f (distance between horizntl grid lines)\n",
		ray->id, ray->next_y);
}

void	debug_aim(t_ray *ray)
{
	if (!ray)
		return ;
	printf("ray_id_%d: step_x = %d, delta_x = %f\n",
		ray->id, ray->step_x, ray->delta_x);
	printf("ray_id_%d: step_y = %d, delta_y = %f\n",
		ray->id, ray->step_y, ray->delta_y);
}

void	debug_wall_info(t_ray *ray, t_wall *wall)
{
	if (!ray || !wall)
		return ;
	printf("\n=== Wall Info Debug ===\n");
	printf("Ray ID: %d\n", ray->id);
	printf("Ray Distance: %f\n", wall->ray_dist);
	printf("Wall Direction: %d\n", wall->dir);
	printf("Wall X: %f\n", wall->wall_x);
	printf("Wall Height: %d\n", wall->height);
	printf("Wall Top: %d\n", wall->top);
	printf("Wall Bottom: %d\n", wall->bottom);
	if (!wall->texture)
		printf("Error: Wall texture is NULL\n");
	else
		printf("wall texture: %s\n", wall->texture->image_name);
	printf("Texture X: %d\n", wall->tex_x);
}

void	debug_cast(t_ray *ray)
{
	if (!ray)
		return ;
	printf("ray_id_%d: delta_x = %f, delta_y = %f\n",
		ray->id, ray->delta_x, ray->delta_y);
	printf("ray_id_%d: delta_x = %f, delta_y = %f, grid_x = %d, grid_y = %d\n",
		ray->id, ray->delta_x, ray->delta_y, ray->grid_x, ray->grid_y);
	printf("ray_id_%d: Out of bounds at grid_x = %d, grid_y = %d\n",
		ray->id, ray->grid_x, ray->grid_y);
	printf("ray_id_%d: Hit wall at grid_x = %d, grid_y = %d\n",
		ray->id, ray->grid_x, ray->grid_y);
}
