/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:32:07 by fandre-b          #+#    #+#             */
/*   Updated: 2025/02/03 19:52:49 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_coord	get_coord(t_coord ref)
{
	t_coord		rounded;
	t_cam		*cam;

	cam = &ft_game()->ray.cam;
	if (ref.x < 0)
		rounded.x = (int)(cam->pos.x);
	else
		rounded.x = (int) round(cam->pos.x);
	if (ref.y < 0)
		rounded.y = (int)(cam->pos.y);
	else
		rounded.y = (int) round(cam->pos.y);
	return (rounded);
}

int	mouse_moved(int x, int y, void *param)
{
	static int	last_x;
	int			diff_x;

	(void) param;
	(void) y;
	diff_x = x - last_x;
	ft_game()->ctl.mv_angle -= diff_x;
	last_x = x;
	ft_game()->update = 1;
	return (0);
}

void	player_walk(void)
{
	t_game	*game;
	t_cam	*cam;
	t_coord	collision;
	t_coord	ref;

	game = ft_game();
	cam = &ft_game()->ray.cam;
	ref.x = cam->dir.x * game->ctl.move.x - cam->dir.y * game->ctl.move.y;
	ref.y = cam->dir.y * game->ctl.move.x + cam->dir.x * game->ctl.move.y;
	collision.x = copysign(COLISION, ref.x);
	collision.y = copysign(COLISION, ref.y);
	// printf("collision set to %f %f\n", collision.x, collision.y);
	cam->pos.y += ref.y;
	if (is_valid(cam->pos.y + collision.y * (1.01), cam->pos.x, "1D \n\0"))
	{
		// printf("\033[34m !!!!!collision direction!!!!!\033[0m\n"); // Blue text
		cam->pos.y = get_coord(ref).y - collision.y;
	}
	cam->pos.x += ref.x;
	if (is_valid(cam->pos.y, cam->pos.x + collision.x * (1.01), "1D \n\0"))
	{
		// printf("\033[32m !!!!!collision direction!!!!!\033[0m\n"); // green text
		cam->pos.x = get_coord(ref).x - collision.x;
	}
	// printf("player moves to %f %f\n", cam->pos.x, cam->pos.y);
}

int	render(void)
{
	t_cam	*cam;

	cam = &ft_game()->ray.cam;
	if (ft_game()->update == 0)
		return (0);
	// update direction angle
	ft_game()->ctl.dir_angle += ft_game()->ctl.mv_angle;
	// update direction vector
	cam->dir.x = get_cosine(ft_game()->ctl.dir_angle);
	cam->dir.y = -get_sine(ft_game()->ctl.dir_angle);
	// Calculate new position
	if (ft_game()->ctl.move.x != 0 || ft_game()->ctl.move.y != 0)
		player_walk();
	// reset values
	ft_game()->ctl.mv_angle = 0;
	// ft_game()->ctl.move.x = 0;
	// ft_game()->ctl.move.y = 0;
	// run raycasting
	raycasting();
	// ft_game()->update = 0;
	draw_minimap(0, 0);
	return (0);
}
