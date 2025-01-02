/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:45:22 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/01/02 20:46:44 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while ((*s1 && *s2) && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_startswith(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if (s2[i] == '\0')
		return (0);
	return (1);
}

char	*str_trim_and_free(char *str)
{
	char	*start;
	char	*end;
	char	*result;
	size_t	len;

	if (!str)
		return (NULL);
	start = str;
	while (*start && (*start == ' ' || *start == '\t' || *start == '\n'))
		start++;
	end = str + ft_strlen(str) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	len = end - start + 2;
	result = (char *)malloc(len + 1);
	if (!result)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(result, start, len);
	free(str);
	return (result);
}
