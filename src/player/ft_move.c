/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 04:56:39 by tbraud            #+#    #+#             */
/*   Updated: 2024/12/23 01:57:32 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_forward(t_data *data)
{
	if (data->map[(int)((data->player[1] + (data->d_player[1] * 5))) / 64][(int)((data->player[0] + (data->d_player[0] * 5))) / 64] == '1')
		return ;
	data->player[0] += data->d_player[0] * 5;
	data->player[1] += data->d_player[1] * 5;
}

static void	ft_backward(t_data *data)
{
	if (data->map[(int)((data->player[1] - (data->d_player[1] * 5))) / 64][(int)((data->player[0] - (data->d_player[0] * 5))) / 64] == '1')
		return ;
	data->player[0] -= data->d_player[0] * 5;
	data->player[1] -= data->d_player[1] * 5;
}

static void	ft_left(t_data *data)
{
	data->d_player[2] = fix_ang_rad(data->d_player[2] + 0.0872665); // 5 degree augmentation ?
	data->d_player[0] = cos(data->d_player[2]) * 5;
	data->d_player[1] = -sin(data->d_player[2]) * 5;
}

static void	ft_right(t_data *data)
{
	data->d_player[2] = fix_ang_rad(data->d_player[2] - 0.0872665); // 5 degree
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


int	ft_draw_map(t_data *data)
{
	int	i = 0;
	int j;
	int	biggest_j = 0;

	data->player[0] *= size_one_block;
	data->player[1] *= size_one_block;
	while(data->map[i]) {
		j = 0;
		while (data->map[i][j]) {
			j++;
		}
		if (j > biggest_j)
			biggest_j = j;
		i++;
	}
	data->size_map[0] = biggest_j;
	data->size_map[1] = i;
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void mlx_pixel_put_img(int *win, int x0, int y0, int color)
{
	if (x0 > widht || y0 > height || x0 < 0 || y0 < 0)
		return ;
	int *pos = win + (y0 * widht + x0);
	*pos = color;
}

void	mlx_put_image_to_window_bis(char *infoMQ, int j, int i, int block, int color)
{
	for (int x = 0; x < block; x++)
	{
		for (int y = 0; y < block; y++)
		{
			mlx_pixel_put_img((int *)infoMQ, j + x, y + i, color);
		}
	}
}


int	ft_display_window(t_data *data)
{
	int	a, b, c;

	if (data->img_r != NULL)
		mlx_destroy_image(data->mlx, data->img_r);
	data->img_r = mlx_new_image(data->mlx, widht, height);
	if (data->img_map != NULL)
		mlx_destroy_image(data->mlx, data->img_map);
	data->img_map = mlx_new_image(data->mlx, widht / 10 , height / 10);
	char	*infoMQ = mlx_get_data_addr(data->img_r, &a, &b, &c);
	// int size_one_block = 64;
	// int	i = 0, j;
	// while(data->map[i]) {
	// 	j = 0;
	// 	while (data->map[i][j]) {
	// 		if (data->map[i][j] == '1')
	// 			mlx_put_image_to_window_bis(infoMQ, j * size_one_block, i * size_one_block, size_one_block, 0xFFFFFFFF);
	// 		else if (data->map[i][j] == '0' || data->map[i][j] == 'N')
	// 			mlx_put_image_to_window_bis(infoMQ, j * size_one_block, i * size_one_block, size_one_block, 0xFF000000);
	// 		j++;
	// 	}
	// 	i++;
	// }
	// mlx_put_image_to_window_bis(infoMQ, data->player[0] - 5, data->player[1] - 5, 9, create_trgb(255, 0, 0, 255));
	ft_mouse(data);
	ft_raycasting(data, infoMQ, data->size_map[0], data->size_map[1]);
	// ft_mini_map();
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_r, 0, 0);
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
