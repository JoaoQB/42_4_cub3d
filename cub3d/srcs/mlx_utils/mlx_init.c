/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:32:26 by fandre-b          #+#    #+#             */
/*   Updated: 2025/02/03 13:43:21 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(int offset_x, int offset_y)
{
	t_coord	player_pos;
	t_coord	curr_pos;
	int i;
	int j;

	(void)offset_x;
	(void)offset_y;
	curr_pos = ft_game()->ray.cam.pos;
	// player_pos.x = curr_pos.x - 5;
	//get player position
	//get min of height and width //set default 1600 for now
	//get scale factor = min * MINIMAP_SCALE // 1600 * 0.1 = 160 for now
	//draw 5x5 square around player position //im using float
	// since i have 160 pixels for 5 squares, i have 16 pixels for each square
	// float_step = 5 / 160 = 0.0625 // for the check_map for each pixel
	// while (player_pos.x < curr_pos.x + 5)
	i = -1;
	while (++i <= 160)
	{
		player_pos.x = curr_pos.x - 5.0 + i * 10.0 / 160;
		j = -1;
		while (++j <= 160)
		{
			player_pos.y = curr_pos.y - 5.0 + j * 10.0 / 160;
			if (j == 0 || i == 0 || j == 160 || i == 160)
				my_pixel_put(&ft_game()->mlx->img, i, j, BLACK_COLOR);
			else if (is_valid(player_pos.y, player_pos.x, "\n\0")) // out of map
				my_pixel_put(&ft_game()->mlx->img, i, j, GREY_COLOR);
			else if (is_valid(player_pos.y, player_pos.x, "1")) // wall
				my_pixel_put(&ft_game()->mlx->img, i, j, BLUE_COLOR);
			else if (is_valid(player_pos.y, player_pos.x, "D")) // door
				my_pixel_put(&ft_game()->mlx->img, i, j, BROWN_COLOR);
			else if (is_valid(player_pos.y, player_pos.x, "C")) // empty space
				my_pixel_put(&ft_game()->mlx->img, i, j, CYAN_COLOR);
			else
				my_pixel_put(&ft_game()->mlx->img, i, j, WHITE_COLOR);
		}
	}
	//draw pov left and right rays
	// flood fill the map encapulated by the rays
	
}
