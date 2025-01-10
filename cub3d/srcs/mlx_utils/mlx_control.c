/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:32:07 by fandre-b          #+#    #+#             */
/*   Updated: 2025/01/07 17:59:17 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** redcross -> exit
** space -> jump
** ctrl -> crouch
** shift -> run (change spd)
** tab -> show map
** m -> show menu
*/

int	handle_close(void *param)
{
	(void) param;
	// ft_free_all();
	exit(0);
	return (0);
}

int	key_press(int key, void *param)
{
	(void) param;
	// printf("Key %d pressed\n", key);
	// if (hash_find(key) == 1)
	// 	return (0);
	// hash_update(key, 1);
	ft_game()->player.speed = 0.1;
	if (key == KEY_ESC)
		handle_close(NULL);
	if (key == KEY_W)
		ft_game()->ctl.move.x += ft_game()->player.speed;
	if (key == KEY_S)
		ft_game()->ctl.move.x += - ft_game()->player.speed;
	if (key == KEY_A)
		ft_game()->ctl.move.y += - ft_game()->player.speed;
	if (key == KEY_D)
		ft_game()->ctl.move.y += ft_game()->player.speed;
	if (key == KEY_LEFT || key == KEY_Q)
		ft_game()->ctl.mv_angle += -1 ;
	if (key == KEY_RIGHT || key == KEY_E)
		ft_game()->ctl.mv_angle += 1;
	ft_game()->update = 1;
	return (0);
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

// intead of using dir_angle, use vector from start (cam->dir)
int	player_moves(void)
{
	t_ray	*ray;
	t_game	*game;
	t_cam	*cam;

	game = ft_game();
	ray = &game->ray;
	cam = &ray->cam;
	if (game->update == 0)
		return (0);

	// update direction angle
	game->player.dir_angle += game->ctl.mv_angle;

	// update direction vector
	cam->dir.x = get_cosine(game->player.dir_angle);
	cam->dir.y = -get_sine(game->player.dir_angle);

    // Calculate new position
    cam->pos.x += game->ctl.move.x * cam->dir.x - game->ctl.move.y * cam->dir.y;
    cam->pos.y += game->ctl.move.x * cam->dir.y + game->ctl.move.y * cam->dir.x;

	// reset values
	game->ctl.mv_angle = 0;
	game->ctl.move.x = 0;
	game->ctl.move.y = 0;

	// run raycasting
	raycasting();
	game->update = 0;
	return (0);
}
