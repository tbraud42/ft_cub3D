/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraud <tbraud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:07:13 by tbraud            #+#    #+#             */
/*   Updated: 2024/04/22 03:29:26 by tbraud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strlen(char *arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_putnbr(size_t n)
{
	char	tmp;

	if (n < 10)
	{
		tmp = n + '0';
		write(1, &tmp, 1);
	}
	else
	{
		ft_putnbr(n / 10);
		tmp = (n % 10) + '0';
		write(1, &tmp, 1);
	}
}
