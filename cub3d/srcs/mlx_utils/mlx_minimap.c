/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:49:52 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/07 12:42:02 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_minimap_pixel(int i, int j, t_coord player_pos)
{
	if (j == 0 || i == 0 || j == 160 || i == 160)
		my_pixel_put(&ft_game()->mlx->img, i, j, BLACK_COLOR);
	else if (is_valid(player_pos.y, player_pos.x, " \t\n\r\v\f\0"))
		my_pixel_put(&ft_game()->mlx->img, i, j, GREY_COLOR);
	else if (is_valid(player_pos.y, player_pos.x, "1"))
		my_pixel_put(&ft_game()->mlx->img, i, j, BLUE_COLOR);
	else if (is_valid(player_pos.y, player_pos.x, "D"))
		my_pixel_put(&ft_game()->mlx->img, i, j, BROWN_COLOR);
	else if (is_valid(player_pos.y, player_pos.x, "C"))
		my_pixel_put(&ft_game()->mlx->img, i, j, CYAN_COLOR);
	else
		my_pixel_put(&ft_game()->mlx->img, i, j, WHITE_COLOR);
}

static void	draw_player(void)
{
	int	px;
	int	py;

	px = 80;
	py = 80;
	my_pixel_put(&ft_game()->mlx->img, px, py, RED_COLOR);
	my_pixel_put(&ft_game()->mlx->img, px + 1, py, RED_COLOR);
	my_pixel_put(&ft_game()->mlx->img, px - 1, py, RED_COLOR);
	my_pixel_put(&ft_game()->mlx->img, px, py + 1, RED_COLOR);
	my_pixel_put(&ft_game()->mlx->img, px, py - 1, RED_COLOR);
}

void	draw_minimap(void)
{
	int		i;
	int		j;
	t_coord	curr_pos;
	t_coord	player_pos;

	curr_pos = ft_game()->ray.cam.pos;
	i = -1;
	while (++i <= 160)
	{
		player_pos.x = curr_pos.x - 5.0 + i * 10.0 / 160;
		j = -1;
		while (++j <= 160)
		{
			player_pos.y = curr_pos.y - 5.0 + j * 10.0 / 160;
			draw_minimap_pixel(i, j, player_pos);
		}
	}
	draw_player();
}
