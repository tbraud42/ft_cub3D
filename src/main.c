/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraud <tbraud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:19:33 by tbraud            #+#    #+#             */
/*   Updated: 2024/04/27 02:16:45 by tbraud           ###   ########.fr       */
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
	t_ptr	ptr;

	if (argc != 2 || !argv[1])
		ft_error("pls give me one map please\n", 0, 0);
	if (ft_test_input(argv[1]))
		ft_error("pls give me a map with extension .cub\n", 0, 0);
	ptr.map = ft_creat_map(argv, &ptr.size_map);
	ptr.index = 0;
	ptr.item = ft_find_point(ptr.map, 'c', ptr.exit);
	ft_find_point(ptr.map, 'e', ptr.exit);
	ft_find_point(ptr.map, 'P', ptr.player);
	ptr.mlx = mlx_init();
	if (!ptr.mlx)
		ft_error("mlx does not launch correctly\n", 1, ptr.map);
	ptr.mlx_win = mlx_new_window(ptr.mlx, (ft_strlen(ptr.map[0])) * 32,
			ptr.size_map * 32, "cub3D<3");
	ft_insert_map(&ptr); // a changer
	ptr.map[ptr.player[1]][ptr.player[0]] = 'o';
	mlx_hook(ptr.mlx_win, ON_KEYDOWN, (1L << 0), ft_event, &ptr);
	mlx_hook(ptr.mlx_win, ON_DESTROY, (1L << 0), ft_exit_mlx, &ptr);
	mlx_loop(ptr.mlx);
}
