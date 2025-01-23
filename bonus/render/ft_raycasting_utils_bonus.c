/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:02:57 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/23 15:23:21 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

double	deg_to_rad(double angle)
{
	return (angle * M_PI / 180.0);
}

double	fix_ang_rad(double a)
{
	if (a > 2 * M_PI)
		a -= 2 * M_PI;
	if (a < 0)
		a += 2 * M_PI;
	return (a);
}

double	ft_dist(double ax, double ay, double bx, double by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	calculate_ray_horizontal(t_data *data, t_ray *math, double tan_ra)
{
	if (sin(math->ray_data[0]) > 0)
	{
		math->ray_data[2] = (((int)data->player[1] >> 6) << 6) - 0.0001;
		math->ray_data[1] = (data->player[1] - math->ray_data[2])
			* tan_ra + data->player[0];
		math->ray_step[1] = -SIZE_ONE_BLOCK;
	}
	else
	{
		math->ray_data[2] = (((int)data->player[1] >> 6) << 6)
			+ SIZE_ONE_BLOCK;
		math->ray_data[1] = (data->player[1] - math->ray_data[2])
			* tan_ra + data->player[0];
		math->ray_step[1] = SIZE_ONE_BLOCK;
	}
}

void	calculate_ray_vertical(t_data *data, t_ray *math, double tan_ra)
{
	if (cos(math->ray_data[0]) > 0)
	{
		math->ray_data[1] = (((int)data->player[0] >> 6) << 6)
			+ SIZE_ONE_BLOCK;
		math->ray_data[2] = (data->player[0] - math->ray_data[1])
			* tan_ra + data->player[1];
		math->ray_step[0] = SIZE_ONE_BLOCK;
	}
	else
	{
		math->ray_data[1] = (((int)data->player[0] >> 6) << 6) - 0.0001;
		math->ray_data[2] = (data->player[0] - math->ray_data[1])
			* tan_ra + data->player[1];
		math->ray_step[0] = -SIZE_ONE_BLOCK;
	}
}
