/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:46:27 by tbraud            #+#    #+#             */
/*   Updated: 2025/01/27 13:39:31 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	get_path_and_colors(t_data *data, char **arr, size_t i)
{
	size_t	error;

	error = 0;
	if (arr[i][0] != '\0')
		ft_strstrim(arr[i]);
	if (!check_unknow_key(arr[i]))
	{
		error_arg();
		error = 1;
	}
	if (!error && !get_no(data, arr[i]))
		error = 1;
	if (!error && !get_so(data, arr[i]))
		error = 1;
	if (!error && !get_we(data, arr[i]))
		error = 1;
	if (!error && !get_ea(data, arr[i]))
		error = 1;
	if (!error && !get_map_colors(data, arr[i]))
		error = 1;
	return (error);
}

static char	**ft_get_map(char **tab, int tab_len, int start)
{
	char	**map;
	int		size;
	int		i;

	size = tab_len - start;
	map = ft_calloc(sizeof(char *), size + 1);
	i = 0;
	if (!map)
		return (NULL);
	while (tab[start])
	{
		map[i] = ft_strdup(tab[start]);
		if (!map[i])
		{
			ft_free(map);
			return (NULL);
		}
		i++;
		start++;
	}
	return (map);
}

int	get_element_from_tab(char **tab, t_data *data)
{
	int		i;
	char	*tmp;
	int		count;

	i = 0;
	count = 0;
	while (i < ft_array_len((void **)tab))
	{
		tmp = tab[i];
		while (ft_isspace(*tmp))
			tmp++;
		if (*tmp == '1' || *tmp == '0')
			break ;
		if (tab[i][0] != '\0')
			ft_strstrim(tab[i]);
		if (check_unknow_key(tab[i]))
			count++;
		if (get_path_and_colors(data, tab, i))
			return (0);
		i++;
	}
	if (count != 6)
		return (error_missing_key());
	data->map = ft_get_map(tab, ft_array_len((void **)tab), i);
	return (1);
}

char	**ft_get_file_in_tab(int fd)
{
	char	*line;
	char	*tmp;
	char	**tmp_tab;

	tmp_tab = NULL;
	line = get_next_line(fd);
	tmp = ft_strdup("");
	if (!tmp)
		return (NULL);
	while (line != NULL)
	{
		tmp = ft_strjoin(tmp, line);
		if (!tmp)
		{
			free(line);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	tmp_tab = ft_split(tmp, '\n');
	free(tmp);
	if (!tmp_tab)
		return (NULL);
	return (tmp_tab);
}

int	ft_parse_data(t_data *data, char *argv)
{
	int		fd;
	char	**tab;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_perror("file opening failure");
	tab = ft_get_file_in_tab(fd);
	close(fd);
	if (get_element_from_tab(tab, data) == 0)
	{
		ft_free(tab);
		ft_free_all(data);
		return (0);
	}
	ft_free(tab);
	ft_get_position(data);
	if (!is_map_valid(data))
	{
		ft_free_all(data);
		return (0);
	}
	return (1);
}
