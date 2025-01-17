/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:18:46 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/01/02 20:30:12 by jqueijo-         ###   ########.fr       */
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
	ray->dir_x = ray->cam.dir.x + ray->cam.plane.x * ray->cam_x;
	ray->dir_y = ray->cam.dir.y + ray->cam.plane.y * ray->cam_x;
	ray->grid_x = (int)ray->cam.pos.x;
	ray->grid_y = (int)ray->cam.pos.y;
	if (ray->dir_x == 0)
		ray->next_x = 1e30;
	else
		ray->next_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->next_y = 1e30;
	else
		ray->next_y = fabs(1 / ray->dir_y);
	// debug_start(ray);
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
		if (ray->delta_x < ray->delta_y)
		{
			ray->delta_x += ray->next_x;
			ray->grid_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->delta_y += ray->next_y;
			ray->grid_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->grid_y < 0 || ray->grid_y >= ray->cam.map_height
			|| ray->grid_x < 0 || ray->grid_x >= ray->cam.map_width)
		{
			// debug_cast(ray);
			break ;
		}
		if (game->map[ray->grid_y][ray->grid_x] == '1')
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
	draw_walls(game);
	mlx_put_image_to_window(game->mlx->mlx,
	game->mlx->win, game->mlx->img.img, 0, 0);
}
