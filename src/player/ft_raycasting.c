/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:53:07 by tbraud            #+#    #+#             */
/*   Updated: 2025/01/17 22:22:18 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void draw_line(void *mlx, int *win, int x0, int y0, int x1, int y1, int color)
// {
// 	int dx = abs(x1 - x0);
// 	int dy = abs(y1 - y0);
// 	int sx = (x0 < x1) ? 1 : -1; // direction de x
// 	int sy = (y0 < y1) ? 1 : -1; // direction de y
// 	int err = dx - dy; // erreur initiale

// 	(void)mlx;
// 	while (1) {
// 		mlx_pixel_put_img(win, x0, y0, color);
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

double deg_to_rad(double angle) // degree to radiant
{
	return (angle * M_PI / 180.0);
}

double fix_ang_rad(double a) // modulo 360 angle en radiant
{
	if(a > 2 * M_PI)
		 a -= 2 * M_PI;
	if(a < 0)
		a += 2 * M_PI;
	return (a);
}

double	dist(double ax, double ay, double bx, double by)// , double ang
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

int	ft_hit_avaible(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i] && i < y)
		i++;
	if (!data->map[i] || i != y)
		return (0);
	while (data->map[i][j] && j < x)
		j++;
	if (j != x)
		return (0);
	if (data->map[i][j] == '1')
		return (1);
	return (0);
}

void ft_raycasting(t_data *data, char *win)
{
	int dof, mx, my; // rapport raycasting/map
	double rx, ry, ra, xo, yo, vx, vy; // les doubles pour les points d'intersection
	double disV, disH; // distance verticale et horizontale
	double Tan;
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
			rx = data->player[0];
			ry = data->player[1];
			dof = 8;
		}

		while (dof < 8) {
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (ft_hit_avaible(data, mx, my)) {
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
			rx = data->player[0];
			ry = data->player[1];
			dof = 8;
		}

		while (dof < 8) {
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (ft_hit_avaible(data, mx, my)) {
				disH = dist(data->player[0], data->player[1], rx, ry);
				dof = 8;
			} else {
				rx += xo;
				ry += yo;
				dof++;
			}
		}

		// Comparer disH et disV pour afficher le point d'impact le plus proche
		int side = 0;
		if(disV < disH)
		{
			rx = vx;
			ry = vy;
			disH = disV;
			side++;
		}

		disH = disH * cos(fix_ang_rad(data->d_player[2] - ra));

		// Calcul de la hauteur de la colonne (distance inversement proportionnelle)
		int lineH = (size_one_block * height) / disH;
		if (lineH > height) lineH = height; // Limiter la hauteur à la taille de l'écran
		int lineOff = (height / 2) - (lineH / 2); // Centrer la colonne verticalement

		// Calculer l'offset dans la texture
		// int tex_offset = (int)(rx) % data->texture[0].img_w;
		// Afficher la colonne avec la texture

		draw_col_with_texture((int *)win, i, (widht + num_ray * 0.45) / num_ray, lineH, lineOff,
                      rx, ry, side, data);
		// draw_col_with_texture((int *)win, i, (widht + num_ray * 0.45) / num_ray, lineH, lineOff, tex_offset, data); // tmp pour texture

		// draw_col((int *)win, i, (widht + num_ray * 0.45) / num_ray, lineH, lineOff, 0xFFFFFF);

		// draw_line(data->mlx, (int *)win, (int)data->player[0], (int)data->player[1], (int)rx, (int)ry, create_trgb(255, 255, 0, 0));
		i++;
		ra = fix_ang_rad(ra - deg_to_rad(fov) / num_ray); // incrementation de ra
	}
}


void draw_col_with_texture(int *win, int i, int column_width, float lineH, float lineOff,
                           double wall_hit_x, double wall_hit_y, int is_vertical, t_data *data)
{
	t_texture tmp = data->texture[0];
	int floor_color = create_trgb(255, data->color_floor[0], data->color_floor[1], data->color_floor[2]);
	int ceiling_color = create_trgb(255, data->color_top[0], data->color_top[1], data->color_top[2]);

	int x = 0;
	while (x < column_width) {
		int y = 0;
		// plafond
		while (y < (int)lineOff) {
			mlx_pixel_put_img(win, i * column_width + x, y, ceiling_color);
			y++;
		}
		// texture
		while (y < (int)(lineOff + lineH)) {
			// Calculer la position y dans la texture (mapper la hauteur de la colonne à 64)
			int tex_y = (int)(((y - lineOff) / lineH) * tmp.img_h) % tmp.img_h;
			// Calculer la position x dans la texture
			int tex_x;
			if (is_vertical) {
				// Si le mur touché est vertical
				tex_x = (int)(wall_hit_y) % tmp.img_w;
			} else {
				// Si le mur touché est horizontal
				tex_x = (int)(wall_hit_x) % tmp.img_w;
			}
			int color = tmp.data[tex_y * tmp.img_w + tex_x];
			mlx_pixel_put_img(win, i * column_width + x, y, color);
			y++;
		}
		// sol
		while (y < height) {
			mlx_pixel_put_img(win, i * column_width + x, y, floor_color);
			y++;
		}
		x++;
	}
}
