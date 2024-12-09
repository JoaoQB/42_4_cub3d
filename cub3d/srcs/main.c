/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:17:39 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/07 20:19:58 by fandre-b         ###   ########.fr       */
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
	char *file_str;

	if (argc != 2)
		return (0);
	file_str = file_to_str(argv[1]);
	extract_images(file_str);
	extract_map(file_str);
	check_map(ft_game()->map);
	init_struct();
	//raycasting
	// mlx_key_hook(ft_game()->mlx->win, handle_key, f);
	// mlx_mouse_hook(ft_game()->mlx->win, handle_mouse, f);
	// mlx_hook(ft_game()->mlx->win, 17, 0, handle_close, f);
	// mlx_loop_hook(ft_game()->mlx, f->info.loop_func, f);
	// mlx_loop(ft_game()->mlx);
	return (0);
}