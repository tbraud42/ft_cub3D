/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_camera_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 07:45:05 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/23 15:23:21 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
