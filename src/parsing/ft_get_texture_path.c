/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_texture_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:42:04 by brguicho          #+#    #+#             */
/*   Updated: 2024/10/30 10:09:12 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_valid_path(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len <= 4)
		return (1);
	if (str[len - 4] != '.' || str[len - 3] != 'x' || str[len - 2] != 'p' || str[len
		- 1] != 'm')
		return (0);
	return (1);
}

int	get_no(t_data *data, char *str)
{
	int fd;
	
	if (ft_strncmp(str, "NO", 2) == 0)
	{
		str += 2;
		if (ft_isspace(*str) == 0)
			return (0); // return error msg + free si besoin
		if	(!is_valid_path(str))
			return (0); // return error msg + free si besoin
		while (ft_isspace(*str))
			str++;
		fd = open(str, O_RDONLY);
		if (fd < 0)
			return (0); // echec ouverture path
		if (data->NO)
			return (0); // info duplique 
		data->NO = ft_strdup(str);
		if (!data->NO)
			return (0); //return error msg + free si besoin
	}
	return (1);
}

int	get_so(t_data *data, char *str)
{
	int fd;
	
	if (ft_strncmp(str, "SO", 2) == 0)
	{
		str += 2;
		if (ft_isspace(*str) == 0)
			return (0); // return error msg + free si besoin
		if	(!is_valid_path(str))
			return (0); // return error msg + free si besoin
		while (ft_isspace(*str))
			str++;
		fd = open(str, O_RDONLY);
		if (fd < 0)
			return (0); // echec ouverture path
		if (data->SO)
			return (0); // info duplique 
		data->SO = ft_strdup(str);
		if (!data->SO)
			return (0); //return error msg + free si besoin
	}
	return (1);
}

int	get_ea(t_data *data, char *str)
{
	int fd;
	
	if (ft_strncmp(str, "EA", 2) == 0)
	{
		str += 2;
		if (ft_isspace(*str) == 0)
			return (0); // return error msg + free si besoin
		if	(!is_valid_path(str))
			return (0); // return error msg + free si besoin
		while (ft_isspace(*str))
			str++;
		fd = open(str, O_RDONLY);
		if (fd < 0)
			return (0); // echec ouverture path
		if (data->EA)
			return (0); // info duplique 
		data->EA = ft_strdup(str);
		if (!data->EA)
			return (0); //return error msg + free si besoin
	}
	return (1);
}

int	get_we(t_data *data, char *str)
{
	int fd;
	
	if (ft_strncmp(str, "WE", 2) == 0)
	{
		str += 2;
		if (ft_isspace(*str) == 0)
			return (0); // return error msg + free si besoin
		if	(!is_valid_path(str))
			return (0); // return error msg + free si besoin
		while (ft_isspace(*str))
			str++;
		fd = open(str, O_RDONLY);
		if (fd < 0)
			return (0); // echec ouverture path
		if (data->WE)
			return (0); // info duplique 
		data->WE = ft_strdup(str);
		if (!data->WE)
			return (0); //return error msg + free si besoin
	}
	return (1);
}
