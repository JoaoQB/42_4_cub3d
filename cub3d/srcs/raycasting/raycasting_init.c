/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:10:07 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/07 18:01:58 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// TODO INIT_GAME
void	init_trigonometry(t_ray *ray)
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

t_ray	*init_ray(t_game *game)
{
	t_ray	*new_ray;

	if (!game)
		return (NULL);
	new_ray = malloc(sizeof(t_ray));
	if (!new_ray)
		return (NULL);
	init_trigonometry(new_ray);
	new_ray->half_fov = FOV / 2;
	new_ray->player_height = UNIT_SIZE / 2;
	new_ray->half_width = WIDTH / 2;
	new_ray->half_height = HEIGHT / 2;
	new_ray->distance_to_projection = new_ray->half_width / get_tangent(new_ray, (int)new_ray->half_fov);
	new_ray->height_calc = UNIT_SIZE / new_ray->distance_to_projection;
	new_ray->ray_increment_angle = FOV / WIDTH;
	new_ray->pov.direction_angle = game->player.dir_angle;
	new_ray->pov.pos_unit_x = (game->player.pos.x) * UNIT_SIZE + (UNIT_SIZE / 2);
	new_ray->pov.pos_unit_y = (game->player.pos.y) * UNIT_SIZE + (UNIT_SIZE / 2);
	return (new_ray);
}
