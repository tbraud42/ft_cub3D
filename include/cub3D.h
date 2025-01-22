/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:30:03 by tbraud            #+#    #+#             */
/*   Updated: 2025/01/22 22:10:04 by brguicho         ###   ########.fr       */
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

# define WIDTH 1024
# define HEIGHT 512

# define FOV 60
# define NUM_RAY 1024
# define RENDER_DIST 2048

# define SIZE_ONE_BLOCK 64

# define NO 0
# define SO 1
# define WE 2
# define EA 3

typedef struct s_texture
{
	char	*file;
	void	*img;
	char	*addr_data;
	int		*data;
	int		img_w;
	int		img_h;
	int		bpp;
	int		size_line;
	int		endian;
}				t_texture;

typedef struct s_ray
{
	int		side;
	double	line_dimensions[2];
	double	ray_data[3];
	double	ray_step[2];
	double	dist[2];
}				t_ray;

typedef struct s_data
{
	char		**map;
	void		*mlx;
	void		*mlx_win;
	void		*img_raycast;
	char		*info_img_raycast;
	size_t		map_width;
	size_t		map_height;
	double		player[2];
	double		d_player[3];
	int			color_top[3];
	int			color_floor[3];
	t_texture	texture[4];
	t_ray		ray;
}				t_data;
//|-----init-----|
void		init_data(t_data *data);
//|----parsing----|
int			ft_parse_data(t_data *data, char *argv);
char		**ft_get_file_in_tab(int fd);
int			is_valid_path(char *str);
int			get_no(t_data *data, char *str);
int			get_so(t_data *data, char *str);
int			get_we(t_data *data, char *str);
int			get_ea(t_data *data, char *str);
int			get_map_colors(t_data *data, char *str);
int			duplicated_color(t_data *data, int flag);
int			get_top_color(t_data *data, char *str);
int			get_floor_color(t_data *data, char *str);
int			is_map_valid(t_data *data);
char		**realloc_copy_map(char **cpy);
int			check_wall(char **copy_map);
int			check_unknow_key(char *str);
int			check_size_map(t_data *data);
int			check_len_number(char **tab);

//|----move----|
int			ft_event(int keycode, t_data *data); // fonction pour les mouvements
void		ft_get_position(t_data *data);
void		init_player_direction(t_data *data);
void		ft_forward(t_data *data);
void		ft_backward(t_data *data);
void		ft_left(t_data *data);
void		ft_right(t_data *data);
void		ft_right_arrow(t_data *data);
void		ft_left_arrow(t_data *data);

//|-----utils-----|
void		ft_free_array(char **map);
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
char		**ft_copy_tab(char **tab);
void		ft_free_all(t_data *data);
int			get_size_line_max(char **arr);
void		*ft_realloc(void *ptr, size_t newsize, size_t old_size);

//|-----error-----|
void		ft_free(char **map);
void		ft_error(char *erno, int choice, char **map);
void		ft_perror(char *msg_error);
int			ft_exit_mlx(t_data *data, int choice);
int			error_arg(void);
int			error_color(int flag);
int			error_texture(int flag);
int			error_map(void);

//|-------render-------|
int			ft_display_window(t_data *data);
void		ft_raycasting(t_data *data, int *win);
double		deg_to_rad(double angle);
double		fix_ang_rad(double a);
void		calculate_ray_horizontal(t_data *data, t_ray *math, double tan_ra);
void		calculate_ray_vertical(t_data *data, t_ray *math, double tan_ra);
double		ft_dist(double ax, double ay, double bx, double by);
void		mlx_pixel_put_img(int *win, int x0, int y0, int color);
int			create_trgb(int t, int r, int g, int b);
void		ft_init_texture(t_data *data);
void		ft_config_data_texture(t_data *data, t_ray *math, int *win, int i);

#endif /*CUB3D_H */
