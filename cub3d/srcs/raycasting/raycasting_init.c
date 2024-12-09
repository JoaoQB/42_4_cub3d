/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:10:07 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/09 16:16:20 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_trigonometry(t_ray *ray)
{
	int	i;

	if (!ray)
		return ;
	i = 0;
	while (i < MAX_ANGLE)
	{
		ray->trign.radians[i] = i * (PI / 180);
		ray->trign.tangents[i] = tan(ray->trign.radians[i]);
		ray->trign.sines[i] = sin(ray->trign.radians[i]);
		ray->trign.cosines[i] = cos(ray->trign.radians[i]);
		i++;
	}
}

void	init_ray(t_game *game)
{
	t_ray	*ray;

	if (!game)
		return ;
	ray = &game->ray;
	ray->h_width = WIDTH / 2;
	ray->h_height = HEIGHT / 2;
	ray->h_fov = FOV / 2;
	ray->p_height = UNIT_SIZE / 2;
	ray->d_proj = ray->h_width / get_tangent(ray, (int)ray->h_fov);
	ray->height_calc = UNIT_SIZE / ray->d_proj;
	init_trigonometry(ray);
	ray->ray_ang_inc = FOV / WIDTH;
	ray->pov.ang_dir = game->player.dir_angle;
	ray->pov.pos_ux = (game->player.pos.x) * UNIT_SIZE + (UNIT_SIZE / 2);
	ray->pov.pos_uy = (game->player.pos.y) * UNIT_SIZE + (UNIT_SIZE / 2);
}
