/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:56:46 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/03 14:57:53 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(t_image *img, int x, int y, int colour)
{
	int	offset;

	offset = (y * img->len_line) + (x * (img->bpp / 8));
	*(unsigned int *)(img->addr + offset) = colour;
}

void	draw_solid_line(int x, int start, int end, int color)
{
	int		y;
	t_game	*game;

	y = start;
	game = ft_game();
	while (y < end)
	{
		my_pixel_put(&game->mlx->img, x, y, color);
		y++;
	}
}

// void	draw_vertical_line(t_game *game, int x)
// {
// 	int		y;
// 	t_image	img;
// 	t_wall	*wall;

// 	if (!game)
// 		return ;
// 	wall = &game->ray.walls[x];
// 	img = game->mlx->img;
// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		if (y >= wall->top && y <= wall->bottom)
// 			my_pixel_put(&img, x, y, COLOR);
// 		else if (y < wall->top)
// 			my_pixel_put(&img, x, y, ft_game()->texture[4]->colour);
// 		else
// 			my_pixel_put(&img, x, y, ft_game()->texture[5]->colour);
// 		y++;
// 	}
// }

void	draw_text_line(t_game *game, t_wall *wall, t_image *data, int x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	if (!game || !wall || !wall->texture || !data)
		return ;
	y = wall->top;
	step = 1.0 * data->height / (wall->bottom - y);
	tex_pos = (y - game->ray.cam.h_height + (wall->bottom - y) / 2) * step;
	while (y < wall->bottom)
	{
		tex_y = (int)tex_pos % data->height;
		if (tex_y < 0)
			tex_y += data->height;
		tex_pos += step;
		color = *(unsigned int *)(data->addr + tex_y * data->len_line
				+ wall->tex_x * (data->bpp / 8));
		my_pixel_put(&game->mlx->img, x, y, color);
		y++;
	}
}

void	draw_walls(t_game *game)
{
	int		i;
	t_wall	*wall;
	t_image	*image_data;

	if (!game)
		return ;
	i = 0;
	while (i < WIDTH)
	{
		wall = &game->ray.walls[i];
		draw_solid_line(i, 0, wall->top, ft_game()->texture[5]->colour);
		if (wall->texture && wall->texture->image_data)
		{
			image_data = wall->texture->image_data;
			draw_text_line(game, wall, image_data, i);
		}
		else
		{
			draw_solid_line(i, wall->top, wall->bottom, COLOR);
		}
		draw_solid_line(i, wall->bottom, HEIGHT, ft_game()->texture[4]->colour);
		i++;
	}
}
