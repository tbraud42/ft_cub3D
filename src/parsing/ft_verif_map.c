/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:25:51 by brguicho          #+#    #+#             */
/*   Updated: 2024/11/05 10:26:28 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E'
		|| c == 'W')
		return (1);
	return (0);
}

int	is_duplicated_player(char **map)
{
	int i;
	int j;
	int count;
	
	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_char(map[i][j]) == 1)
			{
				count++;
				if (count > 1)
					return (1);
			}
			j++;
		}
		i++;
	}
	if (count = 0)
		return (1);
	return (0);
}

int is_map_close(t_data *data)
{
	
}