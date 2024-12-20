/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:32:26 by fandre-b          #+#    #+#             */
/*   Updated: 2024/12/14 18:31:09 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(int offset_x, int offset_y)
{
	int x;
	int y;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
			draw_by_scale(x, y, MINIMAP_SCALE, offset_x, offset_y);
			//i can pass an structure of object to be drawn instead like
			//with map dimentions, rescale, offset(pos) and image dimension
	}
}

void draw_by_scale(int x, int y, int scale, int offset_x, int offset_y) 
{
	int i;
	int j;
	int color;

	i = x * scale + offset_x;
	while (i < (x + 1) * scale + offset_x)
	{
		j = y * scale + offset_y;
		while (j < (y + 1) * scale + offset_y)
		{
			color = ft_game()->map[y][x] == 1 ? 0x00FF00 : 0x000000;
			my_pixel_put(&ft_game()->mlx->img, i, j, color);
			j++;
		}
		i++;
	}
}