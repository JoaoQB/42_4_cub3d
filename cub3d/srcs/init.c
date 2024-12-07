/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:52:20 by fandre-b          #+#    #+#             */
/*   Updated: 2024/12/07 17:59:37 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>


int main(int argc, char **argv){
	file_to_str(argv[1]);
	extract_images(file_str);
	extract_map(file_str);
	check_map(ft_game()->map);
	init_struct();
	//raycasting
	// mlx_key_hook(f->win, handle_key, f);
	// mlx_mouse_hook(f->win, handle_mouse, f);
	mlx_hook(f->win, 17, 0, handle_close, f);
	mlx_loop_hook(f->mlx, f->info.loop_func, f);
	mlx_loop(f->mlx);
}

void	xpm_to_binary()
{
	// alocate new image struct and save the image
	img.img = mlx_xpm_file_to_image(mlx.mlx, "path/to/your/image.jpg", &img.width, &img.height);
	if (img.img == NULL)
		fprintf(stderr, "Failed to load image\n");
	ft_game()->textures[0].addr = mlx_get_data_addr(ft_game()->textures[0].img, &ft_game()->textures[0].bpp, &ft_game()->textures[0].len_line, &ft_game()->textures[0].endian);
}

void	init_struct(t_fractol *f)
{
	init_mlx(f);
	//need struct for minimap (same size as the screen, pixel(x,y) = scren_size/mini_map_size)

	//need struct for FOV (lets try 120) num_rays = WIDTH
	//need struct for angles (do i need tho? FOV/num_rays)
	//need struct for raycasting (x num_rays) (60 up 70 down 1.70m)
	f->info.ray_distance = calloc (sizeof(double) * (WIDTH)); //num_rays
	return ;
}

void	init_mlx(t_fractol *f)
{
	f->mlx = mlx_init();
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, f->name);
	f->img.img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	f->img.addr = mlx_get_data_addr(f->img.img, &f->img.bpp, \
	&f->img.len_line, &f->img.endian);
	return ;
}

void	my_pixel_put(t_data *img, int x, int y, int colour)
{
	int	offset;

	offset = (y * img->len_line) + (x * (img->bpp / 8));
	*(unsigned int *)(img->addr + offset) = colour;
}

void	draw_minimap(void)
{
	int x;
	int y;

	x = -1;
	while (++x < ft_game()->map_width)
	{
		y = -1;
		while (++y < ft_game()->map_height)
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
			my_mlx_pixel_put(&ft_game()->img, i, j, color);
			j++;
		}
		i++;
	}
}
