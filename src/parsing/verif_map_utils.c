/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:40:08 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/06 15:22:13 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


char	**realloc_copy_map(char **cpy)
{
	int i;
	
	i = 0;
	while (cpy[i])
	{
		cpy[i] = ft_realloc(cpy[i], get_size_line_max(cpy), ft_strlen(cpy[i]) + 1);
		i++;
	}
	return (cpy);
}