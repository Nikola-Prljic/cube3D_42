/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:10:20 by rkurnava          #+#    #+#             */
/*   Updated: 2023/09/13 14:15:05 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WINDOW_WITH 300
# define WINDOW_HEIGT 300
# define TILE_SIZE 32
# define PI 3.14159

typedef struct s_ray_cast
{
	int			up_down;
	int			left_right;
	double		off;
	double		fov;
	double		plane;
	double		vl;
	double		hl;
	double		v_x;
	double		v_y;
	double		h_x;
	double		h_y;
	char		view_point;
	double		player_dir;
	double		player_dir_x;
	double		player_dir_y;
	double		px;
	double		py;
	double		ray_angle;
}				t_ray_cast;

typedef struct s_texture
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
}				t_texture;

typedef struct s_img
{
	void		*img;
	int			width;
	int			height;
	int			*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_texture_draw
{
	double		top;
	int			ray_x;
	double		wall_strip;
	double		bottom;
}				t_texture_draw;

typedef struct s_data
{
	t_texture	*texture;
	t_img		*img;
	t_img		*north;
	t_img		*south;
	t_img		*west;
	t_img		*east;
	int			distance;
	int			vertrical_hit;
	int			floor_rgb;
	int			sky_rgb;
	char		**map;
	char		**map_copy;
	void		*mlx_ptr;
	void		*win_ptr;
	int			py;
	int			px;
	int			map_y;
	int			map_x;
	t_ray_cast	*rays;
	int			raycount;
}				t_data;

typedef struct s_map
{
	int			fd;
	char		*buffer;
}				t_map;

typedef struct s_path
{
	int			x;
	int			y;
}				t_path;

typedef struct s_rect
{
	int			start_y;
	int			start_x;
	int			size_y;
	int			size_x;
	int			color;
}				t_rect;

typedef struct s_handle_textures
{
	short		is_new_line;
	char		*direction;
	char		*texture_path;
}				t_handle_textures;

//input_handle.c
int				input_handle(int argc, char **argv, int *fd);

//main.c
int				free_data(t_data *data);

//player_action.c
int				keypress(int keysum, t_data *data);

//ft_atoi
int				ft_atoi(const char *nptr);

//map_check_utils.c
int				charinstr(char c, char *valid_chars);
int				isvalidchar(t_data *data, char *mapstr, char *valid_chars,
					int y);
int				free_map_exit(t_data *data, t_map *file, char *msg);
int				ft_matrix_push_back(t_data *data, t_map *file, char *str);
char			*saveline(t_data *data, t_map *file, int y,
					short *map_parts_after_nl);

//map_check_walls.c
void			map_check_walls(t_data *data);

//map_check.c
int				map_check(t_data *data, int fd);

//map_colors_utils.c
int				string_rgb_to_int(char **color_rgb, int *color);

//map_colors.c
void			handel_color_codes(t_data *data, t_map *file);

//map_surrounded_by_walls.c
int				surrounded_by_walls(t_data *data, int x, int y);

//map_textures
void			handel_textures(t_data *data, t_map *file);

//map_utils.c
char			*ft_strdup(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
void			free_data_exit(t_data *data, char *msg);
void			free_set_null(char **ptr);
int				is_number(char *color_rgb, int *color);

//convertions.c
double			deg2rad(double degrees);
double			rad2deg(double radians);
int				x_close(t_data *data);

//free_stuff.c
int				free_data(t_data *data);

//raycasting_utils.c
void			save_cor_ver(double *ay, double *ax, t_data *data);
void			save_cor_hor(double *ay, double *ax, t_data *data);
void			render(t_data *data);

//raycasting.c
int				ray_functions(t_data *data);

//raylen.c
void			raylen(t_data *data);
void			where_we_look(t_data *data, int reseting, double angle);
int				hit(t_data *data, char **map, int ay, int ax);
void			raylen_v(t_data *data, double angle, char **map);
void			raylen_h(t_data *data, double angle, char **map);

//opentextures.c
void			load_all_textures(t_data *data);

//utils.c
int				ft_strlen(const char *str);
char			*ft_strj(char const *s1, char const *s2);
int				puterror(char *str);
void			printmap(char **map);
void			free2d(char **map);

//wall_collision.c
int				collision(t_data *data);

//window_loop.c
int				window_loop(t_data *data);
int				rendercub(t_data *data);

//window_draw.c
void			img_pix_put(t_img *img, int x, int y, int color);
void			draw_floor_sky(t_data *data, int sky_color, int ground_color);
void			draw_walls(t_data *data, double distance, t_img *texture);
void			create_img_addr(t_data *data, t_img *img);

#endif
