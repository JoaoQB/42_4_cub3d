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

#include "cub3d_bonus.h"

void	extract_map(t_game *game, char **lines)
{
	int		i;
	char	**map;

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

void	extract_textures(char **lines)
{
	int			i;
	t_direction	dir;
	char		**words;

	i = -1;
	while (lines[++i] != NULL)
	{
		lines[i] = ft_strtrim(lines[i], "\n");
		dir = get_direction_struct(lines[i]) / 90;
		if (dir == TEXTURE_SIZE)
			break ;
		if (ft_game()->texture[dir] != NULL)
			return (free_frases(lines), ft_print_err("Duplicated texture"));
		if (dir != TEXTURE_SIZE)
		{
			if (ft_wordcount(lines[i], ' ') != 2)
				return (free_frases(lines), ft_print_err("Invalid texture"));
			words = ft_split(lines[i], ' ');
			ft_game()->texture[dir] = extract_info_process(words);
			free_frases(words);
			free(lines[i]);
			lines[i] = ft_strdup("");
		}
	}
}

t_texture	*extract_info_process(char **words)
{
	t_texture	*texture;
	int			i;

	i = -1;
	while (words[++i])
		;
	if (i != 2)
		ft_print_err("Textures: Invalid texture format");
	texture = (t_texture *) my_calloc(1, sizeof(t_texture));
	texture->image_name = ft_strtrim(ft_strdup(words[0]), " \n\t\v\f\r");
	texture->image_path = ft_strtrim(ft_strdup(words[1]), " \n\t\v\f\r");
	return (texture);
}
