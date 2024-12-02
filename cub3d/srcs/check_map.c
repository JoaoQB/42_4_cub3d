/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:52:20 by fandre-b          #+#    #+#             */
/*   Updated: 2024/12/01 17:36:22 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

enum Direction get_direction(const char *str) {
	if (ft_strcmp(str, "NO") == 0) 
		return NORTH;
	if (ft_strcmp(str, "SO") == 0)
		return SOUTH;
	if (ft_strcmp(str, "EA") == 0) 
		return EAST;
	if (ft_strcmp(str, "WE") == 0) 
		return WEST;
	if (ft_strcmp(str, "F") == 0)
		return FLOOR;
	if (ft_strcmp(str, "C") == 0) 
		return CEIL;
	return UNKNOWN; // Invalid direction
}

void handle_

void	file_to_str(bool *fd, char **file_str)
{
	char *read_str;
	size_t bytes;
	int fd;
	//i got strjoin to join map with new read

	bytes = 1;
	*file_str = NULL;
	while(bytes > 0)
	{
		bytes = read(fd, read_str, 100);
		if (bytes == -1)
			return (free(file_str), NULL);
		if (bytes == 0)
			break;
		*file_str = ft_strnjoin(*file_str, read_str, bytes);
	}
	clear_empty_lines(file_str);
}

void clear_empty_lines(char *file_str)
{
	int i;

	i = -1;
	while (*file_str != '\0')
	{
		if (*file_str++ == '\n')
		{
			while (ft_is_spaces(file_str[++i]))
				;
			if (file_str[i] != '\n' || file_str[i] != '\0')
				remove_line(file_str ); //TODO remove line function
		}
	}
}

void remove_line(char *file_str)
{
	int j;
	int i;
	
	i = 0;
	//from start of line find EOF or \n
	while (file_str[i] != '\n' && file_str[i] != '\0')
		i++;
	j = -1;
	//from this new pos, shift all file <i> slots
	while (file_str[i + (++j)] != '\0')
		file_str[j] = file_str[i + j];
	file_str[j] = '\0';
}

void *extract_images(char *file_str)
{
	enum Direction dir;
	int i;
	struct s_panel *panel;

	i = -1;
	panel = NULL;
	while (file_str[i++] != '\0')
	{
		//run run full file. if there is an valid direction save line info
		//this might be bad,
		dir = get_direction(&file_str[i]);
		if (dir != UNKNOWN)
		{
			panel = malloc(sizeof(struct s_panel));
			panel->name = get_name(&file_str[i], i);
			panel->path = get_path(&file_str[i], i);
			panel->image_data = get_image_data(panel->path);
			panel->colour = get_colour(&file_str[i], i);
			ft_game()->direction[dir] = panel;
			panel = NULL;
			remove_line(&file_str[i], i);
		}
	}
}

bool		extract_map(char *file_str)
{
	int i;
	char **map;

	//slipe file by lines
	map = ft_split(file_str, '\n');
	map->height = -1;
	map->width = 0;
	//calc square size height and width
	while (map[++(map->height)] != '\0')
		if (map->width < ft_strlen(map[map->height]))
			map->width = ft_strlen(map[map->height]);
	//reconstruct the char** to have full square allocated
	ft_game()->map_s->map = calloc(map->height * sizeof(char *));
	i = -1;
	while (++i < map->height)
	{
		ft_game()->map_s->map[i] = calloc((map->width + 1) * sizeof(char));
		ft_strlcpy(map[i], map[i], map->width);
	}
	free(map);
}

bool		check_map(char *map)
{
	int		i;
	int		j;

	//verificar se no mapa existe algum caracter que nao seja 0, 1, 2, N, S, W, E, ' ', P, *valido
	i = =1;
	while (++i < map->height)
	{
		j = -1;
		//run the complete array, with ele_by_ele checks
		while (++j < map->width)
		{
			//for player position / then check for encapsulation
			if (ft_strchr("0NWES", map->map[i][j]))
				if (!validate_position(i, j, map))
					return (false);
			//for walls and spaces
			if (!ft_strchr(" 1", map->map[i][j]))
				return (false);
		}
	}
	return (true);
}

bool		validate_position(int y, int x)
{
	char *map;

	map = ft_game()->map->map;

	//check if element is contained in the map
	//flood fill intead or with recursive or with queue structure
	if (!is_valid(y - 1, x, "01NWES") || !is_valid(y + 1, x, "01NWES"))
		return (false); 
	if (!is_valid(y, x - 1, "01NWES") || !is_valid(y, x + 1, "01NWES"))
		return (false);
	if (!is_valid(y - 1, x - 1, "01NWES") || !is_valid(y + 1, x + 1, "01NWES"))
		return (false);
	if (!is_valid(y - 1, x + 1, "01NWES") || !is_valid(y + 1, x - 1, "01NWES"))
		return (false);
	return (true);
}

bool is_valid(int x, int y, char *valid_str)
{
	char *map;

	map = ft_game()->map;

	if (ft_strchr(valid_str, map[y][x]))
		return(true);
	return (false);
}


// WASD -> MOVE
// arrows -> camera
// mouse -> camera
// esq -> exit
// redcross -> exit

// space -> jump
// ctrl -> crouch
// shift -> run (change spd)
// tab -> show map
// m -> show menu

