/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:20:21 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/07 11:17:17 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	my_pixel_put(t_image *img, int x, int y, int colour)
{
	int	offset;

	offset = (y * img->len_line) + (x * (img->bpp / 8));
	*(unsigned int *)(img->addr + offset) = colour;
}

int	get_colour(const char *str)
{
	int		colour;
	char	**rgb;
	int		i;

	colour = 0;
	while (*str && ft_isspaces(*str))
		str++;
	if (ft_wordcount((char *)str, ',') != 3)
		ft_print_err("Colors: Invalid colour format");
	rgb = ft_split((char *)str, ',');
	i = -1;
	colour = 0;
	while (rgb[++i])
	{
		colour |= ft_atoi(rgb[i]) << 8 * (2 - i);
		if (errno == EINVAL)
		{
			free_frases(rgb);
			ft_print_err("Colors: Invalid colour format");
		}
	}
	free_frases(rgb);
	return (colour);
}

t_image	*xpm_to_binary(char *image_path)
{
	t_image	*img;

	if (!ft_game() || !ft_game()->mlx || !ft_game()->mlx->mlx)
		ft_print_err("MLX: not properly initialized");
	if (access(image_path, F_OK | R_OK) == -1)
		return (NULL);
	img = (t_image *)my_calloc(1, sizeof(t_image));
	img->img = mlx_xpm_file_to_image(ft_game()->mlx->mlx,
			image_path, &img->width, &img->height);
	if (!img->img)
		ft_print_err("MLX: XPM loading failed");
	img->addr = mlx_get_data_addr(img->img,
			&img->bpp, &img->len_line, &img->endian);
	if (!img->addr)
		ft_print_err("MLX: get data address failed");
	return (img);
}
