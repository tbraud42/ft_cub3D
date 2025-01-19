/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:19:33 by tbraud            #+#    #+#             */
/*   Updated: 2025/01/19 22:33:25 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_test_input(char *av)
{
	int	i;

	i = ft_strlen(av);
	if (i <= 4)
		return (1);
	if (av[i - 4] != '.' || av[i - 3] != 'c' || av[i - 2] != 'u' || av[i
		- 1] != 'b')
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	init_data(&data);
	if (argc != 2 || !argv[1])
		ft_error("pls give me one map please\n", 0, 0);
	if (ft_test_input(argv[1]))
		ft_error("pls give me a map with extension .cub\n", 0, 0);
	if (ft_parse_data(&data, argv[1]) == 0)
		return (1);
	data.player[0] *= size_one_block;
	data.player[1] *= size_one_block;
	data.mlx = mlx_init();
	if (!data.mlx)
		ft_error("mlx does not launch correctly\n", 1, data.map);
	data.mlx_win = mlx_new_window(data.mlx, widht, height, "cub3D<3");
	if (!data.mlx_win)
		ft_error("somthing wrong with the mlx windows\n", 0, 0);
	mlx_loop_hook(data.mlx, ft_display_window, &data);
	mlx_hook(data.mlx_win, ON_KEYDOWN, (1L << 0), ft_event, &data);
	mlx_hook(data.mlx_win, ON_DESTROY, (1L << 0), ft_exit_mlx, &data);
	mlx_loop(data.mlx);
}
