/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:05:53 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/04 15:26:29 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_door_valid(char **map, int y, int x)
{
	if (!map)
		return (false);
	if (is_out_of_bounds(x, y))
			return (false);
	if (is_out_of_bounds(x - 1, y) || is_out_of_bounds(x + 1, y)
		|| is_out_of_bounds(x, y - 1) || is_out_of_bounds(x, y + 1))
		return (false);
	if ((map[y][x - 1] == '1' && map[y][x + 1] == '1')
		|| (map[y - 1][x] == '1' && map[y + 1][x] == '1'))
		return (true);
	return (false);
}

void	check_doors(t_game *game, char **map)
{
	int	x;
	int	y;

	if (!game || !map)
		return ;
	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width && map[y][x] != '\n' && map[y][x] != '\0')
		{
			if (map[y][x] == 'D' || map[y][x] == 'C')
				if (!is_door_valid(map, y, x))
					return (ft_print_error("Invalid door position"));
		}
	}
}

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
	if (dist > COLISION * 2)
		return ;
	if (is_valid(y, x, "D"))
		game->map[y][x] = 'C';
	else if (is_valid(y, x, "C"))
		game->map[y][x] = 'D';
}
