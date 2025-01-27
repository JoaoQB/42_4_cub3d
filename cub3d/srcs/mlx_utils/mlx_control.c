/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:32:07 by fandre-b          #+#    #+#             */
/*   Updated: 2025/01/07 17:59:17 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (key == 104)
		mlx_mouse_hide(ft_game()->mlx->mlx, ft_game()->mlx->win);
	if (key == 106)
		mlx_mouse_show(ft_game()->mlx->mlx, ft_game()->mlx->win);
	ft_game()->player.speed = 0.1;
	if (key == KEY_ESC)
		handle_close(NULL);
	if (key == KEY_W && ft_game()->ctl.move.x <= 0) // i can do move check
		ft_game()->ctl.move.x += ft_game()->player.speed;
	if (key == KEY_S && ft_game()->ctl.move.x >= 0)
		ft_game()->ctl.move.x += - ft_game()->player.speed;
	if (key == KEY_A && ft_game()->ctl.move.y >= 0)
		ft_game()->ctl.move.y += - ft_game()->player.speed;
	if (key == KEY_D && ft_game()->ctl.move.y <= 0)
		ft_game()->ctl.move.y += ft_game()->player.speed;
	if (key == KEY_LEFT || key == KEY_Q)
		ft_game()->ctl.mv_angle += -1 ;
	if (key == KEY_RIGHT || key == KEY_E)
		ft_game()->ctl.mv_angle += 1;
	ft_game()->update = 1;
	return (0);
}

int	key_release(int key, void *param)
{
	(void) param;
	if (key == KEY_W && ft_game()->ctl.move.x >= 0) // i can do move check
		ft_game()->ctl.move.x -= ft_game()->player.speed;
	if (key == KEY_S && ft_game()->ctl.move.x <= 0)
		ft_game()->ctl.move.x -= - ft_game()->player.speed;
	if (key == KEY_A && ft_game()->ctl.move.y <= 0)
		ft_game()->ctl.move.y -= - ft_game()->player.speed;
	if (key == KEY_D && ft_game()->ctl.move.y >= 0)
		ft_game()->ctl.move.y -= ft_game()->player.speed;
	if (key == KEY_LEFT || key == KEY_Q)
		ft_game()->ctl.mv_angle -= -1;
	if (key == KEY_RIGHT || key == KEY_E)
		ft_game()->ctl.mv_angle -= 1;
	ft_game()->update = 1;
	return (0);
}


int	mouse_moved(int x, int y, void *param)
{
	static int	last_x;
	int			diff_x;

	(void) param;
	(void) y;
	diff_x = x - last_x;
	ft_game()->ctl.mv_angle -= diff_x;
	last_x = x;
	ft_game()->update = 1;
	return (0);
}

t_coord get_coord(t_coord ref)
{
	t_coord		rounded;
	t_cam	*cam;

	cam = &ft_game()->ray.cam;
	if (ref.x < 0)
		rounded.x = (int)(cam->pos.x);
	else
		rounded.x = (int) round(cam->pos.x);
	if (ref.y < 0)
		rounded.y = (int)(cam->pos.y);
	else
		rounded.y = (int) round(cam->pos.y);
	return (rounded);
}

void player_walk (void)
{
	t_game	*game;
	t_cam	*cam;
	t_coord collision;
	t_coord ref;

	game = ft_game();
	cam = &ft_game()->ray.cam;
	ref.x = cam->dir.x * game->ctl.move.x - cam->dir.y * game->ctl.move.y;
	ref.y = cam->dir.y * game->ctl.move.x + cam->dir.x * game->ctl.move.y;
	collision.x = copysign(COLISION, ref.x);
	collision.y = copysign(COLISION, ref.y);
	// printf("collision set to %f %f\n", collision.x, collision.y);
	cam->pos.y += ref.y;
	if (is_valid(cam->pos.y + collision.y * (1.01), cam->pos.x, "1 \n\0"))
	{
        // printf("\033[34m !!!!!collision direction!!!!!\033[0m\n"); // Blue text
		cam->pos.y = get_coord(ref).y - collision.y;
	}
	cam->pos.x += ref.x;
	if (is_valid(cam->pos.y, cam->pos.x + collision.x * (1.01), "1 \n\0"))
	{
        // printf("\033[32m !!!!!collision direction!!!!!\033[0m\n"); // green text
		cam->pos.x = get_coord(ref).x - collision.x;
	}
	// printf("player moves to %f %f\n", cam->pos.x, cam->pos.y);
}

int	render(void)
{
	t_cam	*cam;

	cam = &ft_game()->ray.cam;
	if (ft_game()->update == 0)
		return (0);
	// update direction angle
	ft_game()->player.dir_angle += ft_game()->ctl.mv_angle;

	// update direction vector
	cam->dir.x = get_cosine(ft_game()->player.dir_angle);
	cam->dir.y = -get_sine(ft_game()->player.dir_angle);

    // Calculate new position
	if (ft_game()->ctl.move.x != 0 || ft_game()->ctl.move.y != 0)
    	player_walk();

	// reset values
	ft_game()->ctl.mv_angle = 0;
	// ft_game()->ctl.move.x = 0;
	// ft_game()->ctl.move.y = 0;

	// run raycasting
	raycasting();
	// ft_game()->update = 0;
	return (0);
}
