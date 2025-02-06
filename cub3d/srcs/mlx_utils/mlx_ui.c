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
	if (key == 104)
		mlx_mouse_hide(ft_game()->mlx->mlx, ft_game()->mlx->win);
	if (key == 106)
		mlx_mouse_show(ft_game()->mlx->mlx, ft_game()->mlx->win);
	if (key == KEY_ESC)
		handle_close(NULL);
	if (key == KEY_W && ft_game()->ctl.move.x <= 0)
		ft_game()->ctl.move.x += ft_game()->ctl.mv_speed;
	if (key == KEY_S && ft_game()->ctl.move.x >= 0)
		ft_game()->ctl.move.x += -ft_game()->ctl.mv_speed;
	if (key == KEY_A && ft_game()->ctl.move.y >= 0)
		ft_game()->ctl.move.y += -ft_game()->ctl.mv_speed;
	if (key == KEY_D && ft_game()->ctl.move.y <= 0)
		ft_game()->ctl.move.y += ft_game()->ctl.mv_speed;
	if (key == KEY_LEFT || key == KEY_Q)
		ft_game()->ctl.mv_angle += ft_game()->ctl.rot_speed * 2;
	if (key == KEY_RIGHT || key == KEY_E)
		ft_game()->ctl.mv_angle += -ft_game()->ctl.rot_speed * 2;
	ft_game()->update = 1;
	return (0);
}

int	key_release(int key, void *param)
{
	(void) param;
	if (key == KEY_W && ft_game()->ctl.move.x >= 0)
		ft_game()->ctl.move.x -= ft_game()->ctl.mv_speed;
	if (key == KEY_S && ft_game()->ctl.move.x <= 0)
		ft_game()->ctl.move.x -= -ft_game()->ctl.mv_speed;
	if (key == KEY_A && ft_game()->ctl.move.y <= 0)
		ft_game()->ctl.move.y -= -ft_game()->ctl.mv_speed;
	if (key == KEY_D && ft_game()->ctl.move.y >= 0)
		ft_game()->ctl.move.y -= ft_game()->ctl.mv_speed;
	ft_game()->update = 1;
	return (0);
}
