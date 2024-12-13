/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:52:20 by fandre-b          #+#    #+#             */
/*   Updated: 2024/12/11 15:35:54 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

t_texture *extract_info_process(char **words)
{
	t_texture *texture;

	texture = (t_texture *) my_calloc(1, sizeof(t_texture));
	texture->image_name = ft_strdup(words[0]);
	texture->image_path = ft_strdup(words[1]);
	texture->image_data = xpm_to_binary(texture->image_path);
	if (texture->image_data == NULL) // check for path existence and permissions 
	{
		texture->colour = get_colour(words[1]);
		if (texture->colour == -1)
			ft_print_error("Failed to load image or colour\n");
	}
	return (texture);
}

int get_colour(const char *str)
{
	// clour is passed as R,G,B
	//so i want con convert this into the int 
	int colour;

	colour = 0; // 0xRRGGBB
	while (*str && ft_issapaces(*str))
		str++;

	return (colour);
}

t_image*	xpm_to_binary(char *image_path)
{
	t_image *img;

	img = (t_image *) my_calloc(1, sizeof(t_image));
	img->img = mlx_xpm_file_to_image(&ft_game()->mlx->mlx, image_path, &img->width, &img->height);
	if (img->img == NULL)
		return (NULL);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len_line, &img->endian);
	//TODO delete
	if (img->img != NULL)
		mlx_put_image_to_window (ft_game()->mlx, ft_game()->mlx->win, img->img, 0, 0);
	return (img);
}

static void init_hash_table(void)
{
	ft_game()->ctl.hash_table = ft_hash_table();
	ft_hash_table()->size = HASH_TABLE_SIZE;
	ft_hash_table()->buckets = (t_bucket **) my_calloc(ft_hash_table()->size , sizeof(t_bucket *));
	// ft_bzero(ft_hash_table()->buckets, ft_hash_table()->size * sizeof(t_bucket *));
	// memset(ft_hash_table()->buckets, 0, ft_hash_table()->size * sizeof(t_bucket *));
}

void	init_struct(void)
{

	init_mlx();
	ft_game()->player = (t_player *) my_calloc(1, sizeof(t_player));
	ft_game()->player->angle = UNKNOWN;
	init_hash_table();
	//need struct for minimap (same size as the screen, pixel(x,y) = scren_size/mini_map_size)
	
	//need struct for raycasting (x num_rays) (60 up 70 down, payer height 1.70m)
	// f->info.ray_distance = my_calloc (sizeof(double) * (WIDTH)); //num_rays
	//need struct for FOV (lets try 120) num_rays = WIDTH
	//need struct for angles (do i need tho? FOV/num_rays) 
}

