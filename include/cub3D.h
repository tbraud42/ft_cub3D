/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:30:03 by tbraud            #+#    #+#             */
/*   Updated: 2024/10/15 03:01:23 by tao              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# define ON_KEYDOWN 2
# define ON_DESTROY 17
# define ESCAPE 65307

typedef struct s_data
{
	char	**map;
	void	*mlx;
	void	*mlx_win;
	void	*img[8]; // texture
	int		player[2]; // placement dans la carte, on rajoute ici l'orientation?
	int		color_top[3]; // couleur toit
	int		color_floor[3]; // couleur sol
}			t_data;

//|----parsing----|
void		ft_init_data(t_data *data, char *argv); // remplir la struct en lisant le doc

//|----move----|
int			ft_event(int keycode, t_data *data); // fonction pour les mouvements

//|-----utils-----|
int			ft_strlen(char *arr);
char		*get_next_line(int fd);
void		ft_bzero(char *s, size_t n);
char		*ft_strdup(char *s);
int			ft_strchr(char *s, int c);
char		*ft_strjoin(char *s1, char *s2);
void		ft_putnbr(size_t n);

//|-----error-----|
void		ft_free(char **map);
void		ft_error(char *erno, int choice, char **map);
void		ft_perror(char *msg_error);
int			ft_exit_mlx(t_data *data, int choice); // fonction de free mlx et destruction des structures

#endif /*CUB3D_H */
