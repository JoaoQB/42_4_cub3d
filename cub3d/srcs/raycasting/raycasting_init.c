/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:10:07 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/14 17:03:30 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define EPSILON 1e-6  // Tolerance for floating-point comparison

// static bool are_equal(double a, double b, double epsilon) {
// 	return fabs(a - b) < epsilon;
// }

// static void test_trigonometry(t_ray *ray) {
// 	int i;
// 	bool success = true;

// 	for (i = 0; i < MAX_ANGLE; i++) {
// 		double radians = i * (PI / 180.0);
// 		double expected_sine = sin(radians);
// 		double expected_cosine = cos(radians);
// 		double expected_tangent = fabs(cos(radians)) < EPSILON ? INFINITY : tan(radians);

// 		// Test sine
// 		if (!are_equal(ray->trign.sines[i], expected_sine, EPSILON)) {
// 			printf("!! Error: sine[%d] expected %.6f, got %.6f\n", i, expected_sine, ray->trign.sines[i]);
// 			success = false;
// 		}

// 		// Test cosine
// 		if (!are_equal(ray->trign.cosines[i], expected_cosine, EPSILON)) {
// 			printf("!! Error: cosine[%d] expected %.6f, got %.6f\n", i, expected_cosine, ray->trign.cosines[i]);
// 			success = false;
// 		}

// 		// Test tangent
// 		if (expected_tangent == INFINITY) {
// 			if (ray->trign.tangents[i] != INFINITY) {
// 				printf("!! Error: tangent[%d] expected INFINITY, got %.6f\n", i, ray->trign.tangents[i]);
// 				success = false;
// 			}
// 		} else if (!are_equal(ray->trign.tangents[i], expected_tangent, EPSILON)) {
// 			printf("!! Error: tangent[%d] expected %.6f, got %.6f\n", i, expected_tangent, ray->trign.tangents[i]);
// 			success = false;
// 		}

// 		// Test radians
// 		if (!are_equal(ray->trign.radians[i], radians, EPSILON)) {
// 			printf("!! Error: radians[%d] expected %.6f, got %.6f\n", i, radians, ray->trign.radians[i]);
// 			success = false;
// 		}
// 	}

// 	if (success) {
// 		printf("!! All trigonometry tests passed!\n");
// 	} else {
// 		printf("!! Some trigonometry tests failed. See above for details.\n");
// 	}
// }

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
	printf("!! Ray Struct Initialized:\n");
	printf("!! h_width: %f\n", ray->h_width);
	printf("!! h_height: %f\n", ray->h_height);
	printf("!! fov: %f\n", ray->fov);
	printf("!! h_fov: %f\n", ray->h_fov);
	printf("!! p_height: %f\n", ray->p_height);
	printf("!! d_proj: %f\n", ray->d_proj);
	printf("!! ray_ang_inc: %f\n", ray->ray_ang_inc);
	printf("!! height_calc: %f\n", ray->height_calc);
	printf("!! map_width %d\n", ray->m_width);
	printf("!! map_height %d\n", ray->m_height);
	printf("!! pov.ang_dir: %f\n", ray->pov.ang_dir);
	printf("!! pov.pos_ux: %f\n", ray->pov.pos_ux);
	printf("!! pov.pos_uy: %f\n", ray->pov.pos_uy);
}

static void	print_trign()
{
	t_ray	*ray;
	int		i;

	ray = &ft_game()->ray;
	if (!ray)
		return ;
	i = 0;
	while (i < MAX_ANGLE)
	{
		printf("Angle: %d degrees\n", i);
		printf("Radians: %f\n", ray->trign.radians[i]);
		printf("Tangent: %f\n", ray->trign.tangents[i]);
		printf("Sine: %f\n", ray->trign.sines[i]);
		printf("Cosine: %f\n", ray->trign.cosines[i]);
		i++;
	}
}

static void	correct_trign(t_ray *ray)
{

	if (!ray)
		return ;
	ray->trign.tangents[0] = ray->trign.tangents[1];
	ray->trign.sines[0] = ray->trign.sines[1];
	ray->trign.tangents[90] = ray->trign.tangents[91];
	ray->trign.cosines[90] = ray->trign.sines[91];
	ray->trign.tangents[180] = ray->trign.tangents[181];
	ray->trign.sines[180] = ray->trign.sines[181];
	ray->trign.tangents[270] = ray->trign.tangents[271];
	ray->trign.cosines[270] = ray->trign.sines[271];
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
	correct_trign(ray);
}

// Divided height_calc by two
void	init_ray(void)
{
	t_ray	*ray;

	if (!ft_game())
		return ;
	ray = &ft_game()->ray;
	init_trigonometry(ray);
	// test_trigonometry(ray);
	print_trign();
	ray->h_width = WIDTH / 2;
	ray->h_height = HEIGHT / 2;
	ray->fov = FOV;
	ray->h_fov = FOV / 2;
	ray->p_height = UNIT_SIZE / 2;
	ray->d_proj = ray->h_width / get_tangent((int)ray->h_fov);
	ray->ray_ang_inc = ray->fov / WIDTH;
	ray->height_calc = (UNIT_SIZE * ray->d_proj);
	ray->m_width = get_map_width(ft_game()->map);
	ray->m_height = get_map_height(ft_game()->map);
	ray->pov.ang_dir = ft_game()->player.dir_angle;
	ray->pov.pos_ux = (ft_game()->player.pos.x) * UNIT_SIZE + (UNIT_SIZE / 2);
	ray->pov.pos_uy = (ft_game()->player.pos.y) * UNIT_SIZE + (UNIT_SIZE / 2);
	print_ray(ray);
}
