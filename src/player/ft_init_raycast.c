/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_raycast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:41:22 by tao               #+#    #+#             */
/*   Updated: 2024/12/23 04:43:08 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void	ft_mini_map(char *win)
// {

// }

int	ft_display_window(t_data *data)
{
	int	a, b, c;

	if (data->img_raycast != NULL)
		mlx_destroy_image(data->mlx, data->img_raycast);
	data->img_raycast = mlx_new_image(data->mlx, widht, height);
	if (data->img_map != NULL)
		mlx_destroy_image(data->mlx, data->img_map);
	data->img_map = mlx_new_image(data->mlx, widht / 10 , height / 10);
	char	*info_img_raycast = mlx_get_data_addr(data->img_raycast, &a, &b, &c);
	// int	i = 0, j;
	// while(data->map[i]) {
	// 	j = 0;
	// 	while (data->map[i][j]) {
	// 		if (data->map[i][j] == '1')
	// 			mlx_put_image_to_window_bis(info_img_raycast, j * size_one_block, i * size_one_block, size_one_block, 0xFFFFFFFF);
	// 		else if (data->map[i][j] == '0' || data->map[i][j] == 'N')
	// 			mlx_put_image_to_window_bis(info_img_raycast, j * size_one_block, i * size_one_block, size_one_block, 0xFF000000);
	// 		j++;
	// 	}
	// 	i++;
	// }
	// mlx_put_image_to_window_bis(info_img_raycast, data->player[0] - 5, data->player[1] - 5, 9, create_trgb(255, 0, 0, 255));
	ft_mouse(data);
	ft_raycasting(data, info_img_raycast);
	// ft_mini_map();
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_raycast, 0, 0);
	return (0);
}

