/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:17:26 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/03 20:12:48 by fandre-b         ###   ########.fr       */
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

int	key_press(int key, void *param)
{
	(void) param;
	if (key == 104)
		mlx_mouse_hide(ft_game()->mlx->mlx, ft_game()->mlx->win);
	if (key == 106)
		mlx_mouse_show(ft_game()->mlx->mlx, ft_game()->mlx->win);
	if (key == KEY_ESC)
		handle_close(NULL);
	// if (key == KEY_SHIFT)
	// 	ft_game()->ctl.mv_speed *= 1.5;
	if (key == KEY_W && ft_game()->ctl.move.x <= 0) // i can do move check
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
	// if (key == KEY_SHIFT)
	// 	ft_game()->ctl.mv_speed /= 1.5;
	if (key == KEY_W && ft_game()->ctl.move.x >= 0) // i can do move check
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
