/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 04:56:39 by tbraud            #+#    #+#             */
/*   Updated: 2025/01/20 20:41:33 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_forward(t_data *data)
{

	while (data->map[(int)((data->player[1] + (data->d_player[1]))) / 64]
		[(int)((data->player[0] + (data->d_player[0]))) / 64] != '1')
	{
		data->player[0] += data->d_player[0];
		data->player[1] += data->d_player[1];
	}
}

void	ft_backward(t_data *data)
{

	while (data->map[(int)((data->player[1] - (data->d_player[1]))) / 64]
		[(int)((data->player[0] - (data->d_player[0]))) / 64] != '1')
	{
		data->player[0] -= data->d_player[0];
		data->player[1] -= data->d_player[1];
	}
}

void	ft_left(t_data *data)
{
	data->d_player[2] = fix_ang_rad(data->d_player[2] + 0.15708);
	data->d_player[0] = cos(data->d_player[2]) * 5;
	data->d_player[1] = -sin(data->d_player[2]) * 5;
}

void	ft_right(t_data *data)
{
	data->d_player[2] = fix_ang_rad(data->d_player[2] - 0.15708);
	data->d_player[0] = cos(data->d_player[2]) * 5;
	data->d_player[1] = -sin(data->d_player[2]) * 5;
}

int	ft_event(int keycode, t_data *data)
{
	if (keycode == ESCAPE)
		ft_exit_mlx(data, 0);
	if (keycode == 'w')
		ft_forward(data);
	else if (keycode == 's')
		ft_backward(data);
	else if (keycode == 'a')
		ft_left(data);
	else if (keycode == 'd')
		ft_right(data);
	return (0);
}
