/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_direction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:27:54 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/20 13:03:19 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_player_direction(t_data *data)
{
	if (data->d_player[2] == 'W')
		data->d_player[2] = PI;
	else if (data->d_player[2] == 'E')
		data->d_player[2] = 0;
	else if (data->d_player[2] == 'S')
		data->d_player[2] = (3 * PI) / 2;
	else if (data->d_player[2] == 'N')
		data->d_player[2] = (PI / 2) - (0.0174533 * 13); // ça le centre mais pas les autre, trouver l'erreur
	data->d_player[0] = cos(data->d_player[2]) * 5;
	data->d_player[1] = -sin(data->d_player[2]) * 5;
	data->player[0] *= size_one_block;
	data->player[1] *= size_one_block;
}
