/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:05:53 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/03 20:31:27 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	door_switch(t_game *game)
{
	int			x;
	int			y;
	int			dist;
	static bool	toggle;

	toggle = !toggle;
	if (!toggle)
		return ;
	game->ray.id = (WIDTH / 2) -1;
	cast_ray(game, &game->ray, "DC1");
	x = game->ray.grid_x;
	y = game->ray.grid_y;
	dist = (int)game->ray.walls[game->ray.id].ray_dist;
	if (dist < COLISION || dist > 1)
		return ;
	if (is_valid(y, x, "D"))
		game->map[y][x] = 'C';
	else if (is_valid(y, x, "C"))
		game->map[y][x] = 'D';
}
