/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:46:27 by tbraud            #+#    #+#             */
/*   Updated: 2024/10/15 03:23:05 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_get_texture(t_data *data, int fd)
{
	(void)data;
	(void)fd;
}

void	ft_init_data(t_data *data, char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_perror("card opening failure");
	ft_get_texture(data, fd);
}

