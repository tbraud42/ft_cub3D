/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_direction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:27:54 by brguicho          #+#    #+#             */
/*   Updated: 2024/12/23 01:44:24 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_player_direction(t_data *data)
{
	if (data->d_player[2] == 'W')
		data->d_player[2] = (3 * PI) / 2;
	else if (data->d_player[2] == 'E')
		data->d_player[2] = PI / 2;
	else if (data->d_player[2] == 'S')
		data->d_player[2] = 0; // inverser avec lui
	else if (data->d_player[2] == 'N')
		data->d_player[2] = PI; // je crois faut inverser
	data->d_player[0] = cosf(data->d_player[2]) * 5;
	data->d_player[1] = sinf(data->d_player[2]) * 5;
}
