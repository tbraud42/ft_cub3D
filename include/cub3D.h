/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraud <tbraud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:30:03 by tbraud            #+#    #+#             */
/*   Updated: 2024/12/03 17:50:21 by tbraud           ###   ########.fr       */
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
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# define ON_KEYDOWN 2
# define ON_DESTROY 17
# define ESCAPE 65307

# define PI 3.1415926535
# define P2 1.5707963267
# define P3 4.7123889803

typedef struct s_img
{
	void	*img;
	char	*relative_path;
	int		img_width;
	int		img_height;
}			t_img;

typedef struct s_data
{
	char	**map;
	void	*mlx;
	void	*mlx_win;
	void	*img[8]; // texture
	float	player[2]; // placement dans la carte, on rajoute ici l'orientation?
	float	d_player[3]; // direction
	int		color_top[3]; // couleur toit
	int		color_floor[3]; // couleur sol
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;

	int		size_map[2];
	t_img	tmp_a;
	t_img	tmp_b;
	t_img	tmp_c;
}			t_data;

//|----parsing----|
void		ft_init_data(t_data *data, char *argv); // remplir la struct en lisant le doc
char    	**ft_get_file_in_tab(int fd);
int			is_valid_path(char *str);
int			get_no(t_data *data, char *str);
int			get_so(t_data *data, char *str);
int			get_we(t_data *data, char *str);
int			get_ea(t_data *data, char *str);
int 		get_map_colors(t_data *data, char *str);
int			duplicated_color(t_data *data, int flag);
int			get_top_color(t_data *data, char *str);
int			get_floor_color(t_data *data, char *str);
//|----move----|
int			ft_event(int keycode, t_data *data); // fonction pour les mouvements

//|-----utils-----|
int			ft_strlen(char *arr);
int			ft_array_len(void **array);
char		*get_next_line(int fd);
void		ft_bzero(char *s, size_t n);
char		*ft_strdup(char *s);
int			ft_strchr(char *s, int c);
char		*ft_strjoin(char *s1, char *s2);
void		ft_putnbr(size_t n);
int			ft_strncmp(char *first, char *second, size_t length);
int			ft_atoi(const char *str);
char		**ft_split(char const *s, char c);
void		ft_strstrim(char *s);
int			ft_isspace(int c);
void		ft_putstr_fd(char *s, int fd);
void		*ft_calloc(size_t nmemb, size_t size);

//|-----error-----|
void		ft_free(char **map);
void		ft_error(char *erno, int choice, char **map);
void		ft_perror(char *msg_error);
int			ft_exit_mlx(t_data *data, int choice); // fonction de free mlx et destruction des structures
int			error_arg(void);
int			error_color(int flag);

//|-------tmp-------|
int	ft_draw_map(t_data *data);
int	ft_display_window(t_data *data);
void	ft_raycasting(t_data *data, int mapX, int mapY);
int	ft_mouse(t_data *data);
float deg_to_rad(float angle);
int fix_ang(int a);
void	draw_col(t_data *data, int col, int lineH, int lineOff);

#endif /*CUB3D_H */
