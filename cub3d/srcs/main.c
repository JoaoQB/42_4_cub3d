/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:17:39 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/11 12:42:54 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game *ft_game(void)
{
	static t_game game;

	return (&game);
}

int main(int argc, char **argv)
{
	char **lines;
	char *file_str;

	if (argc != 2)
		return (0);
	init_struct();
	file_str = file_to_str(argv[1]);
	lines = ft_split(file_str, '\n');
	extract_textures(lines);
	extract_map(lines);
	free(lines);
	check_map(ft_game()->map);


	draw_minimap(0, 0);
	mlx_put_image_to_window(ft_game()->mlx->mlx, ft_game()->mlx->win, ft_game()->mlx->img.img, 0, 0);
	// mlx_put_image_to_window(ft_game()->mlx->mlx, ft_game()->mlx->win, ft_game()->mlx->img.img, 0, 0);


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
	mlx_loop_hook(ft_game()->mlx, player_moves, NULL);
	// Start the loop to listen for events
	mlx_loop(ft_game()->mlx->mlx);
	return (0);
}