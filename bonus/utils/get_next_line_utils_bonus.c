/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:23:00 by tbraud            #+#    #+#             */
/*   Updated: 2025/01/23 15:23:21 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

char	*ft_strdup(char *s)
{
	int		i;
	char	*dest;

	dest = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dest)
		return (0);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_bzero(char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		s[i] = '\0';
		i++;
	}
}

int	ft_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*tab;
	int		len_s1;
	int		len_all;

	if (!s1)
		len_s1 = 0;
	else
		len_s1 = ft_strlen(s1);
	len_all = len_s1 + ft_strlen(s2);
	tab = malloc(sizeof(char) * (len_all + 1));
	if (!tab)
		return (0);
	i = 0;
	while (i < len_all)
	{
		if (i < len_s1)
			tab[i] = s1[i];
		else
			tab[i] = s2[i - len_s1];
		i++;
	}
	tab[i] = '\0';
	free(s1);
	return (tab);
}
