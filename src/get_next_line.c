/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraud <tbraud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:48:19 by tbraud            #+#    #+#             */
/*   Updated: 2024/04/18 21:32:13 by tbraud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_sort_save_tab(char *tab, char save_tab[])
{
	int	i;
	int	j;

	if (!tab)
		return ;
	i = 0;
	while (tab[i] && tab[i] != '\n')
		i++;
	if (tab[i])
		i++;
	j = i;
	while (tab[i])
	{
		save_tab[i - j] = tab[i];
		tab[i] = '\0';
		i++;
	}
	save_tab[i - j] = '\0';
}

static int	ft_line(int fd, char **tab, char save_tab[])
{
	int		i;

	i = read (fd, save_tab, BUFFER_SIZE);
	if (i == -1 || i == 0)
		return (i);
	save_tab[i] = '\0';
	if (!*tab)
		*tab = ft_strdup(save_tab);
	else
		*tab = ft_strjoin(*tab, save_tab);
	return (i);
}

char	*get_next_line(int fd)
{
	static char	save_tab[BUFFER_SIZE + 1];
	char		*tab;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (0);
	tab = 0;
	if (save_tab[0])
		tab = ft_strdup(save_tab);
	ft_bzero(save_tab, BUFFER_SIZE + 1);
	i = BUFFER_SIZE;
	while (ft_strchr(tab, '\n') && i == BUFFER_SIZE)
		i = ft_line(fd, &tab, save_tab);
	if (i == -1)
		return (0);
	ft_bzero(save_tab, BUFFER_SIZE + 1);
	ft_sort_save_tab(tab, save_tab);
	return (tab);
}
