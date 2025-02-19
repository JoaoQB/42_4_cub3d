/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:18:52 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/19 13:43:25 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*ft_game(void)
{
	static t_game	game_s;

	return (&game_s);
}

void	init_game(char *file_path)
{
	init_control();
	init_parsing(file_path);
	init_texture(ft_game());
	init_mlx();
	init_ray(ft_game());
	render();
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		ft_print_err("Please run ./cub3d <file_path.cub> ");
	if (!ft_strcmp(argv[0], "./bonus_cub3d"))
		ft_game()->bonus = 1;
	else
		ft_game()->bonus = 0;
	init_game(argv[1]);
	mlx_loop_hook(ft_game()->mlx->mlx, render, NULL);
	mlx_loop(ft_game()->mlx->mlx);
	return (0);
}
