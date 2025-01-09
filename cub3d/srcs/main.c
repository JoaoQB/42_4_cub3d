/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:18:52 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/01/02 19:36:01 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render(void)
{
	player_moves();
	return (0);
}

t_game	*ft_game(void)
{
	static t_game	game_s;

	return (&game_s);
}

// TODO PRINT_ERROR?
// TODO merge init_game
// TODO make an function mlx_hooks
// Normi not accepting
int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		printf("Please run ./cub3d <file_path.cub> \n");
		return (EXIT_FAILURE);
	}
	init_game(argv[1]);
	raycasting();
	render();
	// free_game();
	// draw_minimap(0, 0);
	// mlx_put_image_to_window(ft_game()->mlx->mlx,
		// ft_game()->mlx->win, ft_game()->mlx->img.img, 0, 0);
	mlx_put_image_to_window(ft_game()->mlx->mlx,
		ft_game()->mlx->win, ft_game()->mlx->img.img, 0, 0);
	// Triggered when a key is pressed.
	mlx_hook(ft_game()->mlx->win, 2, 1L << 0, key_press, NULL);
	// Triggered when a key is released.
	mlx_hook(ft_game()->mlx->win, 3, 1L << 1, key_release, NULL);
	// Triggered when the mouse is moved.
	mlx_hook(ft_game()->mlx->win, 6, 1L << 6, mouse_moved, NULL);
	// Triggered when a mouse button is pressed.
	//TODO find if i need to use this
	mlx_hook(ft_game()->mlx->win, 4, 1L << 2, handle_mouse, NULL);
	// Triggered when a mouse button is released.
	mlx_hook(ft_game()->mlx->win, 5, 1L << 3, handle_mouse, NULL);
	// Triggered cross exit is pressed
	mlx_hook(ft_game()->mlx->win, 17, 0, handle_close, NULL);
	// Set the loop to call the player_moves function
	mlx_loop_hook(ft_game()->mlx->mlx, render, NULL);
	mlx_loop(ft_game()->mlx->mlx);
	// mlx_loop_hook(ft_game()->mlx, player_moves, NULL);
	return (0);
}
