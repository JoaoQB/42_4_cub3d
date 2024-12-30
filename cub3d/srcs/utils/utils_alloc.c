/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:29:42 by fandre-b          #+#    #+#             */
/*   Updated: 2024/12/11 15:36:05 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *ft_strdup(char *str)
{
	int i;
	char *new_str;

	i = 0;
	while (str[i])
		i++;
	new_str = (char *) my_calloc(i + 1, sizeof(char));
	i = -1;
	while (str[++i])
		new_str[i] = str[i];
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strnjoin(char *old_str, char *str_add, int size)
{
	int		len_old;
	int		len_new;
	char	*new_str;

	if (!str_add || !str_add[0] || size == 0)
		return (old_str);
	len_old = ft_strlen(old_str);
	len_new = ft_strlen(str_add);
	if (len_new < size || size == -1)
		size = len_new;
	new_str = (char *) my_calloc(size + len_old + 1, sizeof(char));
	ft_strlcpy(new_str, old_str, len_old + 1);
	ft_strlcpy(&new_str[len_old], str_add, size + 1);
	free(old_str);
	return (new_str);
}

char **ft_split(char *str, char c)
{
	char **map;
	int i;
	int j;

	map = (char **) my_calloc(ft_wordcount(str, c) + 1, sizeof(char *));
	j = -1;
	while (*str)
	{
		i = 0;
		while (*str && ft_issapaces(*str))
			str++;
		while (str[i] && str[i] != c)
			i++;
		if (str[i] && str[i] == c)
			i++;
		map[++j] = ft_strnjoin(NULL, str, i);
		str += i;
	}
	map[++j] = NULL;
	return (map);
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