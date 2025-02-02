/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:18:46 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/02 16:29:36 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Keeping debug logs for now
static void	start_ray(t_ray *ray, int ray_id)
{
	if (!ray)
		return ;
	ray->id = ray_id;
	ray->hit = 0;
	ray->cam_x = 2 * ray_id / ray->cam.width - 1;
	ray->dir.x = ray->cam.dir.x + ray->cam.plane.x * ray->cam_x;
	ray->dir.y = ray->cam.dir.y + ray->cam.plane.y * ray->cam_x;
	ray->grid_x = (int)ray->cam.pos.x;
	ray->grid_y = (int)ray->cam.pos.y;
	if (ray->dir.x == 0)
		ray->next.x = 1e30;
	else
		ray->next.x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->next.y = 1e30;
	else
		ray->next.y = fabs(1 / ray->dir.y);
	// debug_start(ray);
}

static void	aim_ray(t_ray *ray)
{
	if (!ray)
		return ;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->delta.x = (ray->cam.pos.x - ray->grid_x) * ray->next.x;
	}
	else
	{
		ray->step.x = 1;
		ray->delta.x = (ray->grid_x + 1.0 - ray->cam.pos.x) * ray->next.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->delta.y = (ray->cam.pos.y - ray->grid_y) * ray->next.y;
	}
	else
	{
		ray->step.y = 1;
		ray->delta.y = (ray->grid_y + 1.0 - ray->cam.pos.y) * ray->next.y;
	}
	// debug_aim(ray);
}

static void	calculate_wall_info(t_game *game, t_ray *ray)
{
	t_wall	*wall;

	if (!game || !ray)
		return ;
	wall = &ray->walls[ray->id];
	wall->ray_dist = get_wall_distance(ray);
	wall->dir = get_wall_direction(ray);
	wall->wall_x = get_wall_x(ray);
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
	wall->texture = game->texture[wall->dir];
	wall->tex_x = get_texture_x(ray, wall);
	// debug_wall_info(ray, wall);
}

static void	cast_ray(t_game*game, t_ray *ray)
{
	if (!game || !ray)
		return ;
	while (ray->hit == 0)
	{
		if (ray->delta.x < ray->delta.y)
		{
			ray->delta.x += ray->next.x;
			ray->grid_x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->delta.y += ray->next.y;
			ray->grid_y += ray->step.y;
			ray->side = 1;
		}
		if (ray->grid_y < 0 || ray->grid_y >= ray->cam.map_height
			|| ray->grid_x < 0 || ray->grid_x >= ray->cam.map_width)
		{
			// debug_cast(ray);
			break ;
		}
		if (game->map[(int)ray->grid_y][(int)ray->grid_x] == '1')
		{
			// debug_cast(ray);
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
	ray->cam.plane.x = -ray->cam.dir.y * get_tangent(ray->cam.hfov);
	ray->cam.plane.y = ray->cam.dir.x * get_tangent(ray->cam.hfov);
	i = -1;
	while (++i < WIDTH)
	{
		start_ray(ray, i);
		aim_ray(ray);
		cast_ray(game, ray);
	}
	// door_switch for debug
	door_switch(game);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx->mlx,
		game->mlx->win, game->mlx->img.img, 0, 0);
}
