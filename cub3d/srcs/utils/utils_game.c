/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:03:52 by fandre-b          #+#    #+#             */
/*   Updated: 2025/02/09 16:03:52 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	ret;

	if (!str)
		return ;
	ret = write(fd, str, ft_strlen(str));
	(void)ret;
}

void	ft_print_err(char *str)
{
	ft_putstr_fd("\n\nError: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	free_game();
	exit(1);
}

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

bool	is_door_valid(char **map, int y, int x)
{
	if (!map)
		return (false);
	if (is_out_of_bounds(x, y))
		return (false);
	if (is_out_of_bounds(x - 1, y) || is_out_of_bounds(x + 1, y)
		|| is_out_of_bounds(x, y - 1) || is_out_of_bounds(x, y + 1))
		return (false);
	if ((map[y][x - 1] == '1' && map[y][x + 1] == '1')
		|| (map[y - 1][x] == '1' && map[y + 1][x] == '1'))
		return (true);
	return (false);
}

bool	is_out_of_bounds(int x, int y)
{
	t_game	*game;

	game = ft_game();
	if (x < 0 || x >= game->map_width)
		return (true);
	if (y < 0 || y >= game->map_height)
		return (true);
	return (false);
}
