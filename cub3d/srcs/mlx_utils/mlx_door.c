/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:05:53 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/02 18:25:31 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// BONUS FUNCTIONS DOOR
t_direction	get_direction()
{
	t_cam	*cam;

	cam = &ft_game()->ray.cam;
	if (cam->dir.y >= 0.8 && cam->dir.y <= 1)
	{
		// printf("looking south\n");
		return (SOUTH);
	}
	if (cam->dir.y <= -0.8 && cam->dir.y >= -1)
	{
		// printf("looking north\n");
		return (NORTH);
	}
	if (cam->dir.x <= -0.8 && cam->dir.x >= -1)
	{
		// printf("looking west\n");
		return (WEST);
	}
	if (cam->dir.x >= 0.8 && cam->dir.x <= 1)
	{
		// printf("looking EAST\n");
		return (EAST);
	}
	return (UNKNOWN);
}

void	door_switch(t_game *game)
{
	t_coord		door;
	t_direction	direction;
	int			x;
	int			y;

	door = get_coord(game->ray.cam.pos);
	direction = get_direction();
	if (direction == UNKNOWN)
		return ;
	// printf("x: %f, y: %f\n", door.x, door.y);
	// printf("dir x: %f, dir y: %f\n", game->ray.cam.dir.x, game->ray.cam.dir.y);
	if (direction == NORTH)
		door.y -= 1;
	else if (direction == SOUTH)
		door.y += 1;
	else if (direction == WEST)
		door.x -= 1;
	else if (direction == EAST)
		door.x += 1;
	x = (int)door.x;
	y = (int)door.y;
	// printf("x: %d, y: %d\n", x, y);
	if (x < 0 || x > game->map_width || y < 0 || y > game->map_height)
	// {
		// printf("Door is out of bounds\n");
		return ;
	// }
	if (game->map[y][x] == 'D')
		game->map[y][x] = 'C';
	else if (game->map[y][x] == 'C')
		game->map[y][x] = 'D';
}
