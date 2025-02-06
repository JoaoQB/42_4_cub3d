#include "cub3d.h"

void	print_ray(t_ray *ray)
{
	if (!ray)
		return ;
	printf("!! Camera Width: %f\n", ray->cam.width);
	printf("!! Camera Height: %f\n", ray->cam.height);
	printf("!! Camera Half Width: %f\n", ray->cam.hwidth);
	printf("!! Camera Half Height: %f\n", ray->cam.h_height);
	printf("!! Camera FOV: %f\n", ray->cam.fov);
	printf("!! Camera Half FOV: %f\n", ray->cam.hfov);
	printf("!! Camera Position: x = %f, y = %f\n",
		ray->cam.pos.x, ray->cam.pos.y);
	printf("!! Camera Direction: dir.x = %f, dir.y = %f\n",
		ray->cam.dir.x, ray->cam.dir.y);
	printf("!! Camera Plane: plane_x = %f, plane_y = %f\n",
		ray->cam.plane.x, ray->cam.plane.y);
	printf("!! Map Width: %d\n", ray->cam.map_width);
	printf("!! Map Height: %d\n", ray->cam.map_height);
}

void	debug_start(t_ray *ray)
{
	if (!ray)
		return ;
	printf("ray_id_%d: cam_x = %f (normalized ray pos on camera plane)\n",
		ray->id, ray->cam_x);
	printf("ray_id_%d: Final Direction Vector (dir.x: %f, dir.y: %f)\n",
		ray->id, ray->dir.x, ray->dir.y);
	printf("ray_id_%d: Starting grid position -> grid_x: %d, grid_y: %d\n",
		ray->id, ray->grid_x, ray->grid_y);
	printf("ray_id_%d: next.x = %f (distance between vertical grid lines)\n",
		ray->id, ray->next.x);
	printf("ray_id_%d: next.y = %f (distance between horizntl grid lines)\n",
		ray->id, ray->next.y);
}

void	debug_aim(t_ray *ray)
{
	if (!ray)
		return ;
	printf("ray_id_%d: delta.x = %f, delta.x = %f\n",
		ray->id, ray->delta.x, ray->delta.x);
	printf("ray_id_%d: step.y = %f, delta.x = %f\n",
		ray->id, ray->step.y, ray->delta.x);
}

void	debug_wall_info(t_ray *ray, t_wall *wall)
{
	if (!ray || !wall)
		return ;
	printf("\n=== Wall Info Debug ===\n");
	printf("Ray ID: %d\n", ray->id);
	printf("Ray Distance: %f\n", wall->ray_dist);
	printf("Wall Direction: %d\n", wall->dir);
	printf("Wall X: %f\n", wall->wall_x);
	printf("Wall Height: %d\n", wall->height);
	printf("Wall Top: %d\n", wall->top);
	printf("Wall Bottom: %d\n", wall->bottom);
	if (!wall->texture)
		printf("Error: Wall texture is NULL\n");
	else
		printf("wall texture: %s\n", wall->texture->image_name);
	printf("Texture X: %d\n", wall->tex_x);
}

void	debug_cast(t_ray *ray)
{
	if (!ray)
		return ;
	printf("ray_id_%d: delta.x = %f, delta.x = %f\n",
		ray->id, ray->delta.x, ray->delta.x);
	printf("ray_id_%d: delta.x = %f, delta.x = %f, grid_x = %d, grid_y = %d\n",
		ray->id, ray->delta.x, ray->delta.x, ray->grid_x, ray->grid_y);
	printf("ray_id_%d: Out of bounds at grid_x = %d, grid_y = %d\n",
		ray->id, ray->grid_x, ray->grid_y);
	printf("ray_id_%d: Hit wall at grid_x = %d, grid_y = %d\n",
		ray->id, ray->grid_x, ray->grid_y);
}

void	print_texture_info(t_texture *texture, int index)
{
	printf("\n=== TEXTURE[%d] ===\n", index);
	printf("Name: %s\n", texture->image_name);
	printf("Path: %s\n", texture->image_path);
	printf("Color: %d\n", texture->colour);
	if (texture->image_data)
	{
		printf("Image data exists\n");
		if (texture->image_data->img)
		{
			printf("Image loaded: Yes\n");
			printf("Dimensions: %dx%d\n",
				texture->image_data->width, texture->image_data->height);
			printf("Address: %p\n", texture->image_data->addr);
			printf("BPP: %d\n", texture->image_data->bpp);
			printf("Line Length: %d\n", texture->image_data->len_line);
			printf("Endian: %d\n", texture->image_data->endian);
		}
	}
	else
		printf("Image not loaded\n");
	printf("================\n");
}

void	print_all_textures(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	printf("\nDEBUG: Texture Information\n");
	while (i < TEXTURE_SIZE)
	{
		if (game->texture[i])
			print_texture_info(game->texture[i], i);
		else
			printf("no texture[%d]\n", i);
		i++;
	}
	print_texture_info(game->door, TEXTURE_SIZE);
}

void	print_map(char **double_array)
{
	int	i;

	i = -1;
	while (double_array[++i])
		ft_putstr_fd(double_array[i], 1);
	ft_putstr_fd("\n", 1);
}
