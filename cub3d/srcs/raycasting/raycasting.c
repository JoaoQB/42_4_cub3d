/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:18:46 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/30 12:18:48 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	start_ray(t_ray *ray, int ray_id)
{

	if (!ray)
		return ;
	ray->id = ray_id;
	ray->hit = 0;
	ray->camX = 2 * ray_id / ray->cam.width - 1;
	// printf("ray_id_%d: camX = %f (normalized ray position on camera plane)\n", ray_id, ray->camX);
	ray->rayDirX = ray->cam.dir.x + ray->cam.plane.x * ray->camX;
	ray->rayDirY = ray->cam.dir.y + ray->cam.plane.y * ray->camX;
	// printf("ray_id_%d: Final Direction Vector (rayDirX: %f, rayDirY: %f)\n",
		// ray_id, ray->rayDirX, ray->rayDirY);
	ray->gridX = (int)ray->cam.pos.x;
	ray->gridY = (int)ray->cam.pos.y;
	// printf("ray_id_%d: Starting grid position -> gridX: %d, gridY: %d\n", ray_id, ray->gridX, ray->gridY);
	if (ray->rayDirX == 0)
		ray->rayNextX = 1e30;
	else
		ray->rayNextX = fabs(1 / ray->rayDirX);
	// printf("ray_id_%d: rayNextX = %f (distance between vertical grid lines)\n", ray_id, ray->rayNextX);
	if (ray->rayDirY == 0)
		ray->rayNextY = 1e30;
	else
		ray->rayNextY = fabs(1 / ray->rayDirY);
	// printf("ray_id_%d: rayNextY = %f (distance between horizontal grid lines)\n", ray_id, ray->rayNextY);
	return ;
}

// Are doubles needed?
static void aim_ray(t_ray *ray)
{
	if (!ray)
		return ;
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->rayInterX = (ray->cam.pos.x - (double)ray->gridX) * ray->rayNextX;
	}
	else
	{
		ray->stepX = 1;
		ray->rayInterX = ((double)ray->gridX + 1.0 - ray->cam.pos.x) * ray->rayNextX;
	}
	// printf("ray_id_%d: stepX = %d, rayInterX = %f\n", ray->id, ray->stepX, ray->rayInterX);
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->rayInterY = (ray->cam.pos.y - (double)ray->gridY) * ray->rayNextY;
	}
	else
	{
		ray->stepY = 1;
		ray->rayInterY = ((double)ray->gridY + 1.0 - ray->cam.pos.y) * ray->rayNextY;
	}
	// printf("ray_id_%d: stepY = %d, rayInterY = %f\n", ray->id, ray->stepY, ray->rayInterY);
}

static void	calculate_wall_info(t_game *game, t_ray *ray)
{
	t_wall	*wall;

	if (!game || !ray)
		return ;
	wall = &ray->walls[ray->id];
	wall->ray_dist = get_wall_distance(ray);
	wall->wall_dir = get_wall_direction(ray);
	wall->wall_x = get_wall_x(ray);
	// printf("\n=== Wall Info Debug ===\n");
	// printf("Ray ID: %d\n", ray->id);
	// printf("Ray Distance: %f\n", wall->ray_dist);
	// printf("Wall Direction: %d\n", wall->wall_dir);
	// printf("Wall X: %f\n", wall->wall_x);
	if (wall->ray_dist == -1)
		wall->wall_height = 0;
	else
		wall->wall_height = (int)(ray->cam.height / wall->ray_dist) / SCALE;
	wall->wall_half_height = wall->wall_height / 2;
	wall->wall_top = game->ray.cam.hHeight - wall->wall_half_height;
	if (wall->wall_top < 0)
		wall->wall_top = 0;
	wall->wall_bottom = game->ray.cam.hHeight + wall->wall_half_height;
	if (wall->wall_bottom >= HEIGHT)
		wall->wall_bottom = HEIGHT - 1;
	// printf("Wall Height: %d\n", wall->wall_height);
	// printf("Wall Top: %d\n", wall->wall_top);
	// printf("Wall Bottom: %d\n", wall->wall_bottom);
	wall->texture = game->texture[wall->wall_dir];
	if (!wall->texture)
		printf("Error: Wall texture is NULL\n");
	else
		printf("wall texture: %s\n", wall->texture->image_name);
	wall->tex_x = get_texture_x(ray, wall);
	printf("Texture X: %d\n", wall->tex_x);
}

static void cast_ray(t_game*game, t_ray *ray)
{
	if (!game || !ray)
		return ;
	while (ray->hit == 0)
	{
		if (ray->rayInterX < ray->rayInterY)
		{
			// printf("ray_id_%d: rayInterX < rayInterY, rayInterX = %f, rayInterY = %f\n"
			// 	, ray->id, ray->rayInterX, ray->rayInterY);
			ray->rayInterX += ray->rayNextX;
			ray->gridX += ray->stepX;
			ray->side = 0;
			// printf("ray_id_%d: Updated rayInterX = %f, rayInterY = %f, gridX = %d, gridY = %d\n"
			// 	, ray->id, ray->rayInterX, ray->rayInterY, ray->gridX, ray->gridY);
		}
		else
		{
			// printf("ray_id_%d: rayInterX >= rayInterY, rayInterX = %f, rayInterY = %f\n", ray->id, ray->rayInterX, ray->rayInterY);
			ray->rayInterY += ray->rayNextY;
			ray->gridY += ray->stepY;
			ray->side = 1;
			// printf("ray_id_%d: Updated rayInterX = %f, rayInterY = %f, gridX = %d, gridY = %d\n"
				// , ray->id, ray->rayInterX, ray->rayInterY, ray->gridX, ray->gridY);
		}
		if (ray->gridY < 0 || ray->gridY >= ray->cam.mapHeight || ray->gridX < 0
			|| ray->gridX >= ray->cam.mapWidth)
		{
			// printf("ray_id_%d: Out of bounds at gridX = %d, gridY = %d\n", ray->id, ray->gridX, ray->gridY);
			break ;
		}
		if (game->map[ray->gridY][ray->gridX] == '1')
		{
			// printf("ray_id_%d: Hit wall at gridX = %d, gridY = %d\n", ray->id, ray->gridX, ray->gridY);
			ray->hit = 1;
		}
	}
	calculate_wall_info(game, ray);
}

void	raycasting()
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
		// printf("ray_id_%d: distance is: %f\n", i, ray->ray_dist[i]);
		// printf("ray_id_%d: wallHeight is: %f\n", i, ray->wall_height[i]);
		// printf("ray_id_%d: wallDir is: %d\n", i, ray->wall_dir[i]);
		i++;
	}
	draw_walls(game);
}
