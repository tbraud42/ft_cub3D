/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tao <tao@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:30:03 by tbraud            #+#    #+#             */
/*   Updated: 2024/10/15 02:20:17 by tao              ###   ########.fr       */
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
	int		player[2];
}			t_data;

//|----move----|
int			ft_event(int keycode, t_data *data);

//|----parsing----|
char		**ft_creat_map(t_data *data, char *argv);

//|-----gnl------|
char		*get_next_line(int fd);

//|-----utils-----|
void		ft_bzero(char *s, size_t n);
char		*ft_strdup(char *s);
int			ft_strchr(char *s, int c);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strlen(char *arr);
void		ft_putnbr(size_t n);

//|-----error-----|
void		ft_free(char **map);
void		ft_error(char *erno, int choice, char **map);
void		ft_perror(void);
int			ft_exit_mlx(t_data *data, int choice);

#endif /*CUB3D_H */
