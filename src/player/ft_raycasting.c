/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:53:07 by tbraud            #+#    #+#             */
/*   Updated: 2025/01/20 22:06:35 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	deg_to_rad(double angle) // degree to radiant
{
	return (angle * M_PI / 180.0);
}

double	fix_ang_rad(double a) // modulo 360 angle en radiant
{
	if (a > 2 * M_PI)
		a -= 2 * M_PI;
	if (a < 0)
		a += 2 * M_PI;
	return (a);
}

double	ft_dist(double ax, double ay, double bx, double by)// , double ang
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


void	ft_raycasting(t_data *data, char *win)
{
	t_ray	math;
	int	dof;
	double tan_ra;
	int	i;
	double	vx,vy; // a changer

	i = 0;
	math.ray_data[0] = fix_ang_rad(data->d_player[2] + deg_to_rad(fov / 2));

	while (i < num_ray) {
		// Raycast vertical
		dof = 0; math.dist[0] = 100000;
		tan_ra = tan(math.ray_data[0]);
		if (fabs(cos(math.ray_data[0])) > 0.001) {
			if (cos(math.ray_data[0]) > 0) {
				math.ray_data[1] = (((int)data->player[0] >> 6) << 6) + size_one_block;
				math.ray_data[2] = (data->player[0] - math.ray_data[1]) * tan_ra + data->player[1];
				math.ray_step[0] = size_one_block;
				math.ray_step[1] = -math.ray_step[0] * tan_ra;
			} else {
				math.ray_data[1] = (((int)data->player[0] >> 6) << 6) - 0.0001;
				math.ray_data[2] = (data->player[0] - math.ray_data[1]) * tan_ra + data->player[1];
				math.ray_step[0] = -size_one_block;
				math.ray_step[1] = -math.ray_step[0] * tan_ra;
			}
		} else {
			math.ray_data[1] = data->player[0];
			math.ray_data[2] = data->player[1];
			dof = 30;
		}

		while (dof < 30) {
			math.map_coords[0] = (int)(math.ray_data[1]) >> 6;
			math.map_coords[1] = (int)(math.ray_data[2]) >> 6;
			if (ft_hit_avaible(data, math.map_coords[0], math.map_coords[1])) {
				math.dist[0] = ft_dist(data->player[0], data->player[1], math.ray_data[1], math.ray_data[2]);
				dof = 30;
			} else {
				math.ray_data[1] += math.ray_step[0];
				math.ray_data[2] += math.ray_step[1];
				dof++;
			}
		}
		vx = math.ray_data[1];
		vy = math.ray_data[2];

		// Raycast horizontal
		dof = 0; math.dist[1] = 100000;
		tan_ra = 1.0 / tan_ra;
		if (fabs(sin(math.ray_data[0])) > 0.001) {
			if (sin(math.ray_data[0]) > 0) {
				math.ray_data[2] = (((int)data->player[1] >> 6) << 6) - 0.0001;
				math.ray_data[1] = (data->player[1] - math.ray_data[2]) * tan_ra + data->player[0];
				math.ray_step[1] = -size_one_block;
				math.ray_step[0] = -math.ray_step[1] * tan_ra;
			} else {
				math.ray_data[2] = (((int)data->player[1] >> 6) << 6) + size_one_block;
				math.ray_data[1] = (data->player[1] - math.ray_data[2]) * tan_ra + data->player[0];
				math.ray_step[1] = size_one_block;
				math.ray_step[0] = -math.ray_step[1] * tan_ra;
			}
		} else {
			math.ray_data[1] = data->player[0];
			math.ray_data[2] = data->player[1];
			dof = 30;
		}

		while (dof < 30) {
			math.map_coords[0] = (int)(math.ray_data[1]) >> 6;
			math.map_coords[1] = (int)(math.ray_data[2]) >> 6;
			if (ft_hit_avaible(data, math.map_coords[0], math.map_coords[1]))
			{
				math.dist[1] = ft_dist(data->player[0], data->player[1], math.ray_data[1], math.ray_data[2]);
				dof = 30;
			}
			else
			{
				math.ray_data[1] += math.ray_step[0];
				math.ray_data[2] += math.ray_step[1];
				dof++;
			}
		}

		math.side = 0;
		if(math.dist[0] < math.dist[1])
		{
			math.ray_data[1] = vx;
			math.ray_data[2] = vy;
			math.dist[1] = math.dist[0];
			math.side++;
		}

		math.dist[1] = math.dist[1] * cos(fix_ang_rad(data->d_player[2] - math.ray_data[0]));

		math.line_dimensions[0] = (size_one_block * height) / math.dist[1];
		math.line_dimensions[1] = (height / 2) - (math.line_dimensions[0] / 2);

		// draw_col_with_texture((int *)win, i, widht / num_ray, math.line_dimensions[0], math.line_dimensions[1], math.ray_data[1], math.ray_data[2], math.side,  math.ray_data[0], data);
		draw_col_with_texture(data, &math, (int *)win, i);
		i++;
		math.ray_data[0] = fix_ang_rad(math.ray_data[0] - deg_to_rad(fov) / num_ray);
	}
}


// void draw_col_with_texture(int *win, int i, int column_width, double lineH, double lineOff, double wall_hit_x, double wall_hit_y, int side, double ray_angle, t_data *data)
// {
//     t_texture *texture;
// 	int floor_color = create_trgb(255, data->color_floor[0], data->color_floor[1], data->color_floor[2]);
// 	int ceiling_color = create_trgb(255, data->color_top[0], data->color_top[1], data->color_top[2]);
// 	int y;
// 	int x;

//     if (side) {
//         if (cos(ray_angle) > 0) {
//             texture = &data->texture[EA];
//         } else {
//             texture = &data->texture[WE];
//         }
//     } else {
//         if (sin(ray_angle) > 0) {
//             texture = &data->texture[SO]; // Mur sud
//         } else {
//             texture = &data->texture[NO]; // Mur nord
//         }
//     }

//     x = 0;
//     while (x < column_width) {
//         y = 0;
//         while (y < (int)lineOff) {
//             mlx_pixel_put_img(win, i * column_width + x, y, ceiling_color);
//             y++;
//         }

//         // Dessiner la colonne texturée (mur)
//         while (y < (int)(lineOff + lineH) && y < height) {
//             // Calculer la position y dans la texture
//             // Si la colonne est plus grande que l'écran, ajuster le point de départ
//             int tex_y = (int)((y - lineOff) / lineH * texture->img_h);

//             // Calculer la position x dans la texture
//             int tex_x;
//             if (side) {
//                 tex_x = (int)(wall_hit_y) % texture->img_w;
//             } else {
//                 tex_x = (int)(wall_hit_x) % texture->img_w;
//             }

//             int color = texture->data[tex_y * texture->img_w + tex_x];
//             mlx_pixel_put_img(win, i * column_width + x, y, color);
//             y++;
//         }

//         while (y < height) {
//             mlx_pixel_put_img(win, i * column_width + x, y, floor_color);
//             y++;
//         }

//         x++;
//     }
// }

void draw_col_with_texture(t_data *data, t_ray *math, int *win, int i)
{
	t_texture *texture;
	int floor_color = create_trgb(255, data->color_floor[0], data->color_floor[1], data->color_floor[2]);
	int ceiling_color = create_trgb(255, data->color_top[0], data->color_top[1], data->color_top[2]);
	int y;
	int x;
	int tex_x;
	int tex_y;
	int column_width = widht / num_ray;

    if (math->side) {
        if (cos(math->ray_data[0]) > 0) {
            texture = &data->texture[EA];
        } else {
            texture = &data->texture[WE];
        }
    } else {
        if (sin(math->ray_data[0]) > 0) {
            texture = &data->texture[SO];
        } else {
            texture = &data->texture[NO];
        }
    }

    x = 0;
    while (x < column_width) {
        y = 0;
        while (y < (int)math->line_dimensions[1]) {
            mlx_pixel_put_img(win, i * column_width + x, y, ceiling_color);
            y++;
        }
        while (y < (int)(math->line_dimensions[1] + math->line_dimensions[0]) && y < height) {
            tex_y = (int)((y - math->line_dimensions[1]) / math->line_dimensions[0] * texture->img_h);

            // if (math->side)
            //     tex_x = (int)(math->ray_data[2]) % texture->img_w;
            // else
            //     tex_x = (int)(math->ray_data[1]) % texture->img_w;

			// a voir si c'est avec size_one_block ou la taille de l'image
			if (math->side) {
				tex_x = (int)(math->ray_data[2]) % size_one_block;
			} else {
				tex_x = (int)(math->ray_data[1]) % size_one_block;
			}
			tex_x = (tex_x * texture->img_w) / size_one_block;

    	    int color = texture->data[tex_y * texture->img_w + tex_x];
            mlx_pixel_put_img(win, i * column_width + x, y, color);
            y++;
        }
        while (y < height) {
            mlx_pixel_put_img(win, i * column_width + x, y, floor_color);
            y++;
        }
        x++;
    }
}
