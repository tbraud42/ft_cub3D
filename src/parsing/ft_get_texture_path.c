/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_texture_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:42:04 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/22 12:32:03 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_valid_path(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len <= 4)
		return (1);
	if (str[len - 4] != '.' || str[len - 3] != 'x'
		|| str[len - 2] != 'p' || str[len - 1] != 'm')
		return (0);
	return (1);
}

int	get_no(t_data *data, char *str)
{
	int	fd;

	if (ft_strncmp(str, "NO", 2) == 0)
	{
		str += 2;
		if (ft_isspace(*str) == 0)
			return (error_texture(1));
		if (!is_valid_path(str))
			return (error_texture(2));
		while (ft_isspace(*str))
			str++;
		fd = open(str, O_RDONLY);
		if (fd < 0)
			return (error_texture(3));
		close(fd);
		if (data->texture[NO].file)
			return (error_texture(4));
		data->texture[NO].file = ft_strdup(str);
		if (!data->texture[NO].file)
			return (error_texture(5));
	}
	return (1);
}

int	get_so(t_data *data, char *str)
{
	int	fd;

	if (ft_strncmp(str, "SO", 2) == 0)
	{
		str += 2;
		if (ft_isspace(*str) == 0)
			return (error_texture(1));
		if (!is_valid_path(str))
			return (error_texture(2));
		while (ft_isspace(*str))
			str++;
		fd = open(str, O_RDONLY);
		if (fd < 0)
			return (error_texture(3));
		close(fd);
		if (data->texture[SO].file)
			return (error_texture(4));
		data->texture[SO].file = ft_strdup(str);
		if (!data->texture[SO].file)
			return (error_texture(5));
	}
	return (1);
}

int	get_ea(t_data *data, char *str)
{
	int	fd;

	if (ft_strncmp(str, "EA", 2) == 0)
	{
		str += 2;
		if (ft_isspace(*str) == 0)
			return (error_texture(1));
		if (!is_valid_path(str))
			return (error_texture(2));
		while (ft_isspace(*str))
			str++;
		fd = open(str, O_RDONLY);
		if (fd < 0)
			return (error_texture(3));
		close(fd);
		if (data->texture[EA].file)
			return (error_texture(4));
		data->texture[EA].file = ft_strdup(str);
		if (!data->texture[EA].file)
			return (error_texture(5));
	}
	return (1);
}

int	get_we(t_data *data, char *str)
{
	int	fd;

	if (ft_strncmp(str, "WE", 2) == 0)
	{
		str += 2;
		if (ft_isspace(*str) == 0)
			return (error_texture(1));
		if (!is_valid_path(str))
			return (error_texture(2));
		while (ft_isspace(*str))
			str++;
		fd = open(str, O_RDONLY);
		if (fd < 0)
			return (error_texture(3));
		close(fd);
		if (data->texture[WE].file)
			return (error_texture(4));
		data->texture[WE].file = ft_strdup(str);
		if (!data->texture[WE].file)
			return (error_texture(5));
	}
	return (1);
}
