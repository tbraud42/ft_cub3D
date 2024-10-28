/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:34:55 by brguicho          #+#    #+#             */
/*   Updated: 2024/10/26 17:57:59 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int get_map_colors(t_data *data, char *str)
{
	if (!ft_strncmp(str, "F", 1))
	{
		if (!duplicated_color(data, 0))
			return (err_color(2));
		str++;
		if (!ft_isspace(*str))
			return (err_arg());
		while (ft_isspace(*str))
			str++;
		return (get_floor_color(data, str, -1));
	}
	if (!ft_strncmp(str, "C", 1))
	{
		if (!duplicated_color(data, 1))
			return (err_color(3));
		str++;
		if (!ft_isspace(*str))
			return (err_arg());
		while (ft_isspace(*str))
			str++;
		return (get_ceiling_color(data, str, -1));
	}
	return (1);
}
