/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:49:48 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/22 23:51:05 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
