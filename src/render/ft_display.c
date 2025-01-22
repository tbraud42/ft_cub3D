/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:41:22 by tao               #+#    #+#             */
/*   Updated: 2025/01/22 09:21:19 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_texture	*ft_get_texture_by_cardinal(t_data *data, t_ray *math)
{
	t_texture	*texture;

	if (math->side)
	{
		if (cos(math->ray_data[0]) > 0)
			texture = &data->texture[WE];
		else
			texture = &data->texture[EA];
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

static void	ft_draw_texture(t_data *data, t_texture *texture, int i, int *pos)
{
	int	color;
	int	tex_x;
	int	tex_y;

	while (pos[1] < (int)(data->ray.line_dimensions[1]
		+ data->ray.line_dimensions[0]) && pos[1] < HEIGHT)
	{
		tex_y = (int)(((pos[1]) - data->ray.line_dimensions[1])
				/ data->ray.line_dimensions[0] * texture->img_h);
		if (data->ray.side)
		{
			tex_x = (int)(data->ray.ray_data[2]) % SIZE_ONE_BLOCK;
		}
		else
		{
			tex_x = (int)(data->ray.ray_data[1]) % SIZE_ONE_BLOCK;
		}
		tex_x = (tex_x * texture->img_w) / SIZE_ONE_BLOCK;
		color = texture->data[tex_y * texture->img_w + tex_x];
		mlx_pixel_put_img((int *)data->info_img_raycast, i
			* (WIDTH / NUM_RAY) + pos[0], pos[1], color);
		(pos[1])++;
	}
}

static void	draw_col(t_data *data, int *win, int i, t_texture *texture)
{
	int	pos[2];
	int	column_width;

	column_width = WIDTH / NUM_RAY;
	pos[0] = 0;
	while (pos[0] < column_width)
	{
		pos[1] = -1;
		while (++pos[1] < (int)data->ray.line_dimensions[1])
			mlx_pixel_put_img(win, i * column_width + pos[0], pos[1],
				create_trgb(255, data->color_top[0], data->color_top[1],
					data->color_top[2]));
		ft_draw_texture(data, texture, i, &pos[0]);
		while (++pos[1] < HEIGHT)
			mlx_pixel_put_img(win, i * column_width + pos[0], pos[1],
				create_trgb(255, data->color_floor[0],
					data->color_floor[1], data->color_floor[2]));
		pos[0]++;
	}
}

void	ft_config_data_texture(t_data *data, t_ray *math, int *win, int i)
{
	math->dist[1] = math->dist[1]
		* cos(fix_ang_rad(data->d_player[2] - math->ray_data[0]));
	math->line_dimensions[0] = (SIZE_ONE_BLOCK * HEIGHT) / math->dist[1];
	math->line_dimensions[1] = (HEIGHT / 2) - (math->line_dimensions[0] / 2);
	draw_col(data, (int *)win, i, ft_get_texture_by_cardinal(data, math));
}

int	ft_display_window(t_data *data)
{
	int		a;
	int		b;
	int		c;

	if (data->img_raycast != NULL)
		mlx_destroy_image(data->mlx, data->img_raycast);
	data->img_raycast = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->info_img_raycast = mlx_get_data_addr(data->img_raycast, &a, &b, &c);
	ft_raycasting(data, (int *)data->info_img_raycast);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_raycast, 0, 0);
	return (0);
}
