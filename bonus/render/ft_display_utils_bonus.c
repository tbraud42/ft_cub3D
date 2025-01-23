/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:49:48 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/23 15:23:21 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

t_texture	*ft_get_texture_by_cardinal(t_data *data, t_ray *math)
{
	t_texture	*texture;

	if (math->side)
	{
		if (cos(math->ray_data[0]) > 0)
			texture = &data->texture[WE];
		else
			texture = &data->texture[EA];
	}
	else
	{
		if (sin(math->ray_data[0]) > 0)
			texture = &data->texture[SO];
		else
			texture = &data->texture[NO];
	}
	return (texture);
}
