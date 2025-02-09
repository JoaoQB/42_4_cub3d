/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:32:07 by fandre-b          #+#    #+#             */
/*   Updated: 2025/02/09 16:33:41 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	ref.x *= ft_game()->ctl.mv_speed;
	ref.y *= ft_game()->ctl.mv_speed;
	collision.x = copysign(COLISION, ref.x);
	collision.y = copysign(COLISION, ref.y);
	cam->pos.y += ref.y;
	if (is_valid(cam->pos.y + collision.y * (1.01), cam->pos.x, "1D \n\0"))
		cam->pos.y = get_coord(ref).y - collision.y;
	cam->pos.x += ref.x;
	if (is_valid(cam->pos.y, cam->pos.x + collision.x * (1.01), "1D \n\0"))
		cam->pos.x = get_coord(ref).x - collision.x;
}

int	render(void)
{
	t_cam	*cam;

	cam = &ft_game()->ray.cam;
	ft_game()->ctl.dir_angle += ft_game()->ctl.mv_angle;
	cam->dir.x = get_cosine(ft_game()->ctl.dir_angle);
	cam->dir.y = -get_sine(ft_game()->ctl.dir_angle);
	if (ft_game()->ctl.move.x != 0 || ft_game()->ctl.move.y != 0)
		player_walk();
	if (ft_game()->update == 1)
		ft_game()->ctl.mv_angle -= ft_game()->ctl.mv_angle;
	ft_game()->update = 0;
	raycasting();
	draw_minimap();
	return (0);
}
