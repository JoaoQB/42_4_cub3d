/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:18:52 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/01/29 13:55:16 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*ft_game(void)
{
	static t_game	game_s;

	return (&game_s);
}


int	main(int argc, char **argv)
{
	if (argc != 2)
		ft_print_error("Please run ./cub3d <file_path.cub> ");
	// mlx_init();
	init_game(argv[1]);
	// FOR DEBUG ONLY
	// raycasting();
	// render();
	mlx_loop_hook(ft_game()->mlx->mlx, render, NULL);
	mlx_loop(ft_game()->mlx->mlx);
	return (0);
}
