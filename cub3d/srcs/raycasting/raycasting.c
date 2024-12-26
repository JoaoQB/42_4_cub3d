/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:05:50 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/18 15:33:27 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	start_ray(t_ray *ray, int ray_id)
{
	if (!ray)
		return ;
	ray->hit = 0;
	ray->id = ray_id;
	// normalize direction vectors to camera plane fov
	ray->camX = 2 * ray_id / ray->cam.width - 1;
	// same as delta distance from camera to grid
	// relative distance between vertical and horizontal grid lines
	ray->rayDir.x = ray->cam.dir.x + ray->cam.plane.x * ray->camX;
	ray->rayDir.y = ray->cam.dir.y + ray->cam.plane.y * ray->camX;
	//copy camera position to grid position
	ray->grid.x = ft_game()->player.pos.x;
	ray->grid.y = ft_game()->player.pos.y;
	// distance between vertical grid lines
	if (ray->rayDir.x == 0)
		ray->rayNext.x = 1e30;
	else
		ray->rayNext.x = fabs(UNIT_SIZE / ray->rayDir.x);
	if (ray->rayDir.y == 0)
		ray->rayNext.y = 1e30;
	else
		ray->rayNext.y = fabs(UNIT_SIZE / ray->rayDir.y);
	return ;
}

// Are doubles needed?
static void aim_ray(t_ray *ray)
{
	// get the direction of the ray
	// and the distance of the first value of the grid
	if (!ray)
		return ;
	if (ray->rayDir.x < 0)
	{
		ray->step.x = -1;
		ray->rayInter.x = (ray->cam.pos.x - ray->grid.x * UNIT_SIZE) * ray->rayNext.x;
	}
	else
	{
		ray->step.x = 1;
		ray->rayInter.x = ((ray->grid.x + 1) * UNIT_SIZE - ray->cam.pos.x) * ray->rayNext.x;
	}
	if (ray->rayDir.y < 0)
	{
		ray->step.y = -1;
		ray->rayInter.y = (ray->cam.pos.y - ray->grid.y * UNIT_SIZE) * ray->rayNext.y;
	}
	else
	{
		ray->step.y = 1;
		ray->rayInter.y = ((ray->grid.y + 1) * UNIT_SIZE - ray->cam.pos.y) * ray->rayNext.y;
	}
}

static void cast_ray(t_game*game, t_ray *ray)
{
	if (!game || !ray)
		return ;
	while (ray->hit == 0)
	{
		if (ray->rayInter.x < ray->rayInter.y)
		{
			ray->rayInter.x += ray->rayNext.x;
			ray->grid.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->rayInter.y += ray->rayNext.y;
			ray->grid.y += ray->step.y;
			ray->side = 1;
		}
		if (ray->grid.y < 0 || ray->grid.y >= ray->cam.mapHeight || ray->grid.x < 0
			|| ray->grid.x >= ray->cam.mapWidth)
		{
			// printf("ray_id_%d: Out of bounds at grid.x = %d, grid.y = %d\n", ray->id, ray->grid.x, ray->grid.y);
			break ;
		}
		if (game->map[(int) ray->grid.y][(int) ray->grid.x] == '1')
		{
			// printf("ray_id_%d: Hit wall at grid.x = %f, grid.y = %f\n", ray->id, ray->grid.x, ray->grid.y);
			ray->hit = 1;
		}
	}
	ray->ray_dist[ray->id] = get_wall_distance(ray);
	ray->wall_dir[ray->id] = get_wall_direction(ray);
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
		// init_trigonometry(ray);
		// init_ray(game);
		start_ray(ray, i);
		aim_ray(ray);
		cast_ray(game, ray);
		if (ray->ray_dist[ray->id] == -1)
			ray->wall_height[ray->id] = 0;
		else
			ray->wall_height[ray->id] = (int)(ray->cam.height / ray->ray_dist[ray->id]) / SCALE;
		i++;
	}
	draw_walls(game);
}