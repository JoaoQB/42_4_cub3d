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
	float	speed;

	speed = (SPEED / UNIT_SIZE) * 0.5;
	(void) param;
	if (key == 104)
		mlx_mouse_hide(ft_game()->mlx->mlx, ft_game()->mlx->win);
	if (key == 106)
		mlx_mouse_show(ft_game()->mlx->mlx, ft_game()->mlx->win);
	if (key == KEY_ESC)
		handle_close(NULL);
	if (key == KEY_W && ft_game()->ctl.move.x <= 0) // i can do move check
		ft_game()->ctl.move.x += speed;
	if (key == KEY_S && ft_game()->ctl.move.x >= 0)
		ft_game()->ctl.move.x += -speed;
	if (key == KEY_A && ft_game()->ctl.move.y >= 0)
		ft_game()->ctl.move.y += -speed;
	if (key == KEY_D && ft_game()->ctl.move.y <= 0)
		ft_game()->ctl.move.y += speed;
	if (key == KEY_LEFT || key == KEY_Q)
		ft_game()->ctl.mv_angle += 1 ;
	if (key == KEY_RIGHT || key == KEY_E)
		ft_game()->ctl.mv_angle += -1;
	ft_game()->update = 1;
	return (0);
}

int	key_release(int key, void *param)
{
	float	speed;

	speed = (SPEED / UNIT_SIZE) * 0.5;
	(void) param;
	if (key == KEY_W && ft_game()->ctl.move.x >= 0) // i can do move check
		ft_game()->ctl.move.x -= speed;
	if (key == KEY_S && ft_game()->ctl.move.x <= 0)
		ft_game()->ctl.move.x -= -speed;
	if (key == KEY_A && ft_game()->ctl.move.y <= 0)
		ft_game()->ctl.move.y -= -speed;
	if (key == KEY_D && ft_game()->ctl.move.y >= 0)
		ft_game()->ctl.move.y -= speed;
	// if (key == KEY_LEFT || key == KEY_Q)
	// 	ft_game()->ctl.mv_angle -= -1;
	// if (key == KEY_RIGHT || key == KEY_E)
	// 	ft_game()->ctl.mv_angle -= 1;
	ft_game()->update = 1;
	return (0);
}
