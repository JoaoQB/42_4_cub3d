/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:10:07 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/09 21:54:03 by jqueijo-         ###   ########.fr       */
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
static void print_ray(t_ray *ray)
{
	if (!ray)
		return;
	printf("Ray Struct Initialized:\n");
	printf("h_width: %f\n", ray->h_width);
	printf("h_height: %f\n", ray->h_height);
	printf("fov: %f\n", ray->fov);
	printf("h_fov: %f\n", ray->h_fov);
	printf("p_height: %f\n", ray->p_height);
	printf("d_proj: %f\n", ray->d_proj);
	printf("ray_ang_inc: %f\n", ray->ray_ang_inc);
	printf("height_calc: %f\n", ray->height_calc);
	printf("map_width %d\n", ray->m_width);
	printf("map_height %d\n", ray->m_height);
	printf("pov.ang_dir: %f\n", ray->pov.ang_dir);
	printf("pov.pos_ux: %f\n", ray->pov.pos_ux);
	printf("pov.pos_uy: %f\n", ray->pov.pos_uy);
}

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
	init_trigonometry(ray);
	ray->h_width = WIDTH / 2;
	ray->h_height = HEIGHT / 2;
	ray->fov = FOV;
	ray->h_fov = FOV / 2;
	ray->p_height = UNIT_SIZE / 2;
	ray->d_proj = ray->h_width / get_tangent(ray, (int)ray->h_fov);
	ray->ray_ang_inc = ray->fov / WIDTH;
	ray->height_calc = UNIT_SIZE / ray->d_proj;
	ray->m_width = get_map_width(game->map);
	ray->m_height = get_map_height(game->map);
	ray->pov.ang_dir = game->player.dir_angle;
	ray->pov.pos_ux = (game->player.pos.x) * UNIT_SIZE + (UNIT_SIZE / 2);
	ray->pov.pos_uy = (game->player.pos.y) * UNIT_SIZE + (UNIT_SIZE / 2);
	print_ray(ray);
}
