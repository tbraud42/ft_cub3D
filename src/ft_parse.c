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

// void    ft_

// void    ft_get_texture(t_data *data, int fd)
// {
//     char    *line;

//     while (1)
//     {
//         line = get_next_line(fd);
//         if (ft_strnstr(line, "NO ", -1))
//             ft_get_texture_path(data->NO);
//         else if (ft_strnstr(line, "SO ", -1))
// 			ft_get_texture_path(data->SO);
//         else if (ft_strnstr(line, "WE ", -1))
// 			ft_get_texture_path(data->WE);
//         else if (ft_strnstr(line, "EA ", -1))
// 			ft_get_texture_path(data->EA);
//         else if (ft_strnstr(line, "F ", -1))
// 			ft_get_color(data->color_floor);
//         else if (ft_strnstr(line, "C ", -1))
// 			ft_get_color(data->color_floor);
//     }
// }

void    ft_init_data(t_data *data, char *argv)
{
    int    fd;

    fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_perror("card opening failure");
	close(fd);
	(void)data;
    // ft_get_texture(data, fd);
}

