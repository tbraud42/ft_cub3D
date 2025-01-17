/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:41:22 by tao               #+#    #+#             */
/*   Updated: 2025/01/17 05:18:37 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_display_window(t_data *data)
{
	int	a, b, c;

	ft_init_texture(data);
	if (data->img_raycast != NULL)
		mlx_destroy_image(data->mlx, data->img_raycast);
	data->img_raycast = mlx_new_image(data->mlx, widht, height);
	char	*info_img_raycast = mlx_get_data_addr(data->img_raycast, &a, &b, &c);
	ft_mouse(data);
	ft_raycasting(data, info_img_raycast);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_raycast, 0, 0);
	return (0);
}

