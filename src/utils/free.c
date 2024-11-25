/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:19:55 by brguicho          #+#    #+#             */
/*   Updated: 2024/11/22 11:13:20 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	if (data->NO)
		free(data->NO);
	if (data->SO)
		free(data->SO);
	if (data->WE)
		free(data->WE);
	if (data->EA)
		free(data->EA);
	if (data->map)
		ft_free(data->map);
}
