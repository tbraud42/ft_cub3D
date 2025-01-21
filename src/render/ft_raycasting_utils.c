/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:02:57 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/21 00:10:19 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	deg_to_rad(double angle)
{
	return (angle * M_PI / 180.0);
}

double	fix_ang_rad(double a)
{
	if (a > 2 * M_PI)
		a -= 2 * M_PI;
	if (a < 0)
		a += 2 * M_PI;
	return (a);
}

double	ft_dist(double ax, double ay, double bx, double by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}
