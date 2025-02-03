/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:18:50 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/03 13:23:38 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(void)
{
	t_mlx	*mlx;

	ft_game()->mlx = my_calloc(1, sizeof(t_mlx));
	mlx = ft_game()->mlx;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		ft_print_error("MLX: not properly initialized");
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, \
	&mlx->img.len_line, &mlx->img.endian);
	if (!mlx->img.img || !mlx->img.addr || !mlx->win)
		ft_print_error("MLX: not properly initialized");
	///// Triggered when the mouse is moved.
	mlx_hook(ft_game()->mlx->win, 6, 1L << 6, mouse_moved, NULL);
	///// Triggered cross exit is pressed
	mlx_hook(ft_game()->mlx->win, 17, 0, handle_close, NULL);
	///// Triggered when a key is pressed.
	mlx_hook(ft_game()->mlx->win, 2, 1L << 0, key_press, NULL);
	// Triggered when a key is released.
	mlx_hook(ft_game()->mlx->win, 3, 1L << 1, key_release, NULL);
	///// Triggered when a mouse button is pressed.
	mlx_hook(ft_game()->mlx->win, 4, 1L << 2, handle_mouse, NULL);
	// Triggered when a mouse button is released.
	mlx_hook(ft_game()->mlx->win, 5, 1L << 3, handle_mouse, NULL);
}

void	init_game(char *file_path)
{
	char	**lines;
	char	*file_str;

	file_str = file_to_str(file_path);
	lines = ft_split(file_str, '\n');
	// free(file_str);
	extract_textures(lines);
	extract_map(ft_game(), lines);
	free(lines);
	ft_game()->player.pos.y = -1;
	ft_game()->player.pos.x = -1;
	check_map(ft_game()->map);
	ft_game()->player.dir_angle = ft_game()->player.angle;
	init_mlx();
	init_texture(ft_game());
	export_textures();
	init_ray(ft_game());
}
