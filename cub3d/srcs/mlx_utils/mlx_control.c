/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:32:07 by fandre-b          #+#    #+#             */
/*   Updated: 2025/01/02 20:38:23 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** redcross -> exit
** space -> jump
** ctrl -> crouch
** shift -> run (change spd)
** tab -> show map
** m -> show menu
*/

int	handle_close(void *param)
{
	(void) param;
	// ft_free_all();
	exit(0);
	return (0);
}

int	key_press(int key, void *param)
{
	(void) param;
	printf("Key %d pressed\n", key);
	// if (hash_find(key) == 1)
	// 	return (0);
	// hash_update(key, 1);
	if (key == KEY_ESC)
		handle_close(NULL);
	if (key == KEY_W)
		ft_game()->ctl.move.x += 1;
	if (key == KEY_S)
		ft_game()->ctl.move.x += -1;
	if (key == KEY_A)
		ft_game()->ctl.move.y += -1;
	if (key == KEY_D)
		ft_game()->ctl.move.y += 1;
	if (key == KEY_LEFT || key == KEY_Q)
		ft_game()->ctl.mv_angle += -1;
	if (key == KEY_RIGHT || key == KEY_E)
		ft_game()->ctl.mv_angle += 1;
	ft_game()->update = 1;
	return (0);
}

int	mouse_moved(int x, int y, void *param)
{
	static int	last_x;
	int			diff_x;

	(void) param;
	printf("Mouse moved %d %d\n", x, y);
	diff_x = x - last_x;
	printf("diff_x: %d\n", diff_x);
	ft_game()->ctl.mv_angle -= diff_x;
	last_x = x;
	ft_game()->update = 1;
	return (0);
}

// intead of using dir_angle, use vector from start (cam->dir)
int	player_moves(void)
{
	t_ray	*ray;
	t_game	*game;
	t_cam	*cam;

	game = ft_game();
	ray = &game->ray;
	cam = &ray->cam;
	if (game->update == 0)
		return (0);
	// if (game->ctl.mv_angle == 0 && game->ctl.move.x == 0
	// 	&& game->ctl.move.x == 0)
	// 	return (0);
	game->player.dir_angle += game->ctl.mv_angle;
	cam->dir.x = get_cosine(game->player.dir_angle);
	cam->dir.y = -get_sine(game->player.dir_angle);
	cam->pos.x += game->ctl.move.x * cam->dir.x - game->ctl.move.y * cam->dir.y;
	cam->pos.y += game->ctl.move.x * cam->dir.y + game->ctl.move.y * cam->dir.x;
	game->ctl.mv_angle = 0;
	game->ctl.move.x = 0;
	game->ctl.move.y = 0;
	raycasting();
	mlx_put_image_to_window(game->mlx->mlx,
		game->mlx->win, game->mlx->img.img, 0, 0);
	game->update = 0;
	return (0);
}

	// ray->dir_x = ray->cam.dir.x + ray->cam.plane.x * ray->cam_x;
	// ray->dir_y = ray->cam.dir.y + ray->cam.plane.y * ray->cam_x;
	// // printf("ray_id_%d: Final Direction Vector (dir_x: %f, dir_y: %f)\n",
	// 	// ray_id, ray->dir_x, ray->dir_y);
	// ray->grid_x = (int)ray->cam.pos.x;
	// ray->grid_y = (int)ray->cam.pos.y;
