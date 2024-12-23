/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 04:56:39 by tbraud            #+#    #+#             */
/*   Updated: 2024/12/23 04:43:05 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_forward(t_data *data)
{
	if (data->map[(int)((data->player[1] + (data->d_player[1] * 5))) / 64][(int)((data->player[0] + (data->d_player[0] * 5))) / 64] == '1')
	{
		while (data->map[(int)((data->player[1] + (data->d_player[1]))) / 64][(int)((data->player[0] + (data->d_player[0]))) / 64] != '1')
		{
			data->player[0] += data->d_player[0];
			data->player[1] += data->d_player[1];
		}
		return ;
	}
	data->player[0] += data->d_player[0] * 5;
	data->player[1] += data->d_player[1] * 5;
}

static void	ft_backward(t_data *data)
{
	if (data->map[(int)((data->player[1] - (data->d_player[1] * 5))) / 64][(int)((data->player[0] - (data->d_player[0] * 5))) / 64] == '1')
	{
		while (data->map[(int)((data->player[1] - (data->d_player[1]))) / 64][(int)((data->player[0] - (data->d_player[0]))) / 64] != '1')
		{
			data->player[0] -= data->d_player[0];
			data->player[1] -= data->d_player[1];
		}
		return ;
	}
	data->player[0] -= data->d_player[0] * 5;
	data->player[1] -= data->d_player[1] * 5;
}

static void	ft_left(t_data *data)
{
	data->d_player[2] = fix_ang_rad(data->d_player[2] + 0.15708);
	data->d_player[0] = cos(data->d_player[2]) * 5;
	data->d_player[1] = -sin(data->d_player[2]) * 5;
}

static void	ft_right(t_data *data)
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

int	ft_mouse(t_data *data)
{
	int	x;
	int	y;
	int	widht_comp;

	widht_comp = (int)(widht * 0.5);
	mlx_mouse_get_pos(data->mlx, data->mlx_win, &x, &y);
	if (x > widht_comp)
		ft_right(data);
	else if (x < widht_comp)
		ft_left(data);
	mlx_mouse_move(data->mlx, data->mlx_win, widht_comp, (int)(height * 0.5));
	return (0);
}
