/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:52:20 by fandre-b          #+#    #+#             */
/*   Updated: 2025/02/17 13:43:26 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	validate_position(int y, int x)
{
	if (ft_strchr("1 ", ft_game()->map[y][x]))
		return (true);
	if (is_valid(y - 1, x, " ") || is_valid(y + 1, x, " "))
		return (false);
	if (is_valid(y, x - 1, " ") || is_valid(y, x + 1, " "))
		return (false);
	return (true);
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
					return (ft_print_err("Invalid door position"));
		}
	}
}

void	check_map(char **map)
{
	t_game	*game;
	int		x;
	int		y;

	game = ft_game();
	y = -1;
	while (++y < game->map_height)
	{
		if (y > 0 && is_empty_line(map[y]))
			ft_print_err("Map: Empty line in map");
		x = -1;
		while (++x < game->map_width && map[y][x] != '\n' && map[y][x] != '\0')
		{
			if (!ft_strchr("10NWESDC ", map[y][x]))
				ft_print_err("Map: Invalid character in map");
			if (!validate_position(y, x))
				ft_print_err("Map: Of map encapsulation");
			if (!get_player_direction(y, x))
				ft_print_err("Map: Repeated player pos");
		}
	}
	if (is_valid(game->ctl.pos.y, game->ctl.pos.x, ""))
		ft_print_err("Map: No player position found");
	check_doors(game, map);
}

void	check_textures(t_game *game)
{
	int	y;

	if (!game)
		return ;
	y = 0;
	while (y < TEXTURE_SIZE && game->texture[y] != NULL)
		y++;
	if (y < 6)
		return (ft_print_err("File: Textures not loaded"));
	if (!game->door || !game->door->image_data)
		return (ft_print_err("File: Door texture not loaded"));
}
