/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:13:47 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/23 13:57:51 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_init_texture(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->texture[i].img = mlx_xpm_file_to_image(data->mlx,
				data->texture[i].file, &data->texture[i].img_w,
				&data->texture[i].img_h);
		if (data->texture[i].img == NULL)
		{
			write(2, "texture ", 9);
			ft_exit_mlx(data, 1);
		}
		data->texture[i].data = (int *)mlx_get_data_addr(data->texture[i].img,
				&data->texture[i].bpp, &data->texture[i].size_line,
				&data->texture[i].endian);
		i++;
	}
}

void	init_ray(t_ray *ray)
{
	ray->dist[0] = 0;
	ray->dist[1] = 0;
	ray->line_dimensions[0] = 0;
	ray->line_dimensions[1] = 0;
	ray->ray_data[0] = 0;
	ray->ray_data[1] = 0;
	ray->ray_data[2] = 0;
	ray->ray_step[0] = 0;
	ray->ray_step[1] = 0;
	ray->side = 0;
}

static void	init_tex(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->texture[i].addr_data = NULL;
		data->texture[i].bpp = 0;
		data->texture[i].data = NULL;
		data->texture[i].endian = 0;
		data->texture[i].file = NULL;
		data->texture[i].img = NULL;
		data->texture[i].img_h = 0;
		data->texture[i].img_w = 0;
		data->texture[i].size_line = 0;
		i++;
	}
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->texture[NO].file = NULL;
	data->texture[SO].file = NULL;
	data->texture[WE].file = NULL;
	data->texture[EA].file = NULL;
	data->map = NULL;
	data->map_height = 0;
	data->map_width = 0;
	data->color_floor[0] = 0;
	data->color_floor[1] = 0;
	data->color_floor[2] = 0;
	data->color_top[0] = 0;
	data->color_top[1] = 0;
	data->color_top[2] = 0;
	data->img_raycast = NULL;
	data->info_img_raycast = NULL;
	init_ray(&data->ray);
	init_tex(data);
}
