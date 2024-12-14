/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:56:46 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/10 11:32:41 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_pixel_put(t_image *img, int x, int y, int colour)
{
	int	offset;

	offset = (y * img->len_line) + (x * (img->bpp / 8));
	*(unsigned int *)(img->addr + offset) = colour;
}

// TODO define WALL_TEXTURE for WALL_COLOR and change floor and ceiling colors
static void	draw_vertical_line(t_game *game, int x, int wall_top, int wall_bottom)
{
	int		y;
	t_image	img;

	if (!game)
		return ;
	img = game->mlx->img;
	y = 0;
	while (y < HEIGHT)
	{
		if (y >= wall_top && y <= wall_bottom)
			my_pixel_put(&img, x, y, WALL_COLOR);
		else if (y < wall_top)
			my_pixel_put(&img, x, y, CEILING_COLOR);
		else
			my_pixel_put(&img, x, y, FLOOR_COLOR);
		y++;
	}
}

void	draw_walls(t_game	*game)
{
	int	i;
	double	half_w_height;
	double	wall_top;
	double	wall_bottom;

	if (!game)
		return ;
	i = 0;
	while (i < WIDTH)
	{
		half_w_height = (game->ray.wall_height[i]) / 2;
		wall_top = game->ray.h_height - half_w_height;
		if (wall_top < 0)
			wall_top = 0;
		wall_bottom = game->ray.h_height + half_w_height;
		if (wall_bottom >= HEIGHT)
			wall_bottom = HEIGHT - 1;
		draw_vertical_line(game, i, wall_top, wall_bottom);
		i++;
	}
}