/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:25:51 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/22 23:48:13 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E'
		|| c == 'W')
		return (1);
	return (0);
}

static	int	check_map_char(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
				&& map[i][j] != 'W' && map[i][j] != '0'
				&& map[i][j] != '1' && map[i][j] != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	is_duplicated_player(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_player_char(map[i][j]) == 1)
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

static void	ft_spread(char **arr, int x, int y, int nbr_line)
{
	int	i;
	int	j;

	i = y;
	j = x;
	arr[i][j] = '2';
	if (i > 0 && (arr[i - 1][j] == '0'
		|| ft_isspace(arr[i - 1][j])))
		ft_spread(arr, x, y - 1, nbr_line);
	if (i < nbr_line && (arr[i + 1][j] == '0'
		|| ft_isspace(arr[i + 1][j])))
		ft_spread(arr, x, y + 1, nbr_line);
	if (j > 0 && (arr[i][j - 1] == '0'
		|| ft_isspace(arr[i][j - 1])))
		ft_spread(arr, x - 1, y, nbr_line);
	if (j < ft_strlen(arr[i]) - 1 && (arr[i][j + 1] == '0'
		|| ft_isspace(arr[i][j + 1])))
		ft_spread(arr, x + 1, y, nbr_line);
	return ;
}

int	is_map_valid(t_data *data)
{
	char	**copy_map;

	data->map_height = ft_array_len((void **) data->map);
	data->map_width = get_size_line_max(data->map);
	if (!check_map_char(data->map) || is_duplicated_player(data->map)
		|| check_size_map(data))
		return (error_map());
	copy_map = ft_copy_tab(data->map);
	copy_map = realloc_copy_map(copy_map);
	ft_spread(copy_map, (int)data->player[0],
		(int)data->player[1], ft_array_len((void **) data->map) - 1);
	if (check_wall(copy_map) == 0)
	{
		ft_free(copy_map);
		return (error_map());
	}
	ft_free(copy_map);
	return (1);
}
