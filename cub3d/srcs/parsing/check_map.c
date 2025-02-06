/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:52:20 by fandre-b          #+#    #+#             */
/*   Updated: 2025/02/04 18:52:13 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// BONUS CHANGE ADDED D
bool	validate_position(int y, int x)
{
	if (ft_strchr("1", ft_game()->map[y][x]))
		return (true);
	if (is_valid(y - 1, x, "") || is_valid(y + 1, x, ""))
		return (false);
	if (is_valid(y, x - 1, "") || is_valid(y, x + 1, ""))
		return (false);
	return (true);
}

bool	is_valid(int y, int x, char *valid_str)
{ //TODO rename
	if (is_out_of_bounds(x, y))
		return (true);
	if (ft_game()->map[y][x] == '\0')
		return (true);
	if (ft_strchr(valid_str, ft_game()->map[y][x]))
		return (true);
	return (false);
}

void	check_map(char **map)
{
	t_game	*game;
	int		x;
	int		y;

	game = ft_game();
	if (map == NULL || game->map_height == 0)
		return (ft_print_error("File: No map found"));
	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width && map[y][x] != '\n' && map[y][x] != '\0')
		{
			if (!ft_strchr("10NWESDC", map[y][x]))
				ft_print_error("Map: Invalid character in map");
			if (!validate_position(y, x))
				ft_print_error("Map: Of map encapsulation");
			if (!get_player_direction(y, x))
				ft_print_error("Map: Repeated player pos");
		}
	}
	if (is_valid(game->ctl.pos.y, game->ctl.pos.x, ""))
		ft_print_error("Map: No player position found");
	check_doors(game, map);
}

void	check_textures(t_game *game)
{
	int	y;

	if (!game)
		return ;
	// print_all_textures(game);
	y = 0;
	while (y < TEXTURE_SIZE && game->texture[y] != NULL)
	{
		// printf("%d\n", y);
		// printf("Texture pointer: %p\n", (void *)game->texture[y]);
		y++;
	}
	// printf("Final y value: %d\n", y);
	if (y < 6)
	{
		// printf("Y: %d, TEXTURE_SIZE: %d\n", y, TEXTURE_SIZE);
		return (ft_print_error("File: Textures not loaded"));
	}
	if (!game->door || !game->door->image_data)
	{
		return (ft_print_error("File1: Door texture not loaded"));
	}
}