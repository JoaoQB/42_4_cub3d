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

#include "cub3d.h"

void	draw_minimap_pixel(int i, int j, t_coord player_pos)
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
			if (i > 75 && i < 85 && j > 75 && j < 85)
				my_pixel_put(&ft_game()->mlx->img, i, j, RED_COLOR);
			else
				draw_minimap_pixel(i, j, player_pos);
		}
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
		if (ft_game()->ctl.fade)
			my_pixel_put_faded(x, y, color, wall->ray_dist);
		else
			my_pixel_put(&game->mlx->img, x, y, color);
		y++;
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
			draw_solid_line(i, wall->top, wall->bottom, wall->texture->colour);
		draw_solid_line(i, wall->bottom, HEIGHT, ft_game()->texture[4]->colour);
		i++;
	}
}
