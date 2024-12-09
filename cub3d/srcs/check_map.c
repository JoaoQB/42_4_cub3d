/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:52:20 by fandre-b          #+#    #+#             */
/*   Updated: 2024/12/08 15:17:18 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

enum Direction get_direction_struct(const char *str) {
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

void get_player_direction(const char *str)
{
	//i can set angle to NOT
	ft_game()->player->angle = UNKNOWN;	
	while (*str && ft_game()->player->angle != UNKNOWN)
	{
		if (ft_strcmp(str, "N") == 0)
			ft_game()->player->angle = NORTH;
		else if (ft_strcmp(str, "S") == 0)
			ft_game()->player->angle = SOUTH;
		else if (ft_strcmp(str, "E") == 0)
			ft_game()->player->angle = EAST;
		else if (ft_strcmp(str, "W") == 0)
			ft_game()->player->angle = WEST;
		else
			ft_game()->player->angle = UNKNOWN;
		str++;
	}
	//check if another player position was found
	while (*str && ft_game()->player->angle != UNKNOWN)
	{
		if (strchr("NSEW", *str++))
		{
			ft_game()->player->angle = UNKNOWN;
			return;	
		}
	}
}

char *	file_to_str(char *file_name)
{
	char read_str[100];
	char *file_str;
	int bytes;
	int fd;
	//i got strjoin to join map with new read

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	bytes = 1;
	file_str = NULL;
	while(bytes > 0)
	{
		bytes = read(fd, read_str, 100);
		if (bytes == -1)
			return (free(file_str), NULL);
		if (bytes == 0)
			break;
		file_str = ft_strnjoin(file_str, read_str, bytes);
	}
	clear_empty_lines(file_str);
	return (file_str);
}

void clear_empty_lines(char *file_str)
{
	int i;

	i = -1;
	while (*file_str != '\0')
	{
		if (*file_str++ == '\n')
		{
			while (ft_issapaces(file_str[++i]))
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

void extract_images(char *file_str)
{
	enum Direction dir;
	int i;
	t_texture *panel;

	i = -1;
	panel = NULL;
	while (file_str[i++] != '\0')
	{
		//run run full file. if there is an valid direction save line info
		//this might be bad,
		get_player_direction(&file_str[i]);
		dir = ft_game()->player->angle;
		if (dir != UNKNOWN)
		{
			panel = (t_texture *) my_calloc(1, sizeof(t_texture *));
			panel->image_name = get_name(&file_str[i], i);
			panel->image_path = get_path(&file_str[i], i);
			panel->image_data = (t_image *) my_calloc(1, sizeof(t_image));
			panel->image_data = xpm_to_binary(panel->image_path);
			panel->colour = get_colour(&file_str[i], i);
			ft_game()->texture[dir] = *panel;
			panel = NULL;
			remove_line(&file_str[i]);
		}
	}
}

char *get_name(const char *str, int i)
{
	int j;
	char *name;

	j = 0;
	while (str[i + j] != ' ')
		j++;
	name = (char *) my_calloc(j, sizeof(char));
	ft_strlcpy(name, &str[i], j);
	return (name);
}

char *get_path(const char *str, int i)
{
	int j;
	char *path;

	j = 0;
	while (str[i + j] != ' ')
		j++;
	path = (char *) my_calloc(j, sizeof(char));
	ft_strlcpy(path, &str[i], j);
	return (path);
}

int get_colour(const char *str, int i)
{
	int j;
	int colour;

	j = 0;
	while (str[i + j] != ' ')
		j++;
	colour = ft_atoi(&str[i]);
	return (colour);
}

void		extract_map(char *file_str)
{
	int i;
	char **map;

	//slipe file by lines
	map = ft_split(file_str, '\n');
	ft_game()->map_height = -1;
	ft_game()->map_width = 0;
	//calc square size height and width
	while (map[++(ft_game()->map_height)])
		if (ft_game()->map_width < ft_strlen(map[ft_game()->map_height]))
			ft_game()->map_width = ft_strlen(map[ft_game()->map_height]);
	//reconstruct the char** to have full square allocated
	ft_game()->map = (char **) my_calloc(ft_game()->map_height, sizeof(char *));
	i = -1;
	while (++i < ft_game()->map_height)
	{
		ft_game()->map[i] = (char *) my_calloc(ft_game()->map_width + 1, sizeof(char));
		ft_strlcpy(map[i], map[i], ft_game()->map_width);
	}
	free(map);
}

bool		check_map(char **map)
{
	int		i;
	int		j;

	//verificar se no mapa existe algum caracter que nao seja 0, 1, 2, N, S, W, E, ' ', P, *valido
	i = -1;
	while (++i < ft_game()->map_height)
	{
		j = -1;
		//run the complete array, with ele_by_ele checks
		while (++j < ft_game()->map_width)
		{
			//for player position / then check for encapsulation
			if (ft_strchr("0NWES", map[i][j]))
				if (!validate_position(i, j))
					return (false);
			//for walls and spaces
			if (!ft_strchr(" 1", map[i][j]))
				return (false);
		}
	}
	return (true);
}

bool		validate_position(int y, int x)
{
			// char *map;

			// map = ft_game()->map;

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
	char **map;

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

