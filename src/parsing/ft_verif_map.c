/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:25:51 by brguicho          #+#    #+#             */
/*   Updated: 2024/11/07 11:02:14 by brguicho         ###   ########.fr       */
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
	if (count == 0)
		return (1);
	return (0);
}

char  **ft_spread(char **final_map, int x, int y, int nbr_line)
{
	int	nbr_char;

	nbr_char = ft_strlen(final_map[0]) - 1;
	final_map[y][x] = 'P';
	if (final_map[y + 1][x] != '1'
		&& final_map[y + 1][x] != 'P'
		&& y + 1 < nbr_line)
		ft_spread(final_map, x, y + 1, nbr_line);
	if (final_map[y - 1][x] != '1'
		&& final_map[y - 1][x] != 'P'
		&& y - 1 > 0)
		ft_spread(final_map, x, y - 1, nbr_line);
	if (final_map[y][x + 1] != '1' && x + 1 < nbr_char
		&& final_map[y][x + 1] != 'P')
		ft_spread(final_map, x + 1, y, nbr_line);
	if (final_map[y][x - 1] != '1' && x - 1 > 0
		&& final_map[y][x - 1] != 'P')
		ft_spread(final_map, x - 1, y, nbr_line);
	return (final_map);
}
