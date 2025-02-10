/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control_toggle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:34:03 by fandre-b          #+#    #+#             */
/*   Updated: 2025/02/09 18:34:03 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	toggle_mouse(void)
{
	t_game		*game;
	static bool	hidden;

	game = ft_game();
	if (hidden)
	{
		mlx_mouse_show(game->mlx->mlx, game->mlx->win);
	}
	else
	{
		mlx_mouse_hide(game->mlx->mlx, game->mlx->win);
	}
	hidden = !hidden;
}

void	toggle_fade(void)
{
	t_game		*game;
	static bool	fading;

	game = ft_game();
	if (fading)
		game->ctl.fade = 0;
	else
		game->ctl.fade = FADE;
	fading = !fading;
}

void	door_switch(t_game *game)
{
	int			x;
	int			y;
	int			dist;
	static bool	toggle;

	toggle = !toggle;
	if (!toggle)
		return ;
	game->ray.id = (WIDTH / 2) - 1;
	cast_ray(game, &game->ray, "DC1");
	x = game->ray.grid_x;
	y = game->ray.grid_y;
	dist = (int)game->ray.walls[game->ray.id].ray_dist;
	if (dist > COLISION * 2)
		return ;
	if (is_valid(y, x, "D"))
		game->map[y][x] = 'C';
	else if (is_valid(y, x, "C"))
		game->map[y][x] = 'D';
}
