/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:29:54 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/07 11:12:06 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*file_to_str(char *file_name)
{
	char	read_str[100];
	char	*file_str;
	int		bytes;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_print_err("Error opening file");
	bytes = 1;
	file_str = NULL;
	while (bytes > 0)
	{
		ft_memset(read_str, 0, 100);
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
		ft_print_err("Invalid player direction");
	ft_game()->ctl.pos.x = x + 0.5;
	ft_game()->ctl.pos.y = y + 0.5;
	return (true);
}

void	export_textures(t_texture *texture)
{
	if (texture)
	{
		texture->image_data = xpm_to_binary(texture->image_path);
		if (texture->image_data == NULL)
		{
			texture->colour = get_colour(texture->image_path);
			if (texture->colour == -1)
				ft_print_err("File: Failed to load image or colour\n");
		}
	}
	else
		ft_print_err("File: Failed to load image or colour\n");
}
