/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:49:36 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/09 16:23:26 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// TODO function to free map
static void free_map(char **map)
{
	if (!map)
		return;
	free(map);
}

void	free_game()
{
	t_game	*game_s;

	game_s = ft_game();
	free_map(game_s->map);
	free(game_s->mlx);
}
