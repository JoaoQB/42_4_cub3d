/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:34:22 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/16 13:26:43 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_map_height(char **map)
{
	int	i;

	if (!map)
		return (-1);
	i = 0;
	while(map[i] != NULL)
		i++;
	return (i);
}

//TODO ft_strlen
static int	get_map_width(char **map)
{
	int	i;
	int	width;
	int	current_width;

	if (!map)
		return (-1);
	i = 0;
	width = 0;
	while(map[i] != NULL)
	{
		current_width = strlen(map[i]);
		if (current_width > width)
			width = current_width;
		i++;
	}
	return (width);
}

void	init_ray2(t_game *game)
{
	t_ray	*ray;

	if (!game)
		return ;
	ray = &game->ray;
	init_trigonometry(ray);
	ray->cam.pos.x = game->player.pos.x;
	ray->cam.pos.y = game->player.pos.y;
	ray->cam.dir.x = get_cosine(game->player.dir_angle);
	ray->cam.dir.y = get_sine(game->player.dir_angle);
	ray->cam.plane.x = -ray->cam.dir.y;
	ray->cam.plane.y = ray->cam.dir.x;
	ray->m_width = get_map_width(game->map);
	ray->m_height = get_map_height(game->map);
	ray->width = WIDTH;
	ray->height = HEIGHT;

	printf("!! Player Position: x = %f, y = %f\n", game->player.pos.x, game->player.pos.y);
	printf("!! Camera Direction: dir_x = %f, dir_y = %f\n", ray->cam.dir.x, ray->cam.dir.y);
	printf("!! Camera Plane: plane_x = %f, plane_y = %f\n", ray->cam.plane.x, ray->cam.plane.y);
}
