/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:38:48 by fandre-b          #+#    #+#             */
/*   Updated: 2025/02/06 12:38:48 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
			draw_solid_line(i, wall->top, wall->bottom, RED_COLOR);
		}
		draw_solid_line(i, wall->bottom, HEIGHT, ft_game()->texture[4]->colour);
		i++;
	}
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
