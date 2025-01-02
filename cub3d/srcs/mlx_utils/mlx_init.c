/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:32:26 by fandre-b          #+#    #+#             */
/*   Updated: 2025/01/02 20:39:43 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(int offset_x, int offset_y)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
			draw_by_scale(x, y, offset_x, offset_y);
			//i can pass an structure of object to be drawn instead like
			//with map dimentions, rescale, offset(pos) and image dimension
	}
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
