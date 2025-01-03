/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:29:54 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/31 13:32:51 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*file_to_str(char *file_name)
{
	char	read_str[100];
	char	*file_str;
	int		bytes;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	bytes = 1;
	file_str = NULL;
	while (bytes > 0)
	{
		memset(read_str, 0, 100);
		bytes = read(fd, read_str, 99);
		if (bytes == -1)
			return (free(file_str), NULL);
		if (bytes == 0)
			break ;
		file_str = ft_strnjoin(file_str, read_str, -1);
	}
	close(fd);
	return (file_str);
}

bool	validate_position(int y, int x)
{
	if (ft_strchr(" 1", ft_game()->map[y][x]))
		return (true);
	if (!is_valid(y - 1, x, "01NWES") || !is_valid(y + 1, x, "01NWES"))
		return (false);
	if (!is_valid(y, x - 1, "01NWES") || !is_valid(y, x + 1, "01NWES"))
		return (false);
	//this also checks for diagonal walls
	// if (!is_valid(y - 1, x - 1, "01NWES")
		// || !is_valid(y + 1, x + 1, "01NWES"))
	// 	return (false);
	// if (!is_valid(y - 1, x + 1, "01NWES")
		// || !is_valid(y + 1, x - 1, "01NWES"))
	// 	return (false);
	return (true);
}

bool	is_valid(int y, int x, char *valid_str)
{
	if (x < 0 || x >= ft_game()->map_width)
		return (true);
	if (y < 0 || y >= ft_game()->map_height)
		return (true);
	if (ft_strchr(valid_str, ft_game()->map[y][x]))
		return (true);
	return (false);
}
