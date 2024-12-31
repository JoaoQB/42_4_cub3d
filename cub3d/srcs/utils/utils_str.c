/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:27:11 by fandre-b          #+#    #+#             */
/*   Updated: 2024/12/31 11:10:51 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_putstr_fd(char *str, int fd)
{
	int ret;
	if (!str)
		return ;
	ret = write(fd, str, ft_strlen(str));
	(void)ret;
}


int	ft_wordcount(const char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && c == str[i])
			i++;
		if (str[i] && str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

int ft_strlen(const char *str)
{
	int i;

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

char* ft_strchr(char *s, int c)
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
	return (unsigned char)*s1 - (unsigned char)*s2;
}

int ft_startswith(const char *s1, const char *s2) {
    int i;

	i = 0;
	while (s1[i] && s2[i])
	{
        if (s1[i] != s2[i])
            break;
		i++;
    }
	if (s2[i] == '\0')
		return 0;
    return 1;
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
