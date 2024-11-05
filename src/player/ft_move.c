/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 04:56:39 by tbraud            #+#    #+#             */
/*   Updated: 2024/11/05 10:16:05 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_forward(t_data *data)
{
	// mlx_pixel_put(data->mlx, data->mlx_win, data->player[0], data->player[1] + 1, 0x00000000);
	// mlx_pixel_put(data->mlx, data->mlx_win, data->player[0] + 1, data->player[1] + 1, 0x00000000);

	data->player[0] += data->d_player[0];
	data->player[1] += data->d_player[1];
	// mlx_pixel_put(data->mlx, data->mlx_win, data->player[0], data->player[1], 0x000000FF);
	// mlx_pixel_put(data->mlx, data->mlx_win, data->player[0] + 1, data->player[1], 0x000000FF);
}

static void	ft_backward(t_data *data)
{
	// mlx_pixel_put(data->mlx, data->mlx_win, data->player[0], data->player[1], 0x00000000);
	// mlx_pixel_put(data->mlx, data->mlx_win, data->player[0] + 1, data->player[1], 0x00000000);

	data->player[0] -= data->d_player[0];
	data->player[1] -= data->d_player[1];
	// mlx_pixel_put(data->mlx, data->mlx_win, data->player[0], data->player[1] + 1, 0x000000FF);
	// mlx_pixel_put(data->mlx, data->mlx_win, data->player[0] + 1, data->player[1] + 1, 0x000000FF);
}

static void	ft_left(t_data *data)
{
	data->d_player[2] -= 0.1;
	if (data->d_player[2] < 0)
		data->d_player[2] += 2 * PI;
	data->d_player[0] = cosf(data->d_player[2]) * 10;
	data->d_player[1] = sinf(data->d_player[2]) * 10;
}

static void	ft_right(t_data *data)
{
	data->d_player[2] += 0.1;
	if (data->d_player[2] > 2 * PI)
		data->d_player[2] -= 2 *PI;
	data->d_player[0] = cosf(data->d_player[2]) * 10;
	data->d_player[1] = sinf(data->d_player[2]) * 10;

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
	while(data->map[i]) {
		j = 0;
		while (data->map[i][j]) {
			if (data->map[i][j] == 'N') {
				data->player[1] = i * data->tmp_b.img_width;
				data->player[0] = j * data->tmp_b.img_height;
				data->d_player[2] = PI / 2;
				data->d_player[0] = cosf(data->d_player[2]) * 10;
				data->d_player[1] = sinf(data->d_player[2]) * 10;
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


int	ft_display_window(t_data *data)
{
	int	i = 0, j;

	mlx_clear_window(data->mlx, data->mlx_win);
	while(data->map[i]) {
		j = 0;
		while (data->map[i][j]) {
			if (data->map[i][j] == '1')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->tmp_a.img, j * data->tmp_a.img_height, i * data->tmp_a.img_width);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->tmp_b.img, data->player[0], data->player[1]);
	// ft_raycasting(data, data->size_map[0], data->size_map[1]);
	return (0);
}

// float	dist(float ax, float ay, float bx, float by)// , float ang
// {
// 	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
// }

// d_player 1 = pdx 2 = pdy 3 = pa
// player 0 = px 1 = py

void	ft_raycasting(t_data *data, int mapX, int mapY)
{
	int		r, mx, my, mp, dof;
	float	rx, ry, ra, xo, yo;
	float	aTan;
	float	nTan;
	float	px, py;
	// float	disH = 1000000, hx = px, hy = py;// pour la suite
	// float	disV = 1000000, vx = px, vy = py;// pour la suite

	ra = data->d_player[2];
	px = data->player[0];
	py = data->player[1];
	r = 0;
	while (r < 1)
	{
		// Horizontale lines
		dof = 0;
		aTan = -1/tan(ra);
		if (ra > PI) // up
		{
			ry = (((int)py>>6)<<6) - 0.0001;
			rx = (py - ry) * aTan + px;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI) // down
		{
			ry = (((int)py>>6)<<6) + 64;
			rx = (py - ry) * aTan + px;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && data->map[mx][my * mapX] == 1) // hit wall
			{
				dof = 8;
			}
			else // next block
			{
				rx += xo;
				ry +=yo;
				dof += 1;
			}
		}
		// Verticale line
		dof = 0;
		nTan = -tan(ra);
		if (ra > P2 && ra < P3) // left
		{
			rx = (((int)px>>6)<<6) - 0.0001;
			ry = (px - rx) * nTan + py;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra > P3) // right
		{
			rx = (((int)px>>6)<<6) + 64;
			ry = (px - rx) * nTan + py;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && data->map[mx][my * mapX] == 1) // hit wall
			{
				dof = 8;
			}
			else // next block
			{
				rx += xo;
				ry +=yo;
				dof += 1;
			}
		}
		r++;
	}
	// draw_line();
}

// void	draw_line(t_data *data)
// {

// }
