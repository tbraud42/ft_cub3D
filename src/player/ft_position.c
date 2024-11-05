/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_position.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:47:41 by brguicho          #+#    #+#             */
/*   Updated: 2024/11/05 10:08:17 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void ft_get_position(t_data *data)
{
	int i;
	int j;
	
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N'
				|| data->map[i][j] == 'S'
				|| data->map[i][j] == 'E'
				|| data->map[i][j] == 'W')
			{
				data->player[0] = (float) i;
				data->player[1] = (float) j;
				data->player_orientation = data->map[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
}
