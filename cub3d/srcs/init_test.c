/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:10:29 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/01/02 20:13:32 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_texture_array(char *textures[7][2])
{
	textures[0][0] = "EA";
	textures[0][1] = "./includes/textures/water_texture2.xpm";
	textures[1][0] = "NO";
	textures[1][1] = "./includes/textures/water_texture.xpm";
	textures[2][0] = "WE";
	textures[2][1] = "./includes/textures/wall_blackhole.xpm";
	textures[3][0] = "SO";
	textures[3][1] = "./includes/textures/wall_gold_energy.xpm";
	textures[4][0] = "F";
	textures[4][1] = "220,100,0";
	textures[5][0] = "C";
	textures[5][1] = "225,30,0";
	textures[6][0] = NULL;
	textures[6][1] = NULL;
}

void	init_test_textures(t_game *game)
{
	char		*textures[7][2];
	int			i;
	t_texture	*texture;

	setup_texture_array(textures);
	i = 0;
	while (textures[i][0] != NULL)
	{
		texture = extract_info_process(textures[i]);
		if (strcmp(textures[i][0], "EA") == 0)
			game->texture[0] = texture;
		else if (strcmp(textures[i][0], "NO") == 0)
			game->texture[1] = texture;
		else if (strcmp(textures[i][0], "WE") == 0)
			game->texture[2] = texture;
		else if (strcmp(textures[i][0], "SO") == 0)
			game->texture[3] = texture;
		else if (strcmp(textures[i][0], "F") == 0)
			game->texture[4] = texture;
		else if (strcmp(textures[i][0], "C") == 0)
			game->texture[5] = texture;
		i++;
	}
}

// TODO init player from .cub file
void	init_test_player(void)
{
	char	**map;

	if (!ft_game())
		return ;
	map = malloc(sizeof(char *) * 8);
	map[0] = strdup("111111111111111");
	map[1] = strdup("100000000000001");
	map[2] = strdup("110110000001011");
	map[3] = strdup("1110000P0000011");
	map[4] = strdup("110000000000011");
	map[5] = strdup("110000101000011");
	map[6] = strdup("111111111111111");
	map[7] = NULL;
	ft_game()->map = map;
	ft_game()->player.pos.x = 7;
	ft_game()->player.pos.y = 3;
	ft_game()->player.dir_angle = SOUTH;
	ft_game()->player.speed = 1;
	init_test_textures(ft_game());
	printf("!! Player initialized:\n");
	printf("!! Position: (%f, %f)\n",
		ft_game()->player.pos.x, ft_game()->player.pos.y);
	printf("!! Direction angle: %f\n", ft_game()->player.dir_angle);
	printf("!! Speed: %f\n", ft_game()->player.speed);
}
