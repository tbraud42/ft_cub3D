/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 04:56:39 by tbraud            #+#    #+#             */
/*   Updated: 2025/01/22 04:21:29 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_forward(t_data *data)
{
	int		i;
	double	step[2];

	i = 0;
	step[0] = data->d_player[1] * 0.1;
	step[1] = data->d_player[0] * 0.1;
	while (i < 15)
	{
		if (data->map[(int)(data->player[1] + step[0] + 2) / 64]
			[(int)(data->player[0] + step[1] + 2) / 64] == '1')
			break ;
		if (data->map[(int)(data->player[1] + step[0] - 2) / 64]
			[(int)(data->player[0] + step[1] - 2) / 64] == '1')
			break ;
		if (data->map[(int)(data->player[1] + step[0] + 2) / 64]
			[(int)(data->player[0] + step[1] - 2) / 64] == '1')
			break ;
		if (data->map[(int)(data->player[1] + step[0] - 2) / 64]
			[(int)(data->player[0] + step[1] + 2) / 64] == '1')
			break ;
		data->player[0] += step[1];
		data->player[1] += step[0];
		i++;
	}
}

void	ft_backward(t_data *data)
{
	int		i;
	double	step[2];

	i = 0;
	step[0] = data->d_player[1] * 0.1;
	step[1] = data->d_player[0] * 0.1;
	while (i < 15)
	{
		if (data->map[(int)(data->player[1] - step[0] + 2) / 64]
			[(int)(data->player[0] - step[1] + 2) / 64] == '1')
			break ;
		if (data->map[(int)(data->player[1] - step[0] - 2) / 64]
			[(int)(data->player[0] - step[1] - 2) / 64] == '1')
			break ;
		if (data->map[(int)(data->player[1] - step[0] + 2) / 64]
			[(int)(data->player[0] - step[1] - 2) / 64] == '1')
			break ;
		if (data->map[(int)(data->player[1] - step[0] - 2) / 64]
			[(int)(data->player[0] - step[1] + 2) / 64] == '1')
			break ;
		data->player[0] -= step[1];
		data->player[1] -= step[0];
		i++;
	}
}

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


void	ft_left(t_data *data)
{
	int		i;
	double	step_x;
	double	step_y;

	i = 0;
	step_x = cos(fix_ang_rad(data->d_player[2] + M_PI_2)) * 0.5;
	step_y = sin(fix_ang_rad(data->d_player[2] + M_PI_2)) * 0.5;
	while (i < 15)
	{
		if (data->map[(int)(data->player[1] - step_y + 2) / 64]
			[(int)(data->player[0] + step_x + 2) / 64] == '1')
			break ;
		if (data->map[(int)(data->player[1] - step_y - 2) / 64]
			[(int)(data->player[0] + step_x - 2) / 64] == '1')
			break ;
		if (data->map[(int)(data->player[1] - step_y + 2) / 64]
			[(int)(data->player[0] + step_x - 2) / 64] == '1')
			break ;
		if (data->map[(int)(data->player[1] - step_y - 2) / 64]
			[(int)(data->player[0] + step_x + 2) / 64] == '1')
			break ;
		data->player[0] += step_x;
		data->player[1] -= step_y;
		i++;
	}
}

void	ft_right(t_data *data)
{
	int		i;
	double	step_x;
	double	step_y;

	i = 0;
	step_x = cos(fix_ang_rad(data->d_player[2] + M_PI_2)) * 0.5;
	step_y = sin(fix_ang_rad(data->d_player[2] + M_PI_2)) * 0.5;
	while (i < 15)
	{
		if (data->map[(int)(data->player[1] + step_y + 2) / 64]
			[(int)(data->player[0] - step_x + 2) / 64] == '1')
			break ;
		if (data->map[(int)(data->player[1] + step_y - 2) / 64]
			[(int)(data->player[0] - step_x - 2) / 64] == '1')
			break ;
		if (data->map[(int)(data->player[1] + step_y + 2) / 64]
			[(int)(data->player[0] - step_x - 2) / 64] == '1')
			break ;
		if (data->map[(int)(data->player[1] + step_y - 2) / 64]
			[(int)(data->player[0] - step_x + 2) / 64] == '1')
			break ;
		data->player[0] -= step_x;
		data->player[1] += step_y;
		i++;
	}
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
	else if (keycode == 65363)
		ft_right_arrow(data);
	else if (keycode == 65361)
		ft_left_arrow(data);
	return (0);
}
