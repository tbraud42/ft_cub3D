/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:37:39 by tbraud            #+#    #+#             */
/*   Updated: 2024/10/15 02:07:38 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_perror(void)
{
	write(2, "Error\n", 7);
	perror(0);
	exit(EXIT_FAILURE);
}

void	ft_error(char *erno, int choice, char **map)
{
	if (choice == 1)
		ft_free(map);
	write(2, "Error\n", 7);
	if (erno)
		write(2, erno, ft_strlen(erno));
	exit(EXIT_FAILURE);
}

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

int	ft_exit_mlx(t_data *data, int choice) // a update en fonction de la struc
{
	int	i;

	i = 0;
	while (i < 8)
	{
		// if (data->img[i]) destroy des textures
		// 	mlx_destroy_image(data->mlx, data->img[i]);
		i++;
	}
	if (choice == 1)
		write(2, "Error\n", 7);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	ft_free(data->map);
	exit(0);
	return (0);
}
