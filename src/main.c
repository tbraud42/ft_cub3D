/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:19:33 by tbraud            #+#    #+#             */
/*   Updated: 2024/12/20 13:17:59 by tao              ###   ########.fr       */
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

	data.NO = NULL;
	data.SO = NULL;
	data.WE = NULL;
	data.EA = NULL;
	data.map = NULL;
	data.color_floor[0] = 0;
	data.color_floor[1] = 0;
	data.color_floor[2] = 0;
	data.color_top[0] = 0;
	data.color_top[1] = 0;
	data.color_top[2] = 0;
	data.img_r = NULL;
	if (argc != 2 || !argv[1])
		ft_error("pls give me one map please\n", 0, 0);
	if (ft_test_input(argv[1]))
		ft_error("pls give me a map with extension .cub\n", 0, 0);
	ft_init_data(&data, argv[1]);
	data.mlx = mlx_init();
	if (!data.mlx)
		ft_error("mlx does not launch correctly\n", 1, data.map);
	ft_draw_map(&data);
	data.mlx_win = mlx_new_window(data.mlx, 1024, 512, "cub3D<3");
	if (!data.mlx_win)
		ft_error("somthing wrong with the mlx windows\n", 0, 0);
	mlx_mouse_hide(data.mlx, data.mlx_win); // pas sur
	mlx_mouse_move(data.mlx, data.mlx_win, height, widht);
	mlx_loop_hook(data.mlx, ft_display_window, &data);
	// mlx_loop_hook(data.mlx, ft_mouse, &data);
	mlx_hook(data.mlx_win, ON_KEYDOWN, (1L << 0), ft_event, &data);
	mlx_hook(data.mlx_win, ON_DESTROY, (1L << 0), ft_exit_mlx, &data);
	mlx_loop(data.mlx);
}
