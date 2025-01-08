/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:37:39 by tbraud            #+#    #+#             */
/*   Updated: 2025/01/08 21:27:06 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_perror(char *msg_error)
{
	write(2, msg_error, ft_strlen(msg_error));
	write(2, "\n", 1);
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

int	ft_exit_mlx(t_data *data, int choice)
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
	ft_free_all(data);
	exit(0);
	return (0);
}
