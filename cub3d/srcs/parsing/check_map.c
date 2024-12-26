/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:52:20 by fandre-b          #+#    #+#             */
/*   Updated: 2024/12/26 21:46:19 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*file_to_str(char *file_name)
{
	char read_str[100];
	char *file_str;
	int bytes;
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	bytes = 1;
	file_str = NULL;
	while(bytes > 0)
	{
		memset(read_str, 0, 100);
		bytes = read(fd, read_str, 99);
		if (bytes == -1)
			return (free(file_str), NULL);
		if (bytes == 0)
			break;
		file_str = ft_strnjoin(file_str, read_str, -1);
	}
	close(fd);
	return (file_str);
}

e_direction get_direction_struct(const char *str)
{
	while (*str && ft_issapaces(*str))
		str++;
	if (ft_startswith(str, "NO") == 0)
		return NORTH;
	if (ft_startswith(str, "SO") == 0)
		return SOUTH;
	if (ft_startswith(str, "EA") == 0)
		return EAST;
	if (ft_startswith(str, "WE") == 0)
		return WEST;
	if (ft_startswith(str, "F") == 0)
		return FLOOR;
	if (ft_startswith(str, "C") == 0)
		return CEIL;
	return UNKNOWN;
}

bool get_player_direction(int y, int x)
{
	char c;

	c = ft_game()->map[y][x];
	if (!ft_strchr("NWES", c))
		return (true);
	if (ft_game()->player.angle != UNKNOWN)
		return (false);
	else if (c == 'N')
		ft_game()->player.angle = NORTH;
	else if (c == 'S')
		ft_game()->player.angle = SOUTH;
	else if (c == 'E')
		ft_game()->player.angle = EAST;
	else if (c == 'W')
		ft_game()->player.angle = WEST;
	else
	{
		ft_print_error("Invalid player direction");
		ft_game()->player.angle = UNKNOWN;
	}
	ft_game()->player.pos.x = x;
	ft_game()->player.pos.y = y;
	return (true);
}

void extract_textures(char **lines)
{
	int i;
	e_direction dir;
	char **words;

	i = -1;
	while (lines[++i] != NULL)
	{
		dir = get_direction_struct(lines[i]) / 90;
		if (ft_game()->texture[dir] != NULL)
			return(free(lines), ft_print_error("Duplicated texture line"));
		if (dir * 90 != UNKNOWN)
		{//dir is a valid dir
			if (ft_wordcount(lines[i], ' ') != 2)
				return(free(lines), ft_print_error("Invalid texture line"));
			words = ft_split(lines[i], ' ');
			ft_game()->texture[dir] = extract_info_process(words);
			free(words);
			free(lines[i]);
			lines[i] = ft_strdup("");
		}
	}
}

void		extract_map(char **lines)
{
	int i;
	char **map;

	ft_game()->player.angle = UNKNOWN;
	// ft_game()->map_height = 0;
	// ft_game()->map_width = 0;
	i = -1;
	while (lines[++i] != NULL)
	{
		if (ft_strlen(lines[i]) > ft_game()->map_width)
			ft_game()->map_width = ft_strlen(lines[i]);
		if (ft_strlen(lines[i]) > 0)
			ft_game()->map_height++;
	}
	map = (char **) my_calloc(ft_game()->map_height + 1, sizeof(char *));
	i = -1;
	while ((*lines) != NULL)
	{
		if (ft_strlen(*lines) > 0)
		{
			map[++i] = (char *) my_calloc(ft_game()->map_width + 1, sizeof(char));
			ft_strlcpy(map[i], *lines, ft_strlen(*lines) + 1);
		}
		lines++;
	}
	map[++i] = NULL;
	ft_game()->map = map;
}

void	check_map(char **map)
{
	int		x;
	int		y;

	if (ft_game()->map_height == 0 || ft_game()->map == NULL)
		return (ft_print_error("No map found"));
	y = -1;
	while (++y < ft_game()->map_height)
	{
		x = 0;
		while (x < ft_game()->map_width && map[y][x] != '\n' && map[y][x] != '\0')
		{
			if (!ft_strchr("1 0NWES", map[y][x]))
				ft_print_error("Invalid character in map");
			if (!validate_position(y, x))
			{
				printf	("y: %d, x: %d, char: %c\n", y, x, map[y][x]);
				ft_print_error("Of map encapsulation");
			}
			if (!get_player_direction(y, x))
				ft_print_error("Repeated player pos");
			x++;
		}
	}
}

bool		validate_position(int y, int x)
{
	if (ft_strchr(" 1", ft_game()->map[y][x]))
		return (true);
	if (!is_valid(y - 1, x, "01NWES") || !is_valid(y + 1, x, "01NWES"))
		return (false);
	if (!is_valid(y, x - 1, "01NWES") || !is_valid(y, x + 1, "01NWES"))
		return (false);
	//this also checks for diagonal walls
	// if (!is_valid(y - 1, x - 1, "01NWES") || !is_valid(y + 1, x + 1, "01NWES"))
	// 	return (false);
	// if (!is_valid(y - 1, x + 1, "01NWES") || !is_valid(y + 1, x - 1, "01NWES"))
	// 	return (false);
	return (true);
}

bool is_valid(int y, int x, char *valid_str)
{
	if (x < 0 || x >= ft_game()->map_width)
		return (true);
	if (y < 0 || y >= ft_game()->map_height)
		return (true);
	if (ft_strchr(valid_str, ft_game()->map[y][x]))
		return(true);
	return (false);
}
