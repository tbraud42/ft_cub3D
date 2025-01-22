/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:45:47 by brguicho          #+#    #+#             */
/*   Updated: 2025/01/22 09:17:58 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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

# define widht 1024
# define height 512

# define fov 60
# define num_ray 180

# define size_one_block 64

# define NO 0
# define SO 1
# define WE 2
# define EA 3

typedef struct s_texture {
	char	*file;
	void	*img;
	char	*addr_data;
	int		*data;
	int		img_w;
	int		img_h;
	int		bpp;
	int		size_line;
	int		endian;
}	 		t_texture;

typedef struct s_ray
{
	int 	dof;
	int 	mx;
	int 	my;
	int 	side;
	int 	lineH;
	int 	lineOff;
	int		tex_x;
	int 	tex_y;
	double	rx;
	double	ry;
	double	xo;
	double	yo;
	double	vx;
	double	vy;
	double	ra;
	double	disV;
	double	disH;
	double	Tan;
}				t_ray;


typedef struct s_data
{
	char		**map;
	void		*mlx;
	void		*mlx_win;
	void		*img_raycast; // peu etre a changer dans textures
	char 		*info_img_raycast;
	double		player[2]; // placement dans la carte, on rajoute ici l'orientation?
	double		d_player[3]; // direction
	int			color_top[3]; // couleur toit
	int			color_floor[3]; // couleur sol
	t_texture	texture[4];
	t_ray 		ray;
}				t_data;

//|-----init-----|
void 		init_data(t_data *data);
//|----parsing----|
int			ft_parse_data(t_data *data, char *argv); // remplir la struct en lisant le doc
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
int			is_map_valid(t_data *data);
char		**realloc_copy_map(char **cpy);
int			check_wall(char **copy_map);
int 		check_unknow_key(char *str);

//|----move----|
int			ft_event(int keycode, t_data *data); // fonction pour les mouvements
void 		ft_get_position(t_data *data);
void		init_player_direction(t_data *data);
void		ft_forward(t_data *data);
void		ft_backward(t_data *data);
void		ft_left(t_data *data);
void		ft_right(t_data *data);



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
char 		**ft_copy_tab(char **tab);
void		ft_free_all(t_data *data);
int			get_size_line_max(char **arr);
void		*ft_realloc(void *ptr, size_t newsize, size_t old_size);

//|-----error-----|
void		ft_free(char **map);
void		ft_error(char *erno, int choice, char **map);
void		ft_perror(char *msg_error);
int			ft_exit_mlx(t_data *data, int choice); // fonction de free mlx et destruction des structures
int			error_arg(void);
int			error_color(int flag);
int 		error_texture(int flag);
int			error_map(void);

//|-------tmp-------|
int	ft_display_window(t_data *data);
void	ft_raycasting(t_data *data, char *img);
int	ft_mouse(t_data *data);
double deg_to_rad(double angle);
double fix_ang_rad(double a);
void mlx_pixel_put_img(int *win, int x0, int y0, int color);
int	create_trgb(int t, int r, int g, int b);
void	ft_init_texture(t_data *data);
void draw_col_with_texture(int *win, int i, int column_width, float lineH, float lineOff, double wall_hit_x, double wall_hit_y, int is_vertical, t_data *data);

#endif