/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:13:47 by brguicho          #+#    #+#             */
/*   Updated: 2024/12/23 03:34:14 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_img_clean(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

void init_data(t_data *data)
{
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->NO = NULL;
	data->SO = NULL;
	data->WE = NULL;
	data->EA = NULL;
	data->map = NULL;
	data->color_floor[0] = 0;
	data->color_floor[1] = 0;
	data->color_floor[2] = 0;
	data->color_top[0] = 0;
	data->color_top[1] = 0;
	data->color_top[2] = 0;
	data->img_raycast = NULL;
	data->img_map = NULL;
}
