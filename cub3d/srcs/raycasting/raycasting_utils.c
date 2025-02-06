/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:24:15 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/04 14:34:57 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_out_of_bounds(int x, int y)
{
	t_game	*game;

	game = ft_game();
	if (x < 0 || x >= game->map_width)
		return (true);
	if (y < 0 || y >= game->map_height)
		return (true);
	return (false);
}

double	get_wall_distance(t_ray *ray)
{
	double	distance;

	if (!ray || ray->hit == 0)
		return (-1);
	if (ray->side == 0)
		distance = (ray->delta.x - ray->next.x);
	else
		distance = (ray->delta.y - ray->next.y);
	return (distance);
}

int	get_wall_direction(t_ray *ray)
{
	if (!ray || ray->hit == 0)
		return (WALL_UNKNOWN);
	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			return (WALL_EAST);
		else
			return (WALL_WEST);
	}
	else
	{
		if (ray->dir.y > 0)
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
		wall_x = ray->cam.pos.y + ray->walls[ray->id].ray_dist * ray->dir.y;
	else
		wall_x = ray->cam.pos.x + ray->walls[ray->id].ray_dist * ray->dir.x;
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
	// printf("Ray direction X: %f\n", ray->dir.x);
	// printf("Ray direction Y: %f\n", ray->dir.y);
	// printf("Wall X: %f\n", wall->wall_x);
	// printf("Texture width: %d\n", wall->texture->image_data->width);
	tex_width = wall->texture->image_data->width;
	tex_x = (int)(wall->wall_x * tex_width);
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}
