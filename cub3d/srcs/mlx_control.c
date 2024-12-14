/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:32:07 by fandre-b          #+#    #+#             */
/*   Updated: 2024/12/14 19:07:08 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// redcross -> exit

// space -> jump
// ctrl -> crouch
// shift -> run (change spd)
// tab -> show map
// m -> show menu



int	handle_close(void *param)
{
	(void) param;
	// ft_free_all();
	exit(0);
	return (0);
}

int	handle_mouse(int button, int x, int y, void *param)
{
	(void) param;
	printf("Mouse button %d at %d %d\n", button, x, y);
	return (0);
}

int	key_press(int key, void *param)
{
	(void) param;
	printf("Key %d pressed\n", key);
	if (hash_find(key) == 1)
		return (0);
	hash_update(key, 1);
	if (key == KEY_ESC)
		handle_close(NULL);
	if (key == KEY_W)
		ft_game()->ctl.move.x += 1;
	if (key == KEY_S)
		ft_game()->ctl.move.x += -1;
	if (key == KEY_A)
		ft_game()->ctl.move.y += -1;
	if (key == KEY_D)
		ft_game()->ctl.move.y += 1;
	if (key == KEY_LEFT || key == KEY_Q)
		ft_game()->ctl.mv_angle += -1;
	if (key == KEY_RIGHT || key == KEY_E)
		ft_game()->ctl.mv_angle += 1;
	ft_game()->update = 1;
	return (0);
}

int	key_release(int key, void *param)
{
	(void) param;
	printf("Key %d released\n", key);
	if (hash_find(key) == 0)
		return (1);
	hash_update(key, 1);
	if (key == KEY_W)
		ft_game()->ctl.move.x -= 1;
	if (key == KEY_S)
		ft_game()->ctl.move.x -= -1;
	if (key == KEY_A)
		ft_game()->ctl.move.y -= -1;
	if (key == KEY_D)
		ft_game()->ctl.move.y -= 1;
	if (key == KEY_LEFT || key == KEY_Q)
		ft_game()->ctl.mv_angle -= -1;
	if (key == KEY_RIGHT || key == KEY_E)
		ft_game()->ctl.mv_angle -= 1;
	ft_game()->update = 1;
	return (0);
}

int mouse_moved(int x, int y, void *param)
{
	static int last_x = 0;
	int diff_x;

	(void) param;
	printf("Mouse moved %d %d\n", x, y);
	diff_x = x - last_x;
	ft_game()->ctl.dir += diff_x;
	ft_game()->update = 1;
	return (0);
}

int player_moves(void)
{
	if (ft_game()->update == 0)
		return 0;
	if (ft_game()->ctl.mv_angle == 0 || ft_game()->ctl.move.x == 0 ||
	ft_game()->ctl.move.x == 0)
		return 0;
	ft_game()->player.dir_angle += ft_game()->ctl.mv_angle * PLAYER_ROTATION;
	ft_game()->player.pos.x += ft_game()->ctl.move.x * PLAYER_SPEED;
	ft_game()->player.pos.y += ft_game()->ctl.move.y * PLAYER_SPEED;
	ft_game()->ctl.mv_angle = 0;
	ft_game()->ctl.move.x = 0;
	ft_game()->ctl.move.y = 0;
	// recalc_raycast();
	// raycasting();
	ft_game()->update = 0;
	return 0;
}
