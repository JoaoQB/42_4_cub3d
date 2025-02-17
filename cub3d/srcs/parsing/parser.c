/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:42:35 by fandre-b          #+#    #+#             */
/*   Updated: 2025/02/06 12:42:35 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_dimensions(char **lines)
{
	int		i;

	i = -1;
	while (lines[++i] != NULL)
	{
		if (ft_strlen(lines[i]) > ft_game()->map_width)
			ft_game()->map_width = ft_strlen(lines[i]);
		if (ft_strlen(lines[i]) > 0)
			ft_game()->map_height++;
	}
}

void	clear_empty_lines_end(char **lines)
{
	int		i;

	i = 0;
	while (lines[i] != NULL)
		i++;
	while (--i >= 0)
	{
		printf("line: %s\n", lines[i]);
		printf("empty: %d\n", is_empty_line(lines[i]));
		if (is_empty_line(lines[i]) == 1)
			free(lines[i]);
		else
			break;
		lines[i] = NULL;
	}
}

void	extract_map(t_game *game, char **lines)
{
	int		i;
	char	**map;

	clear_empty_lines_end(lines);
	get_map_dimensions(lines);
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
	if (map == NULL || game->map_height == 0)
		return (ft_print_err("File: No map found"));
	game->map = map;
}

t_texture	*extract_info_process(char *line)
{
	t_texture	*texture;
	char		**words;

	if (ft_wordcount(line, ' ') != 2)
		return (NULL);
	words = ft_split(line, ' ');
	texture = (t_texture *) my_calloc(1, sizeof(t_texture));
	texture->image_name = ft_strtrim(ft_strdup(words[0]), " \n\t\v\f\r");
	texture->image_path = ft_strtrim(ft_strdup(words[1]), " \n\t\v\f\r");
	free_frases(words);
	return (texture);
}

void	extract_textures(char **lines)
{
	t_direction	dir;
	int			i;

	i = -1;
	while (lines[++i] != NULL)
	{
		lines[i] = ft_strtrim(lines[i], "\n");
		if (is_empty_line(lines[i]))
		{
			lines[i] = ft_strtrim(lines[i], " \n\t\v\f\r");
			continue ;
		}
		dir = get_direction_struct(lines[i]) / 90;
		if (dir == TEXTURE_SIZE)
			break ;
		else if (ft_game()->texture[dir] != NULL)
			return (free_frases(lines), ft_print_err("Duplicated texture"));
		ft_game()->texture[dir] = extract_info_process(lines[i]);
		if (!ft_game()->texture[dir])
			return (free_frases(lines), ft_print_err("Invalid texture"));
		free(lines[i]);
		lines[i] = ft_strdup("");
	}
}
