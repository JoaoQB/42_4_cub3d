/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:18:46 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/01/02 19:42:25 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	start_ray(t_ray *ray, int ray_id)
{
	if (!ray)
		return ;
	ray->id = ray_id;
	ray->hit = 0;
	ray->cam_x = 2 * ray_id / ray->cam.width - 1;
	// printf("ray_id_%d: cam_x = %f (normalized ray position on camera plane)\n", ray_id, ray->cam_x);
	ray->dir_x = ray->cam.dir.x + ray->cam.plane.x * ray->cam_x;
	ray->dir_y = ray->cam.dir.y + ray->cam.plane.y * ray->cam_x;
	// printf("ray_id_%d: Final Direction Vector (dir_x: %f, dir_y: %f)\n",
		// ray_id, ray->dir_x, ray->dir_y);
	ray->grid_x = (int)ray->cam.pos.x;
	ray->grid_y = (int)ray->cam.pos.y;
	// printf("ray_id_%d: Starting grid position -> grid_x: %d, grid_y: %d\n", ray_id, ray->grid_x, ray->grid_y);
	if (ray->dir_x == 0)
		ray->next_x = 1e30;
	else
		ray->next_x = fabs(1 / ray->dir_x);
	// printf("ray_id_%d: next_x = %f (distance between vertical grid lines)\n", ray_id, ray->next_x);
	if (ray->dir_y == 0)
		ray->next_y = 1e30;
	else
		ray->next_y = fabs(1 / ray->dir_y);
	// printf("ray_id_%d: next_y = %f (distance between horizontal grid lines)\n", ray_id, ray->next_y);
	return ;
}


static void	aim_ray(t_ray *ray)
{
	if (!ray)
		return ;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->delta_x = (ray->cam.pos.x - ray->grid_x) * ray->next_x;
	}
	else
	{
		ray->step_x = 1;
		ray->delta_x = (ray->grid_x + 1.0 - ray->cam.pos.x) * ray->next_x;
	}
	// printf("ray_id_%d: step_x = %d, delta_x = %f\n", ray->id, ray->step_x, ray->delta_x);
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->delta_y = (ray->cam.pos.y - ray->grid_y) * ray->next_y;
	}
	else
	{
		ray->step_y = 1;
		ray->delta_y = (ray->grid_y + 1.0 - ray->cam.pos.y) * ray->next_y;
	}
	// printf("ray_id_%d: step_y = %d, delta_y = %f\n", ray->id, ray->step_y, ray->delta_y);
}

// Keeping debug logs for now
static void	calculate_wall_info(t_game *game, t_ray *ray)
{
	t_wall	*wall;

	if (!game || !ray)
		return ;
	wall = &ray->walls[ray->id];
	wall->ray_dist = get_wall_distance(ray);
	wall->dir = get_wall_direction(ray);
	wall->wall_x = get_wall_x(ray);
	// printf("\n=== Wall Info Debug ===\n");
	// printf("Ray ID: %d\n", ray->id);
	// printf("Ray Distance: %f\n", wall->ray_dist);
	// printf("Wall Direction: %d\n", wall->dir);
	// printf("Wall X: %f\n", wall->wall_x);
	if (wall->ray_dist == -1)
		wall->height = 0;
	else
		wall->height = (int)(ray->cam.height / wall->ray_dist) / SCALE;
	wall->half_height = wall->height / 2;
	wall->top = game->ray.cam.h_height - wall->half_height;
	if (wall->top < 0)
		wall->top = 0;
	wall->bottom = game->ray.cam.h_height + wall->half_height;
	if (wall->bottom >= HEIGHT)
		wall->bottom = HEIGHT - 1;
	// printf("Wall Height: %d\n", wall->height);
	// printf("Wall Top: %d\n", wall->top);
	// printf("Wall Bottom: %d\n", wall->bottom);
	wall->texture = game->texture[wall->dir];
	// if (!wall->texture)
	// 	printf("Error: Wall texture is NULL\n");
	// else
	// 	printf("wall texture: %s\n", wall->texture->image_name);
	wall->tex_x = get_texture_x(ray, wall);
	// printf("Texture X: %d\n", wall->tex_x);
}

static void cast_ray(t_game*game, t_ray *ray)
{
	if (!game || !ray)
		return ;
	while (ray->hit == 0)
	{
		if (ray->delta_x < ray->delta_y)
		{
			// printf("ray_id_%d: delta_x < delta_y, delta_x = %f, delta_y = %f\n"
			// 	, ray->id, ray->delta_x, ray->delta_y);
			ray->delta_x += ray->next_x;
			ray->grid_x += ray->step_x;
			ray->side = 0;
			// printf("ray_id_%d: Updated delta_x = %f, delta_y = %f, grid_x = %d, grid_y = %d\n"
			// 	, ray->id, ray->delta_x, ray->delta_y, ray->grid_x, ray->grid_y);
		}
		else
		{
			// printf("ray_id_%d: delta_x >= delta_y, delta_x = %f, delta_y = %f\n", ray->id, ray->delta_x, ray->delta_y);
			ray->delta_y += ray->next_y;
			ray->grid_y += ray->step_y;
			ray->side = 1;
			// printf("ray_id_%d: Updated delta_x = %f, delta_y = %f, grid_x = %d, grid_y = %d\n"
				// , ray->id, ray->delta_x, ray->delta_y, ray->grid_x, ray->grid_y);
		}
		if (ray->grid_y < 0 || ray->grid_y >= ray->cam.map_height || ray->grid_x < 0
			|| ray->grid_x >= ray->cam.map_width)
		{
			// printf("ray_id_%d: Out of bounds at grid_x = %d, grid_y = %d\n", ray->id, ray->grid_x, ray->grid_y);
			break ;
		}
		if (game->map[ray->grid_y][ray->grid_x] == '1')
		{
			// printf("ray_id_%d: Hit wall at grid_x = %d, grid_y = %d\n", ray->id, ray->grid_x, ray->grid_y);
			ray->hit = 1;
		}
	}
	calculate_wall_info(game, ray);
}

void	raycasting(void)
{
	t_game	*game;
	t_ray	*ray;
	int		i;

	game = ft_game();
	if (!game)
		return ;
	ray = &game->ray;
	i = 0;
	while (i < WIDTH)
	{
		start_ray(ray, i);
		aim_ray(ray);
		cast_ray(game, ray);
		i++;
	}
	draw_walls(game);
}
