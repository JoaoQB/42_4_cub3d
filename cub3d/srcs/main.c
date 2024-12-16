/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:17:39 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/16 14:53:59 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* ./cub3d | grep -e "\!\! " -e "ray_id_0," -e "ray_id_1," -e "ray_id_2," -e "ray_id_3," -e "ray_id_398," -e "ray_id_399," -e "ray_id_400," -e "ray_id_401," -e "ray_id_402," -e "ray_id_600," -e "ray_id_799," -e "ray_id_200" -e "ray_id_397," -e "ray_id_403,"
*/

int render()
{
	raycasting();
	mlx_put_image_to_window(ft_game()->mlx->mlx, ft_game()->mlx->win, ft_game()->mlx->img.img, 0, 0);
	return (0);
}

t_game	*ft_game()
{
	static t_game	game_s;

	return (&game_s);
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		// TODO PRINT_ERROR?
		printf("Please run ./cub3d <.cub_file_path> \n");
		return (EXIT_FAILURE);
	}
	init_game();
	raycasting2();
	// mlx_loop_hook(ft_game()->mlx->mlx, render, NULL);
	// mlx_loop(ft_game()->mlx->mlx);
	free_game();
	return (EXIT_SUCCESS);
}
