/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 04:56:39 by tbraud            #+#    #+#             */
/*   Updated: 2024/12/11 18:16:11 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_forward(t_data *data)
{
	// if ((int)(data->d_player[0] * 5)) cree les hiy wall
	data->player[0] += data->d_player[0] * 5;
	data->player[1] += data->d_player[1] * 5;
	// printf("player = %f, %f", data->player[0], data->player[1]);
}

static void	ft_backward(t_data *data)
{
	data->player[0] -= data->d_player[0] * 5;
	data->player[1] -= data->d_player[1] * 5;
	// printf("player = %f, %f", data->player[0], data->player[1]);
}

static void	ft_left(t_data *data)
{
	data->d_player[2] -= 0.1;
	if (data->d_player[2] < 0)
		data->d_player[2] += 2 * M_PI;
	data->d_player[0] = cosf(data->d_player[2]) * 5;
	data->d_player[1] = sinf(data->d_player[2]) * 5;
	// data->d_player[2] -= 5;
	// data->d_player[2] = fix_ang(data->d_player[2]);
	// data->d_player[0] = cos(deg_to_rad(data->d_player[2]));
	// data->d_player[1] = -sin(deg_to_rad(data->d_player[2]));
}

static void	ft_right(t_data *data)
{
	data->d_player[2] += 0.1;
	if (data->d_player[2] > 2 * M_PI)
		data->d_player[2] -= 2 * M_PI;
	data->d_player[0] = cosf(data->d_player[2]) * 5;
	data->d_player[1] = sinf(data->d_player[2]) * 5;
	// data->d_player[2] += 5;
	// data->d_player[2] = fix_ang(data->d_player[2]);
	// data->d_player[0] = cos(deg_to_rad(data->d_player[2]));
	// data->d_player[1] = -sin(deg_to_rad(data->d_player[2]));
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

	data->tmp_a.img = mlx_xpm_file_to_image(data->mlx, "./white.xpm", &data->tmp_a.img_width, &data->tmp_a.img_height);
	if (data->tmp_a.img == NULL) {
		write(2, "error mlx\n", 11);
		perror(NULL);
		return (0);
	}
	data->tmp_b.img = mlx_xpm_file_to_image(data->mlx, "./player.xpm", &data->tmp_b.img_width, &data->tmp_b.img_height);
	if (data->tmp_b.img == NULL) {
		write(2, "error player\n", 14);
		perror(NULL);
		return (0);
	}
	data->tmp_c.img = mlx_xpm_file_to_image(data->mlx, "./black.xpm", &data->tmp_c.img_width, &data->tmp_c.img_height);
	if (data->tmp_c.img == NULL) {
		write(2, "error black\n", 13);
		perror(NULL);
		return (0);
	}
	while(data->map[i]) {
		j = 0;
		while (data->map[i][j]) {
			if (data->map[i][j] == 'N') {
				data->player[1] = i * data->tmp_a.img_width;
				data->player[0] = j * data->tmp_a.img_height;
				data->d_player[2] = 1.5708;
				data->d_player[0] = cosf(data->d_player[2]) * 5;
				data->d_player[1] = sinf(data->d_player[2]) * 5;
				// data->d_player[0] = cos(deg_to_rad(data->d_player[2]));
				// data->d_player[1] = -sin(deg_to_rad(data->d_player[2]));
			}
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

int a, b;

void mlx_pixel_put_img(int *win, int x0, int y0, int color)
{
	if (x0 > 64 * 7 || y0 > 64 * 5 || x0 < 0 || y0 < 0)
		return ;
	int *pos = win + (y0 * 64 * 7 + x0); // tu changera le 64 * 7
	*pos = color;
	// *pos = (1 >> 24 | 1 >> 16 | 1 >> 8 | 100);
}

void	mlx_put_image_to_window_bis(char *infoMQ, int j, int i, int height, int widht, int color)
{
	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < widht; y++)
		{
			mlx_pixel_put_img((int *)infoMQ, j + x, y + i, color);
		}
	}
}

int	ft_display_window(t_data *data)
{
	void	*mQ;
	int	i = 0, j;
	int	c;

	mQ = mlx_new_image(data->mlx, 64 * 7, 64 * 5);
	char	*infoMQ = mlx_get_data_addr(mQ, &a, &b, &c);
	while(data->map[i]) {
		j = 0;
		while (data->map[i][j]) {
			if (data->map[i][j] == '1')
				mlx_put_image_to_window_bis(infoMQ, j * data->tmp_a.img_height, i * data->tmp_a.img_width, data->tmp_a.img_height, data->tmp_a.img_width, 0xFFFFFFFF);
			else if (data->map[i][j] == '0' || data->map[i][j] == 'N')
				mlx_put_image_to_window_bis(infoMQ, j * data->tmp_c.img_height, i * data->tmp_c.img_width, data->tmp_b.img_height, data->tmp_b.img_width, 0xFF000000);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window_bis(infoMQ, data->player[0] - 5, data->player[1] - 5, 9, 9, create_trgb(255, 0, 0, 255));
	ft_mouse(data);
	ft_raycasting(data, infoMQ, data->size_map[0], data->size_map[1]);
	mlx_put_image_to_window(data->mlx, data->mlx_win, mQ, 0, 0);
	return (0);
}

int	ft_mouse(t_data *data)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(data->mlx, data->mlx_win, &x, &y);
	if (x > 512) // doit etre variable sur la taille de l'ecran
		ft_right(data);
	else if (x < 512) // doit etre variable sur la taille de l'ecran
		ft_left(data);
	mlx_mouse_move(data->mlx, data->mlx_win, 512, 256);
	return (0);
}
