/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:56:46 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/31 11:09:03 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(t_image *img, int x, int y, int colour)
{
	int	offset;

	offset = (y * img->len_line) + (x * (img->bpp / 8));
	*(unsigned int *)(img->addr + offset) = colour;
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
		if (y >= wall->wall_top && y <= wall->wall_bottom)
			my_pixel_put(&img, x, y, COLOR);
		else if (y < wall->wall_top)
			my_pixel_put(&img, x, y, CEILING_COLOR);
		else
			my_pixel_put(&img, x, y, FLOOR_COLOR);
		y++;
	}
}

void	draw_textured_line(t_game *game, t_wall *wall, int x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	if (!game || !wall || !wall->texture || !wall->texture->image_data)
	{
		draw_vertical_line(game, x);
		return ;
	}
	y = wall->wall_top;
	step = 1.0 * wall->texture->image_data->height / (wall->wall_bottom - y);
	tex_pos = (y - game->ray.cam.hHeight + (wall->wall_bottom - y) / 2) * step;
	while (y < wall->wall_bottom)
	{
		tex_y = (int)tex_pos % wall->texture->image_data->height;
		if (tex_y < 0)
			tex_y += wall->texture->image_data->height;
		tex_pos += step;
		color = *(unsigned int *)(wall->texture->image_data->addr + tex_y * wall->texture->image_data->len_line + wall->tex_x * (wall->texture->image_data->bpp / 8));
		my_pixel_put(&game->mlx->img, x, y, color);
		y++;
	}
}

void	draw_walls(t_game *game)
{
	int		i;
	t_wall	*wall;

	if (!game)
		return ;
	i = 0;
	while (i < WIDTH)
	{
		wall = &game->ray.walls[i];
		draw_textured_line(game, wall, i);
		i++;
	}
}
