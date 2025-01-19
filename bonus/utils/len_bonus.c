/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:14:41 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/19 22:06:05 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

int	ft_array_len(void **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

int	get_size_line_max(char **arr)
{
	int	i;
	int	size_max;

	i = 0;
	size_max = 0;
	while (arr[i])
	{
		if (ft_strlen(arr[i]) > size_max)
			size_max = ft_strlen(arr[i]);
		i++;
	}
	return (size_max);
}
