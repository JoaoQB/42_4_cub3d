/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:27:11 by fandre-b          #+#    #+#             */
/*   Updated: 2025/02/17 17:04:43 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

bool	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (true);
	i = 0;
	while (line[i] && ft_strchr(" \t\r\v\f\n", line[i]))
		i++;
	if (line[i] == '\0')
		return (true);
	return (false);
}

int	ft_wordcount(char *str, char c)
{
	int	words;

	if (!str)
		return (0);
	words = 1;
	while (*str)
	{
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
	return (words);
}

bool	ft_isspaces(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\r')
		return (true);
	return (false);
}
