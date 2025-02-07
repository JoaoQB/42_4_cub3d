/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:18:50 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/07 12:39:33 by fandre-b         ###   ########.fr       */
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
		ft_print_err("MLX: not properly initialized");
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, \
	&mlx->img.len_line, &mlx->img.endian);
	if (!mlx->img.img || !mlx->img.addr || !mlx->win)
		ft_print_err("MLX: not properly initialized");
	mlx_hook(ft_game()->mlx->win, 6, 1L << 6, mouse_moved, NULL);
	mlx_hook(ft_game()->mlx->win, 17, 0, handle_close, NULL);
	mlx_hook(ft_game()->mlx->win, 2, 1L << 0, key_press, NULL);
	mlx_hook(ft_game()->mlx->win, 3, 1L << 1, key_release, NULL);
	mlx_hook(ft_game()->mlx->win, 4, 1L << 2, handle_mouse, NULL);
	mlx_hook(ft_game()->mlx->win, 5, 1L << 3, handle_mouse, NULL);
}

void	init_parsing(char *file_path)
{
	char	**lines;
	char	*file_str;

	file_str = file_to_str(file_path);
	lines = ft_split(file_str, '\n');
	free(file_str);
	extract_textures(lines);
	extract_map(ft_game(), lines);
	free_frases(lines);
	check_map(ft_game()->map);
}

void	init_ray(t_game *game)
{
	t_ray	*ray;

	if (!game)
		return ;
	ray = &game->ray;
	ray->cam.fov = FOV;
	ray->cam.hfov = ray->cam.fov / 2;
	ray->cam.width = WIDTH;
	ray->cam.height = HEIGHT;
	ray->cam.pos.x = game->ctl.pos.x;
	ray->cam.pos.y = game->ctl.pos.y;
	ray->cam.dir.x = get_cosine(game->ctl.dir_angle);
	ray->cam.dir.y = -get_sine(game->ctl.dir_angle);
	ray->cam.width = WIDTH;
	ray->cam.height = HEIGHT;
	ray->cam.h_height = ray->cam.height / 2;
}

void	init_control(void)
{
	ft_game()->ctl.mv_speed = (1.0 / UNIT_SIZE) * MOVE_SPEED;
	ft_game()->ctl.rot_speed = ROTATION_SPEED;
	ft_game()->ctl.pos.y = -1;
	ft_game()->ctl.pos.x = -1;
	ft_game()->ctl.angle = UNKNOWN;
}

void	init_texture(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = -1;
	while (++i < WIDTH)
		game->ray.walls[i].texture = NULL;
	i = -1;
	while (++i < TEXTURE_SIZE)
		export_textures(ft_game()->texture[i]);
	game->door = (t_texture *)my_calloc(1, sizeof(t_texture));
	game->door->image_path = ft_strdup("./includes/textures/wall_tiles.xpm");
	game->door->image_name = ft_strdup("DOOR");
	export_textures(game->door);
	check_textures(ft_game());
	return ;
}
