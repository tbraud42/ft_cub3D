/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:30:03 by tbraud            #+#    #+#             */
/*   Updated: 2025/01/08 21:19:33 by brguicho         ###   ########.fr       */
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

# define widht 1024
# define height 512

# define fov 60
# define num_ray 60

# define size_one_block 64
// variable selon les texture ?

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_data
{
	char	**map;
	void	*mlx;
	void	*mlx_win;
	double	player[2]; // placement dans la carte, on rajoute ici l'orientation?
	double	d_player[3]; // direction
	int		color_top[3]; // couleur toit
	int		color_floor[3]; // couleur sol
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;

	void	*img_raycast;

	void	*img_map;

}			t_data;

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

//|----move----|
int			ft_event(int keycode, t_data *data); // fonction pour les mouvements
void 		ft_get_position(t_data *data);
void		init_player_direction(t_data *data);

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
int			error_map();

//|-------tmp-------|
int	ft_display_window(t_data *data);
void	ft_raycasting(t_data *data, char *img);
int	ft_mouse(t_data *data);
double deg_to_rad(double angle);
double fix_ang_rad(double a);
void draw_col(int *win, int i, int column_width, float lineH, float lineOff, int color);
void mlx_pixel_put_img(int *win, int x0, int y0, int color);
int	create_trgb(int t, int r, int g, int b);

#endif /*CUB3D_H */
