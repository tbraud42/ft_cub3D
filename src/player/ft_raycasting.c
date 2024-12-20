/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:53:07 by tbraud            #+#    #+#             */
/*   Updated: 2024/12/20 20:17:52 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
#define height 512

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

void ft_raycasting(t_data *data, char *win, int mapX, int mapY)
{
	int dof, mx, my; // rapport raycasting/map
	float rx, ry, ra, xo, yo, vx, vy; // les floats pour les points d'intersection
	float disV, disH; // distance verticale et horizontale
	float Tan;
	int i = 0;

	// Convertir ra en radians une seule fois
	ra = fix_ang_rad(data->d_player[2] + deg_to_rad(fov / 2));

	while (i < num_ray) {
		// Raycast vertical
		dof = 0; disV = 100000;
		Tan = tan(ra);
		if (fabs(cos(ra)) > 0.001) {  // Rayon vers la gauche ou la droite
			if (cos(ra) > 0) {  // Vers la droite
				rx = (((int)data->player[0] >> 6) << 6) + size_one_block;
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
			rx = data->player[0]; // (((int)data->player[0] >> 6) << 6) + 0.0001;
			ry = data->player[1]; // (((int)data->player[1] >> 6) << 6) + 0.0001
			dof = 8;
		}

		while (dof < 8) {
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (mx >= 0 && mx < mapX && my >= 0 && my < mapY && data->map[my][mx] == '1') {
				disV = dist(data->player[0], data->player[1], rx, ry);
				dof = 8;
			} else {
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		vx = rx;
		vy = ry;

		// Raycast horizontal
		dof = 0; disH = 100000;
		Tan = 1.0 / Tan;
		if (fabs(sin(ra)) > 0.001) {  // Rayon vers le haut ou le bas
			if (sin(ra) > 0) {  // Vers le bas
				ry = (((int)data->player[1] >> 6) << 6) - 0.0001;
				rx = (data->player[1] - ry) * Tan + data->player[0];
				yo = -size_one_block;
				xo = -yo * Tan;
			} else {  // Vers le haut
				ry = (((int)data->player[1] >> 6) << 6) + size_one_block;
				rx = (data->player[1] - ry) * Tan + data->player[0];
				yo = size_one_block;
				xo = -yo * Tan;
			}
		} else {  // Rayon aligné horizontalement
			rx = data->player[0]; // (((int)data->player[0] >> 6) << 6) + 0.0001
			ry = data->player[1]; // (((int)data->player[1] >> 6) << 6) + 0.0001
			dof = 8;
		}

		while (dof < 8) {
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (mx >= 0 && mx < mapX && my >= 0 && my < mapY && data->map[my][mx] == '1') {
				disH = dist(data->player[0], data->player[1], rx, ry);
				dof = 8;
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

		float ca = fix_ang_rad(data->d_player[2] - ra);
        disH = disH * cos(ca);

        // Calcul de la hauteur de la colonne (distance inversement proportionnelle)
        int lineH = (size_one_block * height) / disH;
        if (lineH > height) lineH = height; // Limiter la hauteur à la taille de l'écran
        int lineOff = (height / 2) - (lineH / 2); // Centrer la colonne verticalement

		draw_col((int *)win, i, widht / fov, lineH, lineOff, 0xFFFFFF);

		// int ca=fix_ang_rad(data->d_player[2] - ra); disH=disH*cos(ca);
		// int lineH = (size_one_block*512)/(disH); if(lineH>512){ lineH=512;} // size_one_block
		// int lineOff = 256 - (lineH>>1);
		// (void)data;
		// draw_col((int *)win, i, lineH, lineOff);
		// draw_line(data->mlx, (int *)win, (int)data->player[0], (int)data->player[1], (int)rx, (int)ry, create_trgb(255, 255, 0, 0));
		i++;
		ra = fix_ang_rad(ra - deg_to_rad(fov / num_ray)); // incrementation de ra
	}
}


void draw_col(int *win, int i, int column_width, float lineH, float lineOff, int color)
{
    for (int x = 0; x < column_width; x++) {
        for (int y = 0; y < (int)lineH; y++) {
            mlx_pixel_put_img(win, i * column_width + x, (int)(lineOff + y), color);
        }
    }
}


// void	draw_col(int *win, int col, int lineH, int lineOff)
// {
// 	int	i = 0;
// 	int	j;

// 	col = (int)(col * 1024) / 60;
// 	while (i < 512)
// 	{
// 		j = 0;
// 		while (j < 17)
// 		{
// 			if (i < lineH)
// 				mlx_pixel_put_img(win, col + j, i, create_trgb(0, 0, 0, 0));
// 			else if (i < lineOff)
// 				mlx_pixel_put_img(win, col + j, i, create_trgb(0, 255, 0, 0));
// 			else
// 				mlx_pixel_put_img(win, col + j, i, create_trgb(0, 0, 0, 0));
// 			j++;
// 		}
// 		i++;
// 	}



	// col = col * 17;
	// while (i < 512)
	// {
	// 	j = 0;
	// 	while (j < 17)
	// 	{
	// 		k = 0;
	// 		while (k < 4)
	// 		{
	// 			if (i < lineH)
	// 				mlx_pixel_put_img(win, col + j, i + k, create_trgb(0, 0, 0, 0));
	// 			else if (i < lineOff)
	// 				mlx_pixel_put_img(win, col + j, i + k, create_trgb(0, 255, 0, 0));
	// 			else
	// 				mlx_pixel_put_img(win, col + j, i + k, create_trgb(0, 0, 0, 0));
	// 			k++;
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
// }
