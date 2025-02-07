/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:18:52 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/07 11:12:06 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*ft_game(void)
{
	static t_game	game_s;

	return (&game_s);
}

void	init_game(char *file_path)
{
	init_control();
	init_parsing(file_path);
	init_mlx();
	init_texture(ft_game());
	init_ray(ft_game());
	render();
}

int nft_wordcount(char *str, char c)
{
	int words;
	
	if (!str)
		return (0);
	words = 1;
	while (*str)
	{
		// printf("words %s\n", str);
		while (*str && *str == c)
			str++;
		while (*str && *str != c)
			str++;
		if (*str && *str == c)
		{
			words++;
			str++;
		}
	}
	return words;
}

char **ft_split(char *str, char c)
{
	char	**map;
	int		i;
	int		j;

	map = (char **) my_calloc(nft_wordcount(str, c) + 1, sizeof(char *));
	j = -1;
	while (*str)
	{
		i = 0;
		while (str[i] && str[i] == c)
			i++;
		while (str[i] && str[i] != c)
			i++;
		map[++j] = ft_strnjoin(NULL, str, i);
		str += i;
		if (*str && *str == c)
			str++;
	}
	return (map);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		ft_print_err("Please run ./cub3d <file_path.cub> ");
	init_game(argv[1]);
	mlx_loop_hook(ft_game()->mlx->mlx, render, NULL);
	mlx_loop(ft_game()->mlx->mlx);
	return (0);
}
