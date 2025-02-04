/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:52:20 by fandre-b          #+#    #+#             */
/*   Updated: 2025/02/04 15:32:13 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_direction	get_direction_struct(const char *str)
{
	while (*str && ft_isspaces(*str))
		str++;
	if (ft_startswith(str, "NO") == 0)
		return (NORTH);
	if (ft_startswith(str, "SO") == 0)
		return (SOUTH);
	if (ft_startswith(str, "EA") == 0)
		return (EAST);
	if (ft_startswith(str, "WE") == 0)
		return (WEST);
	if (ft_startswith(str, "F") == 0)
		return (FLOOR);
	if (ft_startswith(str, "C") == 0)
		return (CEIL);
	return (UNKNOWN);
}

bool	get_player_direction(int y, int x)
{
	char	c;

	c = ft_game()->map[y][x];
	if (!ft_strchr("NWES", c))
		return (true);
	if (ft_game()->ctl.angle != UNKNOWN)
		return (false);
	else if (c == 'N')
		ft_game()->ctl.angle = NORTH;
	else if (c == 'S')
		ft_game()->ctl.angle = SOUTH;
	else if (c == 'E')
		ft_game()->ctl.angle = EAST;
	else if (c == 'W')
		ft_game()->ctl.angle = WEST;
	else
		ft_print_error("Invalid player direction");
	ft_game()->ctl.pos.x = x + 0.5;
	ft_game()->ctl.pos.y = y + 0.5;
	return (true);
}

void	extract_textures(char **lines)
{
	int			i;
	t_direction	dir;
	char		**words;

	i = -1;
	while (lines[++i] != NULL)
	{
		dir = get_direction_struct(lines[i]) / 90;
		if (dir == TEXTURE_SIZE)
			break ;
		if (ft_game()->texture[dir] != NULL)
			return (free_frases(lines), ft_print_error("Duplicated texture line"));
		if (dir != TEXTURE_SIZE)
		{
			if (ft_wordcount(lines[i], ' ') != 2)
				return (free_frases(lines), ft_print_error("Invalid texture line"));
			words = ft_split(lines[i], ' ');
			ft_game()->texture[dir] = extract_info_process(words);
			free_frases(words);
			free(lines[i]);
			lines[i] = ft_strdup("");
		}
	}
}

void	extract_map(t_game *game, char **lines)
{
	int		i;
	char	**map;

	if (!game)
		return ;
	game->ctl.angle = UNKNOWN;
	i = -1;
	while (lines[++i] != NULL)
	{
		if (ft_strlen(lines[i]) > game->map_width)
			game->map_width = ft_strlen(lines[i]);
		if (ft_strlen(lines[i]) > 0)
			game->map_height++;
	}
	map = (char **) my_calloc(game->map_height + 1, sizeof(char *));
	i = -1;
	while ((*lines) != NULL)
	{
		if (ft_strlen(*lines) > 0)
		{
			map[++i] = (char *)my_calloc(game->map_width + 1, sizeof(char));
			ft_strlcpy(map[i], *lines, ft_strlen(*lines) + 1);
		}
		lines++;
	}
	map[++i] = NULL;
	game->map = map;
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
			if (!ft_strchr("1 0NWESDC", map[y][x]))
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
