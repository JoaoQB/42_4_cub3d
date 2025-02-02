/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:32:26 by fandre-b          #+#    #+#             */
/*   Updated: 2025/02/01 14:18:55 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	draw_minimap(int offset_x, int offset_y)
// {
// 	int	x;
// 	int	y;

// 	x = -1;
// 	while (++x < WIDTH)
// 	{
// 		y = -1;
// 		while (++y < HEIGHT)
// 			draw_by_scale(x, y, offset_x, offset_y);
// 			//i can pass an structure of object to be drawn instead like
// 			//with map dimentions, rescale, offset(pos) and image dimension
// 	}
// }

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
				my_pixel_put(&ft_game()->mlx->img, i, j, GREEN_COLOR);
			else if (is_valid(player_pos.y, player_pos.x, "1")) // wall
				my_pixel_put(&ft_game()->mlx->img, i, j, BLUE_COLOR);
			else
				my_pixel_put(&ft_game()->mlx->img, i, j, WHITE_COLOR);
		}
	}
	//draw pov left and right rays
	// flood fill the map encapulated by the rays
	
}


// jqueijo: Hardcoded MINIMAP_SCALE as function had too many parameters
void	draw_by_scale(int x, int y, int offset_x, int offset_y)
{
	int	i;
	int	j;
	int	color;

	i = x * MINIMAP_SCALE + offset_x;
	while (i < (x + 1) * MINIMAP_SCALE + offset_x)
	{
		j = y * MINIMAP_SCALE + offset_y;
		while (j < (y + 1) * MINIMAP_SCALE + offset_y)
		{
			if (ft_game()->map[y][x] == 1)
				color = 0x00FF00;
			else
				color = 0x000000;
			my_pixel_put(&ft_game()->mlx->img, i, j, color);
			j++;
		}
		i++;
	}
}
