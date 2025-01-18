/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:40:08 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/18 10:37:46 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**realloc_copy_map(char **cpy)
{
	int	i;

	i = 0;
	while (cpy[i])
	{
		cpy[i] = ft_realloc(cpy[i],
				get_size_line_max(cpy), ft_strlen(cpy[i]) + 1);
		i++;
	}
	return (cpy);
}

int	check_wall(char **copy_map)
{
	int	i;
	int	j;

	i = -1;
	while (copy_map[++i])
	{
		j = -1;
		while (copy_map[i][++j])
		{
			if ((i == 0 && copy_map[i][j] == '2')
					|| (i == ft_array_len((void **) copy_map) - 1
					&& copy_map[i][j] == '2'))
				return (0);
			if ((j == 0 && copy_map[i][j] == '2')
						|| (j == ft_strlen(copy_map[i]) - 1
						&& copy_map[i][j] == '2'))
				return (0);
		}
	}
	return (1);
}
