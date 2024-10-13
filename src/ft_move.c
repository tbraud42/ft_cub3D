/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraud <tbraud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 04:56:39 by tbraud            #+#    #+#             */
/*   Updated: 2024/04/27 02:17:18 by tbraud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_forward(t_ptr *ptr)
{
	(void)ptr;
}

static void	ft_backward(t_ptr *ptr)
{
	(void)ptr;
}

static void	ft_left(t_ptr *ptr)
{
	(void)ptr;
}

static void	ft_right(t_ptr *ptr)
{
	(void)ptr;
}

void	ft_choose(int keycode, t_ptr *ptr)
{
	if (keycode == 'w')
		ft_foward(ptr);
	else if (keycode == 's')
		ft_backward(ptr);
	else if (keycode == 'a')
		ft_left(ptr);
	else if (keycode == 'd')
		ft_right(ptr);
}

int	ft_event(int keycode, t_ptr *ptr) // upgrade pour cub
{
	if (keycode == ESCAPE)
		ft_exit_mlx(ptr, 0);
	ft_choose(keycode, ptr);
	if (ptr->map[ptr->player[1]][ptr->player[0]] == 'c')
		ptr->map[ptr->player[1]][ptr->player[0]] = 'o';
	if (ptr->item == 0)
		mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->img[5],
			ptr->exit[0] * 32, ptr->exit[1] * 32);
	return (0);
}
