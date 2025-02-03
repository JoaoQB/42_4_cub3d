/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:20:21 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/03 19:02:42 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



int	handle_mouse(int button, int x, int y, void *param)
{
	(void) param;
	(void) x;
	(void) y;
	// printf("Mouse button %d at %d %d\n", button, x, y);
	if (button == 1)
		door_switch(ft_game());
	return (0);
}
