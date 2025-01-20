/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:13:47 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/20 22:25:07 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_init_texture(t_data *data)
{
	int	i;
	static int time;

	if (time)
		return ;
	i = 0;
	while (i < 4)
	{
		data->texture[i].img = mlx_xpm_file_to_image(data->mlx, data->texture[i].file, &data->texture[i].img_w, &data->texture[i].img_h);
		if (data->texture[i].img == NULL)
		{
			printf("error texture");
			exit(1);
		}
		data->texture[i].data = (int *)mlx_get_data_addr(data->texture[i].img, &data->texture[i].bpp, &data->texture[i].size_line, &data->texture[i].endian);
		i++;
	}
	time++;
}

void init_data(t_data *data)
{
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->texture[NO].file = NULL;
	data->texture[SO].file = NULL;
	data->texture[WE].file = NULL;
	data->texture[EA].file = NULL;
	data->map = NULL;
	data->color_floor[0] = 0;
	data->color_floor[1] = 0;
	data->color_floor[2] = 0;
	data->color_top[0] = 0;
	data->color_top[1] = 0;
	data->color_top[2] = 0;
	data->img_raycast = NULL;
}
