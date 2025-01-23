/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:39:01 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/23 15:25:05 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	ft_mouse(t_data *data)
{
	int	x;
	int	y;
	int	widht_comp;

	widht_comp = (int)(WIDTH * 0.5);
	mlx_mouse_get_pos(data->mlx, data->mlx_win, &x, &y);
	if (x > widht_comp)
		ft_right_arrow(data);
	else if (x < widht_comp)
		ft_left_arrow(data);
	mlx_mouse_move(data->mlx, data->mlx_win, widht_comp, (int)(HEIGHT * 0.5));
}
