/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:32:26 by fandre-b          #+#    #+#             */
/*   Updated: 2024/12/11 15:33:09 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	init_mlx()
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, \
	&mlx->img.len_line, &mlx->img.endian);
	ft_game()->mlx = mlx;
	return ;
}

void	my_pixel_put(t_image *img, int x, int y, int colour)
{
	int	offset;

	offset = (y * img->len_line) + (x * (img->bpp / 8));
	*(unsigned int *)(img->addr + offset) = colour;
}

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