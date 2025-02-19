/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_ui.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:36:17 by fandre-b          #+#    #+#             */
/*   Updated: 2025/02/06 12:36:17 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_close(void *param)
{
	(void) param;
	free_game();
	exit(0);
	return (0);
}

int	handle_mouse(int button, int x, int y, void *param)
{
	(void) param;
	(void) x;
	(void) y;
	if (button == 1)
		door_switch(ft_game());
	return (0);
}

int	key_press(int key, void *param)
{
	(void) param;
	if (key == KEY_F)
		toggle_fade();
	if (key == KEY_ESC)
		handle_close(NULL);
	if (key == KEY_W && ft_game()->ctl.move.x <= 0)
		ft_game()->ctl.move.x += 1;
	if (key == KEY_S && ft_game()->ctl.move.x >= 0)
		ft_game()->ctl.move.x -= 1;
	if (key == KEY_A && ft_game()->ctl.move.y >= 0)
		ft_game()->ctl.move.y -= 1;
	if (key == KEY_D && ft_game()->ctl.move.y <= 0)
		ft_game()->ctl.move.y += 1;
	if (key == KEY_LEFT || key == KEY_Q)
		ft_game()->ctl.mv_angle += ft_game()->ctl.rot_speed;
	if (key == KEY_RIGHT || key == KEY_E)
		ft_game()->ctl.mv_angle += -ft_game()->ctl.rot_speed;
	if (key == KEY_SHIFT)
		ft_game()->ctl.mv_speed = (3.0 / UNIT_SIZE) * MOVE_SPEED;
	return (0);
}

int	key_release(int key, void *param)
{
	(void) param;
	if (key == KEY_W || key == KEY_S)
		ft_game()->ctl.move.x -= ft_game()->ctl.move.x;
	if (key == KEY_A || key == KEY_D)
		ft_game()->ctl.move.y -= ft_game()->ctl.move.y;
	if (key == KEY_LEFT || key == KEY_Q || key == KEY_RIGHT || key == KEY_E)
		ft_game()->ctl.mv_angle -= ft_game()->ctl.mv_angle;
	if (key == KEY_SHIFT)
		ft_game()->ctl.mv_speed = (1.0 / UNIT_SIZE) * MOVE_SPEED;
	return (0);
}
