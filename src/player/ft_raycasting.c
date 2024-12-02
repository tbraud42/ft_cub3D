/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:53:07 by tbraud            #+#    #+#             */
/*   Updated: 2024/12/02 17:15:46 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1; // direction de x
	int sy = (y0 < y1) ? 1 : -1; // direction de y
	int err = dx - dy; // erreur initiale

	while (1) {
		mlx_pixel_put(mlx, win, x0, y0, color);
		if (x0 == x1 && y0 == y1) // cas d'arret
			break;
		int e2 = 2 * err; // Mise à jour de l'erreur et des coordonnées x et y
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

#define size_one_block 64 // variable selon les texture ?
#define dist_max 100000 // hard limit

float deg_to_rad(float angle) // degree to radiant
{
	return (angle * M_PI / 180.0);
}

int fix_ang_deg(int a) // modulo 360 angle en degree
{
	if(a > 359)
		 a -= 360;
	if(a < 0)
		a += 360;
	return (a);
}


float fix_ang_rad(float a) // modulo 360 angle en radiant
{
	if(a > 2 * M_PI)
		 a -= 2 * M_PI;
	if(a < 0)
		a += 2 * M_PI;
	return (a);
}

void ft_raycasting(t_data *data, int mapX, int mapY) {
	int dof, mx, my; // raport raycasting/map
	float rx, ry, ra, xo, yo, vx, vy; // les float pour les point
	float px = data->player[0];
	float py = data->player[1];
	float disV = dist_max, disH = dist_max; // distance vertival et horizontal
	float Tan;
	int	i = 0;

	// Convertir ra en radians une seule fois
	// ra = data->d_player[2];
	ra = fix_ang_rad(data->d_player[2] - 0.523599);
	// printf("%f\n", ra)

	// raycast verticale
	while (i < 60)
	{
		dof = 0;
		Tan = tan(ra);
		if (cos(ra) > 0.001)  // Vers la droite
		{
			rx = (((int)px >> 6) << 6) + size_one_block;
			ry = (px - rx) * Tan + py;
			xo = size_one_block;
			yo = -xo * Tan;
		}
		else if (cos(ra) < -0.001)  // Vers la gauche
		{
			rx = (((int)px >> 6) << 6) - 0.0001;
			ry = (px - rx) * Tan + py;
			xo = -size_one_block;
			yo = -xo * Tan;
		}
		else  // Regard droit ou gauche
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8) {
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (mx >= 0 && mx < mapX && my >= 0 && my < mapY && data->map[my][mx] == '1')
			{
				disV = cosf(ra) * (rx - px) - sinf(ra) * (ry - py);  // Calcul de la distance
				vx = rx;
				vy = ry;
				break;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof++;
				if (dof >= dist_max) break;
			}
		}

		// raycast horizontal
		dof = 0;
		Tan = 1.0 / Tan;
		if (sin(ra) > 0.001)  // Vers le haut
		{
			ry = (((int)py >> 6) << 6) - 0.0001;
			rx = (py - ry) * Tan + px;
			yo = -size_one_block;
			xo = -yo * Tan;
		}
		else if (sin(ra) < -0.001)  // Vers le bas
		{
			ry = (((int)py >> 6) << 6) + size_one_block;
			rx = (py - ry) * Tan + px;
			yo = size_one_block;
			xo = -yo * Tan;
		}
		else  // Droit ou gauche
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8) {
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (mx >= 0 && mx < mapX && my >= 0 && my < mapY && data->map[my][mx] == '1')
			{
				disH = cosf(ra) * (rx - px) - sinf(ra) * (ry - py);  // Calcul de la distance
				break;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof++;
				if (dof >= dist_max) break;
			}
		}

		// Comparer disH et disV pour afficher le point d'impact le plus proche
		if(disV<disH)
		{
			rx=vx;
			ry=vy;
			disH=disV;
		}
		// int ca = \FixAng(pa-ra);
		// disH = disH*cos(degToRad(ca));
		int lineH = (64*320)/(disH);
		if(lineH>512) // ??
			lineH=512;
		int lineOff = 160 - (lineH>>1);
		draw_col(data, i, lineH, lineOff);
		// draw_line(data->mlx, data->mlx_win, (int)px, (int)py, (int)rx, (int)ry, 0xFF0000);
		i++;
		ra = fix_ang_rad(ra + 0.0174533); // incrementation de ra
		// ra = fix_ang_rad(ra - (60 * M_PI / 180) / 60.0);
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// void	draw_col(t_data *data, int col, int lineH, int lineOff)
// {
// 	int	i = 0;

// 	while (i < 256)
// 	{
// 		if (i < lineH)
// 			mlx_pixel_put(data->mlx, data->mlx_win, col, i, create_trgb(0, 0, 0, 0));
// 		else if (i < lineOff)
// 			mlx_pixel_put(data->mlx, data->mlx_win, col, i, create_trgb(0, 255, 0, 0));
// 		else
// 			mlx_pixel_put(data->mlx, data->mlx_win, col, i, create_trgb(0, 0, 0, 0));
// 		i++;
// 	}
// }

void	draw_col(t_data *data, int col, int lineH, int lineOff)
{
	int	i = 0;
	int	j, k;

	col = col * 17;
	while (i < 256)
	{
		j = 0;
		while (j < 17)
		{
			k = 0;
			while (k < 4)
			{
				if (i < lineH)
					mlx_pixel_put(data->mlx, data->mlx_win, col + j, (i * 2) + k, create_trgb(0, 0, 0, 0));
				else if (i < lineOff)
					mlx_pixel_put(data->mlx, data->mlx_win, col + j, (i * 2) + k, create_trgb(0, 255, 0, 0));
				else
					mlx_pixel_put(data->mlx, data->mlx_win, col + j, (i * 2) + k, create_trgb(0, 0, 0, 0));
				k++;
			}
			j++;
		}
		i++;
	}
}
