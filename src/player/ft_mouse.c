/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:39:01 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/18 12:42:18 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
