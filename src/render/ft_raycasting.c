/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:53:07 by tbraud            #+#    #+#             */
/*   Updated: 2025/01/21 17:28:22 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_hit_avaible(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i] && i < y)
		i++;
	if (!data->map[i] || i != y)
		return (0);
	while (data->map[i][j] && j < x)
		j++;
	if (j != x)
		return (0);
	if (data->map[i][j] == '1')
		return (1);
	return (0);
}

static void	ft_raycasting_hit(t_data *data, t_ray *math, int dof, int num_dist)
{
	int	map_coords[2];

	while (dof < 30)
	{
		map_coords[0] = (int)(math->ray_data[1]) >> 6;
		map_coords[1] = (int)(math->ray_data[2]) >> 6;
		if (ft_hit_avaible(data, map_coords[0], map_coords[1]))
		{
			math->dist[num_dist] = ft_dist(data->player[0], data->player[1],
					math->ray_data[1], math->ray_data[2]);
			dof = 30;
		}
		else
		{
			math->ray_data[1] += math->ray_step[0];
			math->ray_data[2] += math->ray_step[1];
			dof++;
		}
	}
}

static void	ft_raycasting_vertical(t_data *data, t_ray *math, double tan_ra)
{
	int	dof;

	dof = 0;
	math->dist[0] = 100000;
	if (fabs(cos(math->ray_data[0])) > 0.001)
	{
		calculate_ray_vertical(data, math, tan_ra);
		math->ray_step[1] = -math->ray_step[0] * tan_ra;
		ft_raycasting_hit(data, math, dof, 0);
		return ;
	}
	math->ray_data[1] = data->player[0];
	math->ray_data[2] = data->player[1];
	dof = 30;
	ft_raycasting_hit(data, math, dof, 0);
}

static void	ft_raycasting_horizontal(t_data *data, t_ray *math, double tan_ra)
{
	int	dof;

	dof = 0;
	math->dist[1] = 100000;
	if (fabs(sin(math->ray_data[0])) > 0.001)
	{
		calculate_ray_horizontal(data, math, tan_ra);
		math->ray_step[0] = -math->ray_step[1] * tan_ra;
		ft_raycasting_hit(data, math, dof, 1);
		return ;
	}
	math->ray_data[1] = data->player[0];
	math->ray_data[2] = data->player[1];
	dof = 30;
	ft_raycasting_hit(data, math, dof, 1);
}

void	ft_raycasting(t_data *data, int *win)
{
	t_ray	math;
	int		i;
	double	tmp[2];

	i = -1;
	math.ray_data[0] = fix_ang_rad(data->d_player[2] + deg_to_rad(FOV / 2));
	while (++i < NUM_RAY)
	{
		ft_raycasting_vertical(data, &math, tan(math.ray_data[0]));
		tmp[0] = math.ray_data[1];
		tmp[1] = math.ray_data[2];
		ft_raycasting_horizontal(data, &math, 1.0 / tan(math.ray_data[0]));
		math.side = 0;
		if (math.dist[0] < math.dist[1])
		{
			math.ray_data[1] = tmp[0];
			math.ray_data[2] = tmp[1];
			math.dist[1] = math.dist[0];
			math.side++;
		}
		ft_config_data_texture(data, &math, win, i);
		math.ray_data[0] = fix_ang_rad(math.ray_data[0]
				- deg_to_rad(FOV) / NUM_RAY);
	}
}
