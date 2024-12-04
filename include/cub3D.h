/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:30:03 by tbraud            #+#    #+#             */
/*   Updated: 2024/12/04 08:12:35 by brguicho         ###   ########.fr       */
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

# define S_WIDTH 600
# define S_HEIGHT 900

typedef struct s_raycast
{
	double 	dir_x;
	double 	dir_y;
	double 	plane_y;
	double 	plane_x;
	double 	sidedist_x;
	double 	sidedist_y;
	double	camera_x;
	double	deltadist_x;
	double	deltadist_y;
	double 	perpwalldist;
	double	ray_x;
	double	ray_y;
	int		side_wall;
	int		hit_wall;
	int		step_x;
	int		step_y;
	int 	map_x;
	int 	map_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
}				t_raycast;

# define S_WIDTH 600
# define S_HEIGHT 900

typedef struct s_raycast
{
	double 	dir_x;
	double 	dir_y;
	double 	plane_y;
	double 	plane_x;
	double 	sidedist_x;
	double 	sidedist_y;
	double	camera_x;
	double	deltadist_x;
	double	deltadist_y;
	double 	perpwalldist;
	double	ray_x;
	double	ray_y;
	int		side_wall;
	int		hit_wall;
	int		step_x;
	int		step_y;
	int 	map_x;
	int 	map_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
}				t_raycast;

typedef struct s_data
{
	char	**map;
	void	*mlx;
	void	*mlx_win;
	void	*img[8]; // texture
	float	player[2]; // placement dans la carte, on rajoute ici l'orientation?
	char	player_orientation;
	int		color_top[3]; // couleur toit
	int		color_floor[3]; // couleur sol
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	t_raycast *raycast;
	t_raycast *raycast;
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
int			is_map_valid(t_data *data);
char		**realloc_copy_map(char **cpy);

//|----move----|
int			ft_event(int keycode, t_data *data); // fonction pour les mouvements
void 		ft_get_position(t_data *data);

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
void		*ft_realloc(void *ptr, size_t newsize);

//|-----error-----|
void		ft_free(char **map);
void		ft_error(char *erno, int choice, char **map);
void		ft_perror(char *msg_error);
int			ft_exit_mlx(t_data *data, int choice); // fonction de free mlx et destruction des structures
int			error_arg(void);
int			error_color(int flag);
int 		error_texture(int flag);

#endif /*CUB3D_H */
