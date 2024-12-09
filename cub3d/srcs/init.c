/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:52:20 by fandre-b          #+#    #+#             */
/*   Updated: 2024/12/08 14:23:26 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

t_image*	xpm_to_binary(char *image_path)
{
	t_image *img;

	img = (t_image *) my_calloc(1, sizeof(t_image));
	// alocate new image struct and save the image
	img->img = mlx_xpm_file_to_image(ft_game()->mlx->mlx, image_path, &img->width, &img->height);
	if (img->img == NULL)
		fprintf(stderr, "Failed to load image\n");
	img->addr = mlx_get_data_addr(img, &img->bpp, &img->len_line, &img->endian);
	return (img);
}

void	init_struct()
{

	init_mlx();
	//need struct for minimap (same size as the screen, pixel(x,y) = scren_size/mini_map_size)
	
	//need struct for raycasting (x num_rays) (60 up 70 down, payer height 1.70m)
	// f->info.ray_distance = my_calloc (sizeof(double) * (WIDTH)); //num_rays
	//need struct for FOV (lets try 120) num_rays = WIDTH
	//need struct for angles (do i need tho? FOV/num_rays) 
}

void	init_mlx()
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, \
	&mlx->img.len_line, &mlx->img.endian);
	ft_game()->mlx = mlx;
	return ;
}

void	my_pixel_put(t_image *img, int x, int y, int colour)
{
	int	offset;

	offset = (y * img->len_line) + (x * (img->bpp / 8));
	*(unsigned int *)(img->addr + offset) = colour;
}

void	draw_minimap(int offset_x, int offset_y)
{
	int x;
	int y;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
			draw_by_scale(x, y, MINIMAP_SCALE, offset_x, offset_y);
			//i can pass an structure of object to be drawn instead like
			//with map dimentions, rescale, offset(position) and image dimension
	}
}

void draw_by_scale(int x, int y, int scale, int offset_x, int offset_y) 
{
	int i;
	int j;
	int color;

	i = x * scale + offset_x;
	while (i < (x + 1) * scale + offset_x)
	{
		j = y * scale + offset_y;
		while (j < (y + 1) * scale + offset_y)
		{
			color = ft_game()->map[y][x] == 1 ? 0x00FF00 : 0x000000;
			my_pixel_put(&ft_game()->mlx->img, i, j, color);
			j++;
		}
		i++;
	}
}

void *my_calloc(int num, int size)
{
    void *ptr;

    ptr = malloc(num * size);
    if (!ptr)
        return NULL;
    memset(ptr, 0, num * size);
    return ptr;
}

void*	ft_bzero(void *ptr, int n)
{
	memset(ptr, 0, n); //TODO ft_memset
	return (ptr);
}
