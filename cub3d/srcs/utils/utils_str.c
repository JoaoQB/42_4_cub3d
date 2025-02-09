/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:27:11 by fandre-b          #+#    #+#             */
/*   Updated: 2025/02/09 16:55:51 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	ret;

	if (!str)
		return ;
	ret = write(fd, str, ft_strlen(str));
	(void)ret;
}

int ft_wordcount(char *str, char c)
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

char	*ft_strcat(char *dest, const char *src)
{
	char	*dest_end;

	dest_end = dest;
	while (*dest_end != '\0')
		dest_end++;
	while (*src != '\0')
	{
		*dest_end = *src;
		dest_end++;
		src++;
	}
	*dest_end = '\0';
	return (dest);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	count;

	if (!dest || !src)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	count = 0;
	while (src[count] != '\0' && count < (size - 1))
	{
		dest[count] = src[count];
		count++;
	}
	dest[count] = '\0';
	return (ft_strlen(src));
}
