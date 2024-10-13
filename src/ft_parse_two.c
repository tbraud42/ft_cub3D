/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraud <tbraud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 05:18:39 by tbraud            #+#    #+#             */
/*   Updated: 2024/04/24 20:14:11 by tbraud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_find_point(char **map, char to_find, int point[2])
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == to_find && count == 0)
			{
				point[0] = x;
				point[1] = y;
				count++;
			}
			else if (map[y][x] == to_find)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	ft_check_duplicates(char **map)
{
	int	i;
	int	j;
	int	point_p;
	int	point_e;

	i = 0;
	point_e = 0;
	point_p = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
				point_e++;
			else if (map[i][j] == 'P')
				point_p++;
			j++;
		}
		i++;
	}
	if (point_e != 1 || point_p != 1)
		ft_error("wrong map given\n", 1, map);
}

static void	*ft_choose_img(char block, t_ptr *ptr)
{
	if (block == '1')
		return (ptr->img[0]);
	else if (block == 'o' || block == '0')
		return (ptr->img[1]);
	else if (block == 'c')
		return (ptr->img[2]);
	else if (block == 'P')
		return (ptr->img[3]);
	else if (block == 'e')
		return (ptr->img[4]);
	return (0);
}

static void	ft_parse_img(t_ptr *ptr)
{
	int	i[2];
	int	j;

	ptr->img[0] = mlx_xpm_file_to_image(ptr->mlx, "sprite/wall.xpm", &i[0],
			&i[1]);
	ptr->img[1] = mlx_xpm_file_to_image(ptr->mlx, "sprite/floor.xpm", &i[0],
			&i[1]);
	ptr->img[2] = mlx_xpm_file_to_image(ptr->mlx, "sprite/item.xpm", &i[0],
			&i[1]);
	ptr->img[3] = mlx_xpm_file_to_image(ptr->mlx, "sprite/player.xpm", &i[0],
			&i[1]);
	ptr->img[4] = mlx_xpm_file_to_image(ptr->mlx, "sprite/c_door.xpm", &i[0],
			&i[1]);
	ptr->img[5] = mlx_xpm_file_to_image(ptr->mlx, "sprite/o_door.xpm", &i[0],
			&i[1]);
	ptr->img[6] = mlx_xpm_file_to_image(ptr->mlx, "sprite/player_door.xpm",
			&i[0], &i[1]);
	ptr->img[7] = mlx_xpm_file_to_image(ptr->mlx, "sprite/player_floor.xpm",
			&i[0], &i[1]);
	j = 0;
	while (j < 8 && ptr->img[j])
		j++;
	if (j != 8)
		ft_exit_mlx(ptr, 1);
}

void	ft_insert_map(t_ptr *ptr)
{
	(void)ptr;
}
