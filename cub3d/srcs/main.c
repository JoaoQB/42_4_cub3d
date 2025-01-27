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

t_game	*ft_game(void)
{
	static t_game	game_s;

	return (&game_s);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		ft_print_error("Please run ./cub3d <file_path.cub> ");
	init_game(argv[1]);
	raycasting();
	render();
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
	mlx_loop_hook(ft_game()->mlx->mlx, render, NULL);
	mlx_loop(ft_game()->mlx->mlx);
	return (0);
}


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
/*
#include "cub3d.h"

t_game	*ft_game(void)
{
	static t_game	game_s;

	return (&game_s);
}

void mlx_init()
{
	t_mlx	*mlx;

	mlx = ft_game()->mlx;
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, \
	&mlx->img.len_line, &mlx->img.endian);
	if (!mlx->img.img || !mlx->img.addr || !mlx->win)
		ft_print_error("MLX: not properly initialized");
	///// Triggered when the mouse is moved.
	mlx_hook(game->mlx->win, 6, 1L << 6, mouse_moved, NULL);
	///// Triggered cross exit is pressed
	mlx_hook(game->mlx->win, 17, 0, handle_close, NULL);
	///// Triggered when a key is pressed.
	mlx_hook(game->mlx->win, 2, 1L << 0, key_press, NULL);
	// Triggered when a key is released.
	mlx_hook(game->mlx->win, 3, 1L << 1, key_release, NULL);
	///// Triggered when a mouse button is pressed.
	mlx_hook(game->mlx->win, 4, 1L << 2, handle_mouse, NULL);
	// Triggered when a mouse button is released.
	mlx_hook(game->mlx->win, 5, 1L << 3, handle_mouse, NULL);
	mlx_loop_hook(game->mlx->mlx, render, NULL);
	mlx_loop(game->mlx->mlx);
}

void	init_game(char *file_path)
{
	char	**lines;
	char	*file_str;

	ft_game()->mlx = my_calloc(1, sizeof(t_mlx));
	ft_game()->mlx = mlx_init();
	if (!ft_game()->mlx)
		ft_print_error("MLX: not properly initialized");
	file_str = file_to_str(file_path);
	lines = ft_split(file_str, '\n');
	// free(file_str);
	extract_textures(lines);
	extract_map(ft_game(), lines);
	free(lines);
	check_map(ft_game()->map);
	ft_game()->player.dir_angle = ft_game()->player.angle;
	init_mlx();
	init_ray(ft_game());
	init_texture(ft_game());
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		ft_print_error("Please run ./cub3d <file_path.cub> ");
	mlx_init();
	init_game(argv[1]);
	raycasting();
	render();

	return (0);
}
*/