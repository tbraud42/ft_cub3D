/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:46:27 by tbraud            #+#    #+#             */
/*   Updated: 2024/10/26 17:52:40 by brguicho         ###   ########.fr       */
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
	if (error)
	{
		ft_free(arr);
		return (error);
	}
	return (error);
}

void	get_element_from_tab(char **tab, t_data *data)
{
	int i;
	char *tmp;

	i = 0;
	while (tab[i])
	{
		tmp = tab[i];
		while (ft_isspace(*tmp))
			tmp++;
		if (*tmp == '1' || *tmp == '0')
			break;
		if (!get_path_and_colors(data, tab, i))
			return ;
		i++;
	}
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
	if (!tmp_tab)
		return (NULL);
	if (line)
		free(line);
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
}
