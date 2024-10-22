/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:09:34 by tao               #+#    #+#             */
/*   Updated: 2024/10/21 10:30:37 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strlen(char *arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	ft_strncmp(char *first, char *second, size_t length)
{
	size_t			index;
	unsigned char	*s1;
	unsigned char	*s2;

	index = 0;
	s1 = (unsigned char *) first;
	s2 = (unsigned char *) second;
	while ((s1[index] || s2[index]) && index < length)
	{
		if (s1[index] != s2[index])
			return ((int) s1[index] - (int) s2[index]);
		index++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	sum;

	sum = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ((str[i] - '0' >= 0 && str[i] - '0' <= 9))
	{
		sum = sum * 10 + str[i] - '0';
		i++;
	}
	return (sum * sign);
}

int	ft_count_line(int fd, char *line)
{
	int nbr_line;

	nbr_line = 0;
	line = get_next_line(fd);
	if (!line || line[0] == '\n')
	{
		free(line);
		return (0);
	}
	while (line != NULL)
	{
		nbr_line++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (nbr_line);
}
