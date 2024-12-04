/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_position.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:47:41 by brguicho          #+#    #+#             */
/*   Updated: 2024/12/04 13:26:36 by brguicho         ###   ########.fr       */
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
				data->player.pos_y = (double) i;
				data->player.pos_x = (double) j;
				data->player.dir = data->map[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
}
