/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:09:34 by tao               #+#    #+#             */
/*   Updated: 2025/01/24 01:26:20 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strncmp(char *first, char *second, size_t length)
{
	size_t			index;
	unsigned char	*s1;
	unsigned char	*s2;

	index = 0;
	s1 = (unsigned char *) first;
	s2 = (unsigned char *) second;
	while ((s1[index] || s2[index]) && index < length)
	{
		if (s1[index] != s2[index])
			return ((int) s1[index] - (int) s2[index]);
		index++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	sum;

	sum = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ((str[i] - '0' >= 0 && str[i] - '0' <= 9))
	{
		sum = sum * 10 + str[i] - '0';
		i++;
	}
	return (sum * sign);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'\
			|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	ft_strstrim(char *s)
{
	char	*read;
	char	*end;
	int		start;

	if (!s)
		return ;
	read = s;
	end = s;
	start = 1;
	end += ft_strlen(s) - 1;
	while (end != s && ft_isspace(*end))
		end--;
	end++;
	while (*read && read != end)
	{
		if (!ft_isspace(*read) || !start)
		{
			start = 0;
			*s = *read;
			s++;
		}
		read++;
	}
	*s = '\0';
}

char	**ft_copy_tab(char **tab)
{
	int		i;
	int		size;
	char	**copy;

	size = ft_array_len((void **)tab);
	copy = ft_calloc(sizeof(char *), (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		copy[i] = ft_strdup(tab[i]);
		if (!copy[i])
		{
			ft_free(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}
