/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:02:56 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/12/31 13:13:42 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// if !texture.image_data: check for path existence and permissions
t_texture	*extract_info_process(char **words)
{
	t_texture	*texture;

	texture = (t_texture *) my_calloc(1, sizeof(t_texture));
	texture->image_name = str_trim_and_free(ft_strdup(words[0]));
	texture->image_path = str_trim_and_free(ft_strdup(words[1]));
	texture->image_data = xpm_to_binary(texture->image_path);
	if (texture->image_data == NULL)
	{
		texture->colour = get_colour(words[1]);
		if (texture->colour == -1)
			ft_print_error("Failed to load image or colour\n");
	}
	return (texture);
}

/*
** TODO this one ain't working
** colour is passed as R,G,B
** so i want con convert this into the int
** 0xRRGGBB
*/
int	get_colour(const char *str)
{
	int	colour;

	colour = 0;
	while (*str && ft_issapaces(*str))
		str++;
	return (colour);
}

// Keeping debug logs for now
t_image	*xpm_to_binary(char *image_path)
{
	t_image	*img;

	// // Debug output
	// printf("\n=== Texture Loading Debug ===\n");
	// printf("Original path: %s\n", image_path);
	// MLX validation
	if (!ft_game() || !ft_game()->mlx || !ft_game()->mlx->mlx)
	{
		// printf("Error: MLX not properly initialized\n");
		return (NULL);
	}
	// File existence check
	if (access(image_path, F_OK | R_OK) == -1)
	{
		// printf("File access error for '%s': %s\n"
			// , image_path, strerror(errno));
		return (NULL);
	}
	// printf("Debug: Loading texture from: %s\n", image_path);
	// MLX loading
	img = (t_image *)my_calloc(1, sizeof(t_image));
	if (!img)
	{
		// printf("Memory allocation failed\n");
		return (NULL);
	}
	img->img = mlx_xpm_file_to_image(ft_game()->mlx->mlx,
			image_path, &img->width, &img->height);
	if (!img->img)
	{
		// printf("MLX XPM loading failed for: %s\n", image_path);
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img,
			&img->bpp, &img->len_line, &img->endian);
	if (!img->addr)
	{
		// printf("MLX get data address failed\n");
		mlx_destroy_image(ft_game()->mlx->mlx, img->img);
		free(img);
		return (NULL);
	}
	return (img);
}
