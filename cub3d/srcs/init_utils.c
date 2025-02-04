/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:02:56 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/04 17:37:58 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*extract_info_process(char **words)
{
	t_texture	*texture;
	int			i;

	i = -1;
	while (words[++i])
		;
	if (i != 2)
		ft_print_error("Textures: Invalid texture format");
	texture = (t_texture *) my_calloc(1, sizeof(t_texture));
	texture->image_name = str_trim_and_free(ft_strdup(words[0]));
	texture->image_path = str_trim_and_free(ft_strdup(words[1]));
	return (texture);
}

int	get_colour(const char *str)
{
	int		colour;
	char	**rgb;
	int 	i;

	colour = 0;
	while (*str && ft_isspaces(*str))
		str++;
	if (ft_wordcount((char *)str, ',') != 3)
		ft_print_error("Colors: Invalid colour format");
	rgb = ft_split((char *)str, ',');
	i = -1;
	colour = 0;
	while (rgb[++i])
	{
		colour |= ft_atoi(rgb[i]) << 8 * (2 - i);
		if (errno == EINVAL)
		{
			free_frases(rgb);
			ft_print_error("Colors: Invalid colour format");
		}
	}
	free_frases(rgb);
	return (colour);
}

t_image	*xpm_to_binary(char *image_path)
{
	t_image	*img;

	if (!ft_game() || !ft_game()->mlx || !ft_game()->mlx->mlx)
		ft_print_error("MLX: not properly initialized");
	if (access(image_path, F_OK | R_OK) == -1)
		return (NULL);
	img = (t_image *)my_calloc(1, sizeof(t_image));
	img->img = mlx_xpm_file_to_image(ft_game()->mlx->mlx,
			image_path, &img->width, &img->height);
	if (!img->img)
		ft_print_error("MLX: XPM loading failed");
	img->addr = mlx_get_data_addr(img->img,
			&img->bpp, &img->len_line, &img->endian);
	if (!img->addr)
		ft_print_error("MLX: get data address failed");
	return (img);
}
