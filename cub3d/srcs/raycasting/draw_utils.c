/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:56:46 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/01/02 22:00:48 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(t_image *img, int x, int y, int colour)
{
	int	offset;

	offset = (y * img->len_line) + (x * (img->bpp / 8));
	*(unsigned int *)(img->addr + offset) = colour;
}

void	draw_solid_line(t_game *game, int x, int start, int end, int color)
{
	int	y;

	y = start;
	while (y < end)
	{
		my_pixel_put(&game->mlx->img, x, y, color);
		y++;
	}
}

void	draw_vertical_line(t_game *game, int x)
{
	int		y;
	t_image	img;
	t_wall	*wall;

	if (!game)
		return ;
	wall = &game->ray.walls[x];
	img = game->mlx->img;
	y = 0;
	while (y < HEIGHT)
	{
		if (y >= wall->top && y <= wall->bottom)
			my_pixel_put(&img, x, y, COLOR);
		else if (y < wall->top)
			my_pixel_put(&img, x, y, CEILING_COLOR);
		else
			my_pixel_put(&img, x, y, FLOOR_COLOR);
		y++;
	}
}

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

// TODO: Always draw color from texture struct.
// 			Ceiling and floor color must be there defined.
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
		draw_solid_line(game, i, 0, wall->top, CEILING_COLOR);
		if (wall->texture)
		{
			image_data = wall->texture->image_data;
			draw_text_line(game, wall, image_data, i);
		}
		else
		{
			draw_solid_line(game, i, wall->top, wall->bottom, COLOR);
		}
		draw_solid_line(game, i, wall->bottom, HEIGHT, FLOOR_COLOR);
		i++;
	}
}
