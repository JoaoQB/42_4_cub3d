/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:20:34 by fandre-b          #+#    #+#             */
/*   Updated: 2025/02/04 17:33:06 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_isspaces(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\r')
		return (true);
	return (false);
}

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

void	ft_print_error(char *str)
{
	ft_putstr_fd("\n\nError: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	free_game();
	exit(1);
}