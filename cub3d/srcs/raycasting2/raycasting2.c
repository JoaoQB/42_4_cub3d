/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:05:50 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/16 15:13:48 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	ray2_cast(t_game *game, t_ray *ray, int ray_id)
{

	if (!game || !ray)
		return (-1);
	ray->hit = 0;
	ray->camX = 2 * ray_id / ray->width - 1;
	printf("ray_id_%d: camX = %f (normalized ray position on camera plane)\n", ray_id, ray->camX);

	ray->rayDirX = ray->cam.dir.x + ray->cam.plane.x * ray->camX;
	ray->rayDirY = ray->cam.dir.y + ray->cam.plane.y * ray->camX;
	printf("ray_id_%d: Final Direction Vector (rayDirX: %f, rayDirY: %f)\n",
		ray_id, ray->rayDirX, ray->rayDirY);

	ray->gridX = (int)ray->cam.pos.x;
	ray->gridY = (int)ray->cam.pos.y;
	printf("ray_id_%d: Starting grid position -> gridX: %d, gridY: %d\n", ray_id, ray->gridX, ray->gridY);
	if (ray->rayDirX == 0)
		ray->rayNextX = 1e30;
	else
		ray->rayNextX = fabs(1 / ray->rayDirX);
	printf("ray_id_%d: rayNextX = %f (distance between vertical grid lines)\n", ray_id, ray->rayNextX);
	if (ray->rayDirY == 0)
		ray->rayNextY = 1e30;
	else
		ray->rayNextY = fabs(1 / ray->rayDirY);
	printf("ray_id_%d: rayNextY = %f (distance between horizontal grid lines)\n", ray_id, ray->rayNextY);

	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->rayFirstX = (ray->cam.pos.x - ray->gridX) * ray->rayNextX;
	}
	else
	{
		ray->stepX = 1;
		ray->rayFirstX = (ray->gridX + 1 - ray->cam.pos.x) * ray->rayNextX;
	}
	printf("ray_id_%d: stepX = %d, rayFirstX = %f\n", ray_id, ray->stepX, ray->rayFirstX);

	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->rayFirstY = (ray->cam.pos.y - ray->gridY) * ray->rayNextY;
	}
	else
	{
		ray->stepY = 1;
		ray->rayFirstY = (ray->gridY + 1 - ray->cam.pos.y) * ray->rayNextY;
	}
	printf("ray_id_%d: stepY = %d, rayFirstY = %f\n", ray_id, ray->stepY, ray->rayFirstY);
	return (0);
}

void	raycasting2()
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
		ray->ray_dist[i] = ray2_cast(game, ray, i);
		i++;
	}
	draw_walls(game);
}
