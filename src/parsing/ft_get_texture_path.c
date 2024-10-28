/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_texture_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:42:04 by brguicho          #+#    #+#             */
/*   Updated: 2024/10/25 12:33:42 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		if (data->NO)
			return (0); // info duplique 
		data->NO = ft_strdup(str);
		if (!data->NO)
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
		if (data->NO)
			return (0); // info duplique 
		data->NO = ft_strdup(str);
		if (!data->NO)
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
		if (data->NO)
			return (0); // info duplique 
		data->NO = ft_strdup(str);
		if (!data->NO)
			return (0); //return error msg + free si besoin
	}
	return (1);
}
