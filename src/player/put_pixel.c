/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:43:26 by tao               #+#    #+#             */
/*   Updated: 2024/12/23 04:43:31 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
