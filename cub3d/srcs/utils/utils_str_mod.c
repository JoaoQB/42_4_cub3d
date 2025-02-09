/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str_mod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:45:22 by jqueijo-          #+#    #+#             */
/*   Updated: 2025/02/09 18:25:55 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	i = 0;
	sign = 1;
	while (ft_isspaces(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = (res * 10) + nptr[i++] - '0';
	if (nptr[i] != '\0' && (nptr[i] < '0' || nptr[i] > '9'))
		errno = EINVAL;
	return (res * sign);
}

char	*ft_strtrim(char *str, char *trim_str)
{
	char	*start;
	char	*end;
	char	*result;
	size_t	len;

	if (!str || !*str || !trim_str)
		return (NULL);
	start = str;
	while (*start && (ft_strchr(trim_str, *start)))
		start++;
	end = str + ft_strlen(str) - 1;
	while (end > start && (ft_strchr(trim_str, *end)))
		end--;
	len = end - start + 2;
	result = (char *)my_calloc(len + 1, sizeof(char));
	if (!result)
		return (free(str), NULL);
	ft_strlcpy(result, start, len);
	return (free(str), result);
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

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((char *)s + i) = c;
		i++;
	}
	return (s);
}

// char *ft_strtrim(char *str, char *set)
// {
// 	char	*result;
// 	size_t	len;
// 	size_t	start;
// 	size_t	end;

// 	if (!str || !*str || !set)
// 		return (NULL);
// 	start = 0;
// 	while (str[start] && (ft_strchr(set, str[start])))
// 		start++;
// 	end = ft_strlen(str);
// 	while (end > start && (ft_strchr(set, str[end - 1])))
// 		end--;
// 	len = end - start;
// 	result = (char*)my_calloc( + 1, sizeof(char));
// 	ft_strlcpy(result, str, len);
// 	printf("result = %s\n", result);
// 	return (free(str), result);
// }
