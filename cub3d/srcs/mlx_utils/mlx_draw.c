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

void	draw_minimap(int offset_x, int offset_y)
{
	int		i;
	int		j;
	t_coord	player_pos;
	t_coord	curr_pos;

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
