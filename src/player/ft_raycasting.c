/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:53:07 by tbraud            #+#    #+#             */
/*   Updated: 2025/01/20 23:23:08 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	ft_hit_avaible(t_data *data, int x, int y)
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

void	ft_raycasting_hit(t_data *data, t_ray *math, int dof, int num_dist)
{
	int	map_coords[2];

	while (dof < 30)
	{
		map_coords[0] = (int)(math->ray_data[1]) >> 6;
		map_coords[1] = (int)(math->ray_data[2]) >> 6;
		if (ft_hit_avaible(data, map_coords[0], map_coords[1]))
		{
			math->dist[num_dist] = ft_dist(data->player[0], data->player[1], math->ray_data[1], math->ray_data[2]);
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

void	ft_raycasting_vertical(t_data *data, t_ray *math, double tan_ra)
{
	int	dof;

	dof = 0;
	if (fabs(cos(math->ray_data[0])) > 0.001)
	{
		if (cos(math->ray_data[0]) > 0)
		{
			math->ray_data[1] = (((int)data->player[0] >> 6) << 6) + size_one_block;
			math->ray_data[2] = (data->player[0] - math->ray_data[1]) * tan_ra + data->player[1];
			math->ray_step[0] = size_one_block;
		}
		else
		{
			math->ray_data[1] = (((int)data->player[0] >> 6) << 6) - 0.0001;
			math->ray_data[2] = (data->player[0] - math->ray_data[1]) * tan_ra + data->player[1];
			math->ray_step[0] = -size_one_block;
		}
		math->ray_step[1] = -math->ray_step[0] * tan_ra;
		ft_raycasting_hit(data, math, dof, 0);
		return ;
	}
	math->ray_data[1] = data->player[0];
	math->ray_data[2] = data->player[1];
	dof = 30;
	ft_raycasting_hit(data, math, dof, 0);
}


void	ft_raycasting_horizontal(t_data *data, t_ray *math, double tan_ra)
{
	int	dof;

	dof = 0;
	if (fabs(sin(math->ray_data[0])) > 0.001)
	{
		if (sin(math->ray_data[0]) > 0)
		{
			math->ray_data[2] = (((int)data->player[1] >> 6) << 6) - 0.0001;
			math->ray_data[1] = (data->player[1] - math->ray_data[2]) * tan_ra + data->player[0];
			math->ray_step[1] = -size_one_block;
		}
		else
		{
			math->ray_data[2] = (((int)data->player[1] >> 6) << 6) + size_one_block;
			math->ray_data[1] = (data->player[1] - math->ray_data[2]) * tan_ra + data->player[0];
			math->ray_step[1] = size_one_block;
		}
		math->ray_step[0] = -math->ray_step[1] * tan_ra;
		ft_raycasting_hit(data, math, dof, 1);
		return ;
	}
	math->ray_data[1] = data->player[0];
	math->ray_data[2] = data->player[1];
	dof = 30;
	ft_raycasting_hit(data, math, dof, 1);
}

t_texture *ft_get_texture_by_cardinal(t_data *data, t_ray *math)
{
	t_texture *texture;

	if (math->side)
	{
		if (cos(math->ray_data[0]) > 0)
			texture = &data->texture[EA];
		else
			texture = &data->texture[WE];
	}
	else
	{
	if (sin(math->ray_data[0]) > 0)
			texture = &data->texture[SO];
		else
			texture = &data->texture[NO];
	}
	return (texture);
}

void	ft_config_data_texture(t_data *data, t_ray *math, int *win, int i)
{
	math->dist[1] = math->dist[1] * cos(fix_ang_rad(data->d_player[2] - math->ray_data[0]));
	math->line_dimensions[0] = (size_one_block * height) / math->dist[1];
	math->line_dimensions[1] = (height / 2) - (math->line_dimensions[0] / 2);
	draw_col(data, math, (int *)win, i, ft_get_texture_by_cardinal(data, math));
}

void	ft_raycasting(t_data *data, int *win)
{
	t_ray	math;
	int	i;
	double	tmp[2];

	i = -1;
	math.ray_data[0] = fix_ang_rad(data->d_player[2] + deg_to_rad(fov / 2));
	while (++i < num_ray)
	{
		math.dist[0] = 100000;
		ft_raycasting_vertical(data, &math, tan(math.ray_data[0]));
		tmp[0] = math.ray_data[1];
		tmp[1] = math.ray_data[2];
		math.dist[1] = 100000;
		ft_raycasting_horizontal(data, &math, 1.0 / tan(math.ray_data[0]));
		math.side = 0;
		if(math.dist[0] < math.dist[1])
		{
			math.ray_data[1] = tmp[0];
			math.ray_data[2] = tmp[1];
			math.dist[1] = math.dist[0];
			math.side++;
		}
		ft_config_data_texture(data, &math, win, i);
		math.ray_data[0] = fix_ang_rad(math.ray_data[0] - deg_to_rad(fov) / num_ray);
	}
}


void	ft_draw_texture(t_ray *math, t_texture *texture, int *win, int i, int *pos)
{
	int	color;
	int	tex_x;
	int	tex_y;

	while (pos[1] < (int)(math->line_dimensions[1] + math->line_dimensions[0]) && pos[1] < height)
	{
		tex_y = (int)(((pos[1]) - math->line_dimensions[1]) / math->line_dimensions[0] * texture->img_h);
		if (math->side)
		{
			tex_x = (int)(math->ray_data[2]) % size_one_block;
		}
		else
		{
			tex_x = (int)(math->ray_data[1]) % size_one_block;
		}
		tex_x = (tex_x * texture->img_w) / size_one_block;
		color = texture->data[tex_y * texture->img_w + tex_x];
		mlx_pixel_put_img(win, i * (widht / num_ray) + pos[0], pos[1], color);
		(pos[1])++;
	}
}

void	draw_col(t_data *data, t_ray *math, int *win, int i, t_texture *texture)
{
	int	pos[2];
	int column_width = widht / num_ray;

	pos[0] = 0;
	while (pos[0] < column_width)
	{
		pos[1] = -1;
		while (++pos[1] < (int)math->line_dimensions[1])
			mlx_pixel_put_img(win, i * column_width + pos[0], pos[1], create_trgb(255, data->color_top[0], data->color_top[1], data->color_top[2]));
		ft_draw_texture(math, texture, win, i, &pos[0]);
		while (++pos[1] < height)
			mlx_pixel_put_img(win, i * column_width + pos[0], pos[1], create_trgb(255, data->color_floor[0], data->color_floor[1], data->color_floor[2]));
		pos[0]++;
	}
}
