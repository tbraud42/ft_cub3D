/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:46:27 by tbraud            #+#    #+#             */
/*   Updated: 2024/11/20 10:01:15 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		get_path_and_colors(t_data *data, char **arr, size_t i)
{
	size_t	error;

	error = 0;
	ft_strstrim(arr[i]);
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
	if (error == 1)
	{
		ft_free(arr);
		ft_free_all(data);
		return (error);
	}
	return (error);
}
static char	**ft_get_map(char **tab, int tab_len, int start)
{
	char **map;
	int size;
	int	i;

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

void	get_element_from_tab(char **tab, t_data *data)
{
	int i;
	char *tmp;
	int	tab_len;

	i = 0;
	tab_len = ft_array_len((void **)tab);
	while (i < tab_len)
	{
		tmp = tab[i];
		while (ft_isspace(*tmp))
			tmp++;
		if (*tmp == '1' || *tmp == '0')
			break;
		if (get_path_and_colors(data, tab, i))
			return ;
		i++;
	}
	data->map = ft_get_map(tab, tab_len, i);
	
}

char **ft_get_file_in_tab(int fd)
{
    char *line;
	char *tmp;
	char **tmp_tab;
	
	tmp_tab = NULL;
    line = get_next_line(fd);
	tmp = ft_strdup("");
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

void    ft_init_data(t_data *data, char *argv)
{
    int		fd;
	char	**tab;

    fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_perror("file opening failure");
    tab = ft_get_file_in_tab(fd);
	close(fd);
	get_element_from_tab(tab, data);
	ft_free(tab);
	ft_get_position(data);
	if (!is_map_valid(data))
	{
		ft_free_all(data);
	}

}
