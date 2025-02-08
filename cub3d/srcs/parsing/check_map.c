/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:52:20 by fandre-b          #+#    #+#             */
/*   Updated: 2025/02/08 18:25:26 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// BONUS CHANGE ADDED D
bool	validate_position(int y, int x)
{
	if (ft_strchr("1 ", ft_game()->map[y][x]))
		return (true);
	// tem de validar
	if (is_valid(y - 1, x, " ") || is_valid(y + 1, x, " "))
		return (false);
	if (is_valid(y, x - 1, " ") || is_valid(y, x + 1, " "))
		return (false);
	return (true);
}

//TODO rename
bool	is_valid(int y, int x, char *valid_str)
{
	if (is_out_of_bounds(x, y))
		return (true);
	if (ft_game()->map[y][x] == '\0')
		return (true);
	if (ft_strchr(valid_str, ft_game()->map[y][x]))
		return (true);
	return (false);
}

bool	is_empty_line(char *line)
{
	int i;

	if (!line)
		return (true);
	i = 0;
	while (line[i] && ft_strchr(" \t\r\v\f", line[i]))
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (true);
	return (false);
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
