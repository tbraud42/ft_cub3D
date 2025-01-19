/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:43:26 by tao               #+#    #+#             */
/*   Updated: 2025/01/19 22:05:23 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	mlx_pixel_put_img(int *win, int x0, int y0, int color)
{
	int	*pos;

	if (x0 > widht - 1 || y0 > height || x0 < 0 || y0 < 0)
		return ;
	pos = win + (y0 * widht + x0);
	*pos = color;
}
