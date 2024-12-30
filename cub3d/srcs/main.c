/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:17:39 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/30 12:08:35 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int render()
{
	player_moves();
	return (0);
}

t_game	*ft_game()
{
	static t_game	game_s;

	return (&game_s);
}

int main(int argc, char **argv)
{


	(void)argv;
	if (argc == 1)
	{
		// printf("argc 1\n");
		ft_game()->update = 1;
	}
	else if (argc == 2)
	{
		// printf("argc 2\n");
		ft_game()->update = 0;
	}
	// if (argc != 2)
	else
	{
		// TODO PRINT_ERROR?
		printf("Please run ./cub3d <.cub_file_path> \n");
		return (EXIT_FAILURE);
	}


	init_game(argv[1]); //TODO merge this
	raycasting();
	render();
	// free_game();
	// draw_minimap(0, 0);
	// mlx_put_image_to_window(ft_game()->mlx->mlx, ft_game()->mlx->win, ft_game()->mlx->img.img, 0, 0);
	// TODO make an function for this :
	mlx_put_image_to_window(ft_game()->mlx->mlx, ft_game()->mlx->win, ft_game()->mlx->img.img, 0, 0);
    // Triggered when a key is pressed.
    mlx_hook(ft_game()->mlx->win, 2, 1L<<0, key_press, NULL);
    // Triggered when a key is released.
    mlx_hook(ft_game()->mlx->win, 3, 1L<<1, key_release, NULL);
    // Triggered when the mouse is moved.
    mlx_hook(ft_game()->mlx->win, 6, 1L<<6, mouse_moved, NULL);
    // Triggered when a mouse button is pressed. //TODO find if i need to use this
    mlx_hook(ft_game()->mlx->win, 4, 1L<<2, handle_mouse, NULL);
    // Triggered when a mouse button is released.
    mlx_hook(ft_game()->mlx->win, 5, 1L<<3, handle_mouse, NULL);
    // Triggered cross exit is pressed
	mlx_hook(ft_game()->mlx->win, 17, 0, handle_close, NULL);
	// Set the loop to call the player_moves function
	mlx_loop_hook(ft_game()->mlx->mlx, render, NULL);
	mlx_loop(ft_game()->mlx->mlx);
	mlx_loop_hook(ft_game()->mlx, player_moves, NULL);
	return (0);
}
