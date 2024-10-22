/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:46:27 by tbraud            #+#    #+#             */
/*   Updated: 2024/10/21 14:09:43 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**ft_get_map(char  **map, char *line, int fd, char *argv)
{
	int	nbr_line;
	int i;

	nbr_line = ft_count_line(fd, line);
	map = malloc(sizeof(char *) * (nbr_line + 1));
	if (!map)
		return (NULL);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_perror("file opening failure");
	i = 0;
	while (line != NULL)
	{
		if (ft_strncmp(line, " ", 1) == 0 || ft_strncmp(line, "1", 1) == 0)
		{
			map[i] = ft_strdup(line);
			if (!map[i])
				return (NULL);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (map);
}

int *ft_get_color(int *color, char *line)
{
	char	*tmp;
	char	**tmp_tab;

	tmp = NULL;
	tmp = ft_get_texture_path(tmp, line, 2);
	if (!tmp)
		return (NULL);
	tmp_tab = ft_split(tmp, ',');
	if (!tmp_tab)
		return (NULL);
	color[0] = ft_atoi(tmp_tab[0]);
	color[1] = ft_atoi(tmp_tab[1]);
	color[2] = ft_atoi(tmp_tab[2]);
	free(tmp);
	ft_free(tmp_tab);
	return (color);
	
}

char    *ft_get_texture_path(char *cardinal, char *line, int i)
{
	int	j;
	int size;
	
	j = 0;
	size = ft_strlen(line);
	cardinal = malloc((size - 1) * sizeof(char));
	if (!cardinal)
		return (NULL);
	while (i < size - 1)
	{
		cardinal[j] = line[i];
		j++;
		i++;
	}
	cardinal[j] = '\0';
	return (cardinal);
}

void    ft_get_texture(t_data *data, int fd, char *argv)
{
    char *line;
	
    line = get_next_line(fd);
    while (line != NULL)
    {
        if (ft_strncmp(line, "NO ", 3) == 0)
            data->NO = ft_get_texture_path(data->NO, line, 3);
        else if (ft_strncmp(line, "SO ", 3) == 0)	
			data->SO = ft_get_texture_path(data->SO, line, 3);
      	else if (ft_strncmp(line, "WE ", 3) == 0)
			data->WE = ft_get_texture_path(data->WE, line, 3);
        else if (ft_strncmp(line, "EA ", 3) == 0)
			data->EA = ft_get_texture_path(data->EA, line, 3);
		else if (ft_strncmp(line, "F ", 2) == 0)
			ft_get_color(data->color_floor, line);
		else if (ft_strncmp(line, "C ", 2) == 0)
			ft_get_color(data->color_top, line);
		else if (ft_strncmp(line, " ", 1) == 0 || ft_strncmp(line, "1", 1) == 0)
			data->map = ft_get_map(data->map, line, fd, argv);
		free(line);
		line = get_next_line(fd);
    }
	free(line);
}

void    ft_init_data(t_data *data, char *argv)
{
    int    fd;
	int		i;

    fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_perror("file opening failure");
    ft_get_texture(data, fd, argv);
	i= 0;
	while (data->map[i])
	{
		printf("%s", data->map[i]);
		i++;	
	}
	close(fd);
}
