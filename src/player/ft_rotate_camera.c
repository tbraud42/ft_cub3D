/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 07:45:05 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/22 07:45:22 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_left_arrow(t_data *data)
{
	data->d_player[2] = fix_ang_rad(data->d_player[2] + 0.15708);
	data->d_player[0] = cos(data->d_player[2]) * 5;
	data->d_player[1] = -sin(data->d_player[2]) * 5;
}

void	ft_right_arrow(t_data *data)
{
	data->d_player[2] = fix_ang_rad(data->d_player[2] - 0.15708);
	data->d_player[0] = cos(data->d_player[2]) * 5;
	data->d_player[1] = -sin(data->d_player[2]) * 5;
}
