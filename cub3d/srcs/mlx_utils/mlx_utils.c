/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:20:21 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/09 18:41:21 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put_faded(int x, int y, int colour, double dist)
{
	double	fading;
	int		rgb[3];
	int		fog[3];
	int		final[3];

	fading = exp(-dist * ft_game()->ctl.fade);
	rgb[0] = (colour >> 16) & 0xFF;
	rgb[1] = (colour >> 8) & 0xFF;
	rgb[2] = colour & 0xFF;
	fog[0] = (BLACK_COLOR >> 16) & 0xFF;
	fog[1] = (BLACK_COLOR >> 8) & 0xFF;
	fog[2] = BLACK_COLOR & 0xFF;
	final[0] = (int)(rgb[0] * fading + fog[0] * (1 - fading));
	final[1] = (int)(rgb[1] * fading + fog[1] * (1 - fading));
	final[2] = (int)(rgb[2] * fading + fog[2] * (1 - fading));
	fading = (final[0] << 16) | (final[1] << 8) | final[2];
	my_pixel_put(&ft_game()->mlx->img, x, y, fading);
}

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
	rgb = ft_split((char *)str, ',');
	if (ft_wordcount((char *)str, ',') != 3)
		return (-1);
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
