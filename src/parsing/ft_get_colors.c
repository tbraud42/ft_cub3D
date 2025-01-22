/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:34:55 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/22 20:21:37 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_floor_color(t_data *data, char *str)
{
	char	**tmp_tab;

	tmp_tab = ft_split(str, ',');
	if (!tmp_tab)
		return (0);
	if (check_len_number(tmp_tab))
	{
		error_color(5);
		ft_free(tmp_tab);
		return (0);
	}
	if (ft_atoi(tmp_tab[0]) >= 0 && ft_atoi(tmp_tab[0]) <= 255
		&& ft_atoi(tmp_tab[1]) >= 0 && ft_atoi(tmp_tab[1]) <= 255
		&& ft_atoi(tmp_tab[2]) >= 0 && ft_atoi(tmp_tab[2]) <= 255)
	{
		data->color_floor[0] = ft_atoi(tmp_tab[0]);
		data->color_floor[1] = ft_atoi(tmp_tab[1]);
		data->color_floor[2] = ft_atoi(tmp_tab[2]);
		ft_free(tmp_tab);
		return (1);
	}
	error_color(5);
	ft_free(tmp_tab);
	return (0);
}

int	get_top_color(t_data *data, char *str)
{
	char	**tmp_tab;

	tmp_tab = ft_split(str, ',');
	if (!tmp_tab)
		return (0);
	if (check_len_number(tmp_tab))
	{
		error_color(4);
		ft_free(tmp_tab);
		return (0);
	}
	if (ft_atoi(tmp_tab[0]) >= 0 && ft_atoi(tmp_tab[0]) <= 255
		&& ft_atoi(tmp_tab[1]) >= 0 && ft_atoi(tmp_tab[1]) <= 255
		&& ft_atoi(tmp_tab[2]) >= 0 && ft_atoi(tmp_tab[2]) <= 255)
	{
		data->color_top[0] = ft_atoi(tmp_tab[0]);
		data->color_top[1] = ft_atoi(tmp_tab[1]);
		data->color_top[2] = ft_atoi(tmp_tab[2]);
		ft_free(tmp_tab);
		return (1);
	}
	error_color(4);
	ft_free(tmp_tab);
	return (0);
}

int	duplicated_color(t_data *data, int flag)
{
	if (flag == 0)
	{
		if (data->color_floor[0])
			return (0);
		if (data->color_floor[1])
			return (0);
		if (data->color_floor[2])
			return (0);
	}
	else if (flag == 1)
	{
		if (data->color_top[0])
			return (0);
		if (data->color_top[1])
			return (0);
		if (data->color_top[2])
			return (0);
	}
	return (1);
}

int	get_map_colors(t_data *data, char *str)
{
	if (!ft_strncmp(str, "F", 1))
	{
		if (!duplicated_color(data, 0))
			return (error_color(2));
		str++;
		if (!ft_isspace(*str))
			return (error_arg());
		while (ft_isspace(*str))
			str++;
		return (get_floor_color(data, str));
	}
	if (!ft_strncmp(str, "C", 1))
	{
		if (!duplicated_color(data, 1))
			return (error_color(3));
		str++;
		if (!ft_isspace(*str))
			return (error_arg());
		while (ft_isspace(*str))
			str++;
		return (get_top_color(data, str));
	}
	return (1);
}
