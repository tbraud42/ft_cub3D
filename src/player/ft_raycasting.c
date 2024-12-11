/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:53:07 by tbraud            #+#    #+#             */
/*   Updated: 2024/12/11 18:16:45 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color)
// {
// 	int dx = abs(x1 - x0);
// 	int dy = abs(y1 - y0);
// 	int sx = (x0 < x1) ? 1 : -1; // direction de x
// 	int sy = (y0 < y1) ? 1 : -1; // direction de y
// 	int err = dx - dy; // erreur initiale

// 	while (1) {
// 		mlx_pixel_put(mlx, win, x0, y0, color);
// 		if (x0 == x1 && y0 == y1) // cas d'arret
// 			break;
// 		int e2 = 2 * err; // Mise à jour de l'erreur et des coordonnées x et y
// 		if (e2 > -dy)
// 		{
// 			err -= dy;
// 			x0 += sx;
// 		}
// 		if (e2 < dx)
// 		{
// 			err += dx;
// 			y0 += sy;
// 		}
// 	}
// }

void draw_line(void *mlx, int *win, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1; // direction de x
	int sy = (y0 < y1) ? 1 : -1; // direction de y
	int err = dx - dy; // erreur initiale

	(void)mlx;
	while (1) {
		mlx_pixel_put_img(win, x0, y0, color);
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

float	dist(float ax, float ay, float bx, float by)// , float ang
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

// void ft_raycasting(t_data *data, int mapX, int mapY) {
// 	int dof, mx, my; // raport raycasting/map
// 	float rx, ry, ra, xo, yo, vx, vy; // les float pour les point
// 	float disV = dist_max, disH = dist_max; // distance vertival et horizontal
// 	float Tan;
// 	int	i = 0;

// 	// Convertir ra en radians une seule fois
// 	// ra = data->d_player[2];
// 	ra = fix_ang_rad(data->d_player[2] - 0.523599);
// 	// printf("%f\n", ra)

// 	while (i < 60)
// 	{
// 		// vertical line
// 		dof = 0;
// 		Tan = -tan(ra);
// 		if (ra > P2 && ra < P3)  // Vers la droite
// 		{
// 			rx = (((int)data->player[0] >> 6) << 6) - 0.0001;
// 			ry = (data->player[0] - rx) * Tan + data->player[1];
// 			xo = -size_one_block;
// 			yo = -xo * Tan;
// 		}
// 		if (ra < P2 || ra > P3)  // Vers la gauche
// 		{
// 			rx = (((int)data->player[0] >> 6) << 6) + size_one_block;
// 			ry = (data->player[0] - rx) * Tan + data->player[1];
// 			xo = size_one_block;
// 			yo = -xo * Tan;
// 		}
// 		else if (ra == 0 || ra == PI)  // Regard droit ou gauche
// 		{
// 			rx = data->player[0];
// 			ry = data->player[1];
// 			dof = 8;
// 		}
// 		while (dof < 8) {
// 			mx = (int)(rx) >> 6;
// 			my = (int)(ry) >> 6;
// 			if (mx >= 0 && mx < mapX && my >= 0 && my < mapY && data->map[my][mx] == '1')
// 			{
// 				disV = dist(data->player[0], data->player[1], rx, ry);
// 				// disV = cosf(ra) * (rx - data->player[0]) - sinf(ra) * (ry - data->player[1]);  // Calcul de la distance
// 				vx = rx;
// 				vy = ry;
// 				break;
// 			}
// 			else
// 			{
// 				rx += xo;
// 				ry += yo;
// 				dof++;
// 				if (dof >= dist_max) break;
// 			}
// 		}

// 		// horizontal
// 		dof = 0;
// 		Tan = -1.0 / tan(ra);
// 		if (ra > PI)  // Vers le haut
// 		{
// 			ry = (((int)data->player[1] >> 6) << 6) - 0.0001;
// 			rx = (data->player[1] - ry) * Tan + data->player[0];
// 			yo = -size_one_block;
// 			xo = -yo * Tan;
// 		}
// 		if (ra < PI)  // Vers le bas
// 		{
// 			ry = (((int)data->player[1] >> 6) << 6) + size_one_block;
// 			rx = (data->player[1] - ry) * Tan + data->player[0];
// 			yo = size_one_block;
// 			xo = -yo * Tan;
// 		}
// 		else if (ra == 0 || ra == PI)  // Droit ou gauche
// 		{
// 			rx = data->player[0];
// 			ry = data->player[1];
// 			dof = 8;
// 		}
// 		while (dof < 8) {
// 			mx = (int)(rx) >> 6;
// 			my = (int)(ry) >> 6;
// 			if (mx >= 0 && mx < mapX && my >= 0 && my < mapY && data->map[my][mx] == '1')
// 			{
// 				disH = dist(data->player[0], data->player[1], rx, ry);
// 				// disH = cosf(ra) * (rx - data->player[0]) - sinf(ra) * (ry - data->player[1]);  // Calcul de la distance
// 				break;
// 			}
// 			else
// 			{
// 				rx += xo;
// 				ry += yo;
// 				dof++;
// 				if (dof >= dist_max) break;
// 			}
// 		}

// 		// Comparer disH et disV pour afficher le point d'impact le plus proche
// 		if(disV<disH)
// 		{
// 			rx=vx;
// 			ry=vy;
// 			disH=disV;
// 		}
// 		// int ca = \FixAng(pa-ra);
// 		// disH = disH*cos(degToRad(ca));
// 		// int lineH = (64*200)/(disH);
// 		// if(lineH>512) // ??
// 		// 	lineH=512;
// 		// int lineOff = 160 - (lineH>>1);
// 		// draw_col(data, i, lineH, lineOff);
// 		draw_line(data->mlx, data->mlx_win, (int)data->player[0], (int)data->player[1], (int)rx, (int)ry, 0xFF0000);
// 		i++;
// 		ra = fix_ang_rad(ra + 0.0174533); // incrementation de ra
// 		// ra = fix_ang_rad(ra - (60 * M_PI / 180) / 60.0);
// 	}
// }

void ft_raycasting(t_data *data, char *maQueue, int mapX, int mapY)
{
	int dof, mx, my; // rapport raycasting/map
	float rx, ry, ra, xo, yo, vx, vy; // les floats pour les points d'intersection
	float disV = dist_max, disH = dist_max; // distance verticale et horizontale
	float Tan;
	int i = 0;

	// Convertir ra en radians une seule fois
	ra = fix_ang_rad(data->d_player[2] - 0.523599);

	while (i < 60) {
		// Raycast vertical
		dof = 0;
		Tan = -tan(ra);
		if (fabs(cos(ra)) > 0.0001) {  // Rayon vers la gauche ou la droite
			if (cos(ra) > 0) {  // Vers la droite
				rx = (((int)data->player[0] >> 6) << 6) + 0.0001;
				ry = (data->player[0] - rx) * Tan + data->player[1];
				xo = size_one_block;
				yo = -xo * Tan;
			} else {  // Vers la gauche
				rx = (((int)data->player[0] >> 6) << 6) - 0.0001;
				ry = (data->player[0] - rx) * Tan + data->player[1];
				xo = -size_one_block;
				yo = -xo * Tan;
			}
		} else {  // Rayon aligné verticalement
			rx = (((int)data->player[0] >> 6) << 6) + 0.0001;
			ry = (((int)data->player[1] >> 6) << 6) + 0.0001;
			dof = 8;
		}

		while (dof < 8) {
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (mx >= 0 && mx < mapX && my >= 0 && my < mapY && data->map[my][mx] == '1') {
				disV = dist(data->player[0], data->player[1], rx, ry);
				vx = rx;
				vy = ry;
				break;
			} else {
				rx += xo;
				ry += yo;
				dof++;
			}
		}

		// Raycast horizontal
		dof = 0;
		Tan = -1.0 / tan(ra);
		if (fabs(sin(ra)) > 0.0001) {  // Rayon vers le haut ou le bas
			if (sin(ra) > 0) {  // Vers le bas
				ry = (((int)data->player[1] >> 6) << 6) + 0.0001;
				rx = (data->player[1] - ry) * Tan + data->player[0];
				yo = size_one_block;
				xo = -yo * Tan;
			} else {  // Vers le haut
				ry = (((int)data->player[1] >> 6) << 6) - 0.0001;
				rx = (data->player[1] - ry) * Tan + data->player[0];
				yo = -size_one_block;
				xo = -yo * Tan;
			}
		} else {  // Rayon aligné horizontalement
			rx = (((int)data->player[0] >> 6) << 6) + 0.0001;
			ry = (((int)data->player[1] >> 6) << 6) + 0.0001;
			dof = 8;
		}

		while (dof < 8) {
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (mx >= 0 && mx < mapX && my >= 0 && my < mapY && data->map[my][mx] == '1') {
				disH = dist(data->player[0], data->player[1], rx, ry);
				break;
			} else {
				rx += xo;
				ry += yo;
				dof++;
			}
		}

		// Comparer disH et disV pour afficher le point d'impact le plus proche
		if(disV < disH)
		{
			rx = vx;
			ry = vy;
			disH = disV;
		}
		// int ca=fix_ang_rad(data->d_player[2] - ra); disH=disH*cos(ca);
		// int lineH = (size_one_block*320)/(disH); if(lineH>320){ lineH=320;}
		// int lineOff = 160 - (lineH>>1);
		// draw_col(data, i, lineH, lineOff);
		draw_line(data->mlx, (int *)maQueue, (int)data->player[0], (int)data->player[1], (int)rx, (int)ry, create_trgb(255, 255, 0, 0));
		i++;
		ra = fix_ang_rad(ra + 0.0174533); // incrementation de ra
	}
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
