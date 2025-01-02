/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:20:21 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/01/02 20:20:50 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_mouse(int button, int x, int y, void *param)
{
	(void) param;
	printf("Mouse button %d at %d %d\n", button, x, y);
	return (0);
}

int	key_release(int key, void *param)
{
	(void) param;
	printf("Key %d released\n", key);
	// if (hash_find(key) == 0)
	// 	return (1);
	// hash_update(key, 1);
	// if (key == KEY_W)
	// 	ft_game()->ctl.move.x -= 1;
	// if (key == KEY_S)
	// 	ft_game()->ctl.move.x -= -1;
	// if (key == KEY_A)
	// 	ft_game()->ctl.move.y -= -1;
	// if (key == KEY_D)
	// 	ft_game()->ctl.move.y -= 1;
	// if (key == KEY_LEFT || key == KEY_Q)
	// 	ft_game()->ctl.mv_angle -= -1;
	// if (key == KEY_RIGHT || key == KEY_E)
	// 	ft_game()->ctl.mv_angle -= 1;
	// ft_game()->update = 1;
	return (0);
}
