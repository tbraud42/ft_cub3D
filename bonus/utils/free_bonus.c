/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:19:55 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/23 15:23:21 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	ft_free(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	ft_free_all(t_data *data)
{
	if (data->texture[NO].file)
		free(data->texture[NO].file);
	if (data->texture[SO].file)
		free(data->texture[SO].file);
	if (data->texture[WE].file)
		free(data->texture[WE].file);
	if (data->texture[EA].file)
		free(data->texture[EA].file);
	if (data->map)
		ft_free(data->map);
}
