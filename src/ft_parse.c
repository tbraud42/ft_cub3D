/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraud <tbraud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:46:27 by tbraud            #+#    #+#             */
/*   Updated: 2024/04/23 18:49:56 by tbraud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static size_t	ft_size_map(char *argv[])
{
	int		fd;
	size_t	size;
	char	*tmp;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_perror();
	size = 0;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		size++;
		free(tmp);
	}
	close(fd);
	if (size >= 3)
		return (size);
	ft_error("the map is empty\n", 0, 0);
	return (0);
}

static void	ft_put_map(char *argv[], char **map, int size)
{
	int		fd;
	int		i;
	char	*tmp;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		free(map);
		ft_perror();
	}
	i = 0;
	while (i < size)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		if (tmp[ft_strlen(tmp) - 1] == '\n')
			tmp[ft_strlen(tmp) - 1] = '\0';
		map[i] = tmp;
		i++;
	}
	close(fd);
}

static void	ft_test_block(char **map, int size)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) != x)
			ft_error("the map is not rectangular\n", 1, map);
		j = 0;
		while (map[i][j])
		{
			if ((i == 0 || i == (size - 1)) && map[i][j] != '1')
				ft_error("wrong map given\n", 1, map);
			if ((j == 0 || j == x - 1) && map[i][j] != '1')
				ft_error("wrong map given\n", 1, map);
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'C'
				&& map[i][j] != 'E' && map[i][j] != 'P')
				ft_error("wrong map given\n", 1, map);
			j++;
		}
		i++;
	}
}

static int	ft_find_issue(char **map, int x, int y, int *item) // a changer
{
	if (map[y][x] == '1' || map[y][x] == 'o' || map[y][x] == 'c'
		|| map[y][x] == 'e')
		return (0);
	if (map[y][x] == '0')
		map[y][x] = 'o';
	if (map[y][x] == 'C')
	{
		*item -= 1;
		map[y][x] = 'c';
	}
	if (map[y][x] == 'E')
	{
		map[y][x] = 'e';
		return (ft_find_issue(map, x - 1, y, item) + ft_find_issue(map, x + 1,
				y, item) + ft_find_issue(map, x, y - 1, item)
			+ ft_find_issue(map, x, y + 1, item) + 1);
	}
	return (ft_find_issue(map, x - 1, y, item) + ft_find_issue(map, x + 1, y,
			item) + ft_find_issue(map, x, y - 1, item) + ft_find_issue(map, x, y
			+ 1, item));
}

char	**ft_creat_map(char *argv[], size_t *size)
{
	char	**map;
	int		point[2];
	int		item;

	*size = ft_size_map(argv);
	map = malloc(sizeof(char *) * (*size + 1));
	if (!map)
		ft_error("error with malloc\n", 0, 0);
	map[*size] = NULL;
	ft_put_map(argv, map, *size);
	ft_test_block(map, *size);
	ft_check_duplicates(map);
	item = ft_find_point(map, 'C', point);
	if (item == 0 || ft_find_point(map, 'P', point) == 0)
		ft_error("the map is not possible\n", 1, map);
	if (ft_find_issue(map, point[0], point[1], &item) == 0 || item != 0)
		ft_error("the map is not possible\n", 1, map);
	return (map);
}
