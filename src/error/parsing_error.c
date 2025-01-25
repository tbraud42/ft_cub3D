/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:01:35 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/25 14:07:31 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	error_color(int flag)
{
	ft_putstr_fd("Error\n", 2);
	if (flag == 2)
		ft_putstr_fd("duplicated color floor in file \n", 2);
	if (flag == 3)
		ft_putstr_fd("duplicated color top in file \n", 2);
	if (flag == 4)
		ft_putstr_fd("wrong color value top in file \n", 2);
	if (flag == 5)
		ft_putstr_fd("wrong color value floor in file \n", 2);
	return (0);
}

int	error_texture(int flag)
{
	ft_putstr_fd("Error\n", 2);
	if (flag == 1)
		ft_putstr_fd("missing space after key\n", 2);
	if (flag == 2)
		ft_putstr_fd("not a valid path\n", 2);
	if (flag == 3)
		ft_putstr_fd("open fail\n", 2);
	if (flag == 4)
		ft_putstr_fd("duplicated value of texture \n", 2);
	if (flag == 5)
		ft_putstr_fd("fail on strdup or value is NULL\n", 2);
	return (0);
}

int	error_arg(void)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("wrong argument to parse in file \n", 2);
	return (0);
}

int	error_map(void)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Map is invalid\n", 2);
	return (0);
}

int	error_missing_key(void)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Missing key in File\n", 2);
	return (0);
}
