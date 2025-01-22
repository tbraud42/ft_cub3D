/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:19:33 by tbraud            #+#    #+#             */
/*   Updated: 2025/01/22 04:28:24 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_test_input(char *av)
{
	int	i;

	i = ft_strlen(av);
	if (i <= 4)
		return (1);
	if (av[i - 4] != '.' || av[i - 3] != 'c' || av[i - 2] != 'u'
		|| av[i - 1] != 'b')
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
	init_player_direction(&data);
	data.mlx = mlx_init();
	if (!data.mlx)
		ft_error("mlx does not launch correctly\n", 1, data.map);
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "cub3D<3");
	if (!data.mlx_win)
		ft_error("somthing wrong with the mlx windows\n", 0, 0);
	ft_init_texture(&data);
	mlx_loop_hook(data.mlx, ft_display_window, &data);
	mlx_hook(data.mlx_win, ON_KEYDOWN, (1L << 0), ft_event, &data);
	mlx_hook(data.mlx_win, ON_DESTROY, (1L << 0), ft_exit_mlx, &data);
	mlx_loop(data.mlx);
}
