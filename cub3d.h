#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WINDOW_WITH 1000
# define WINDOW_HEIGT 800
# define TILE_SIZE 64
# define PI 3.141593
# define STOP_RENDER 1
# define START_RENDER 0
# define MAP_SIZE 0.2

typedef struct s_ray_cast
{
	int			up_down;
	int			left_right;
	float			v_x;
	float			v_y;
	float			h_x;
	float			h_y;
	char		view_point;
	float		player_dir;
	float		player_dir_x;
	float		player_dir_y;
	int			plane;
	float		px;
	float		py;
	void		*player;
	void		*space;
	void		*spacev;
	void		*wall;
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
    int			bpp; /* bits per pixel */
    int			line_len;
    int			endian;
}				t_img;

/* typedef struct s_mlx_img
{
	void	*mlx_img;
    char	*addr;
    int		bpp; bits per pixel
    int		line_len;
    int		endian;
}				t_mlx_img; */

typedef struct s_data
{
	t_texture	*texture;
	t_img		*img;
	t_img		*north;
	t_img		*south;
	t_img		*west;
	t_img		*east;
	int 		distance;
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
	int 		raycount;

	//////
	int 		zoom_faktor;
	////////
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
	int start_y;
	int start_x;
	int size_y; 
	int size_x;
	int color;
}				t_rect;

//input_handle.c
int				input_handle(int argc, char **argv, int *fd);

//main.c
int				free_data(t_data *data);

//ft_atoi
int				ft_atoi(const char *nptr);

//map_check_utils.c
int				charInStr(char c, char *valid_chars);
int				isValidchar(t_data *data, char *mapstr, char *valid_chars,
					int y);
int				free_map_exit(t_data *data, t_map *file, char *msg);
int				ft_matrix_push_back(t_data *data, t_map *file, char *str);
char			*saveline(t_data *data, t_map *file, int y,
					short *map_parts_after_nl);

//map_check_walls.c
void			map_check_walls(t_data *data);

//map_check.c
int				map_check(t_data *data, int fd);

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

//convertions.c
double			deg2rad(double degrees);
double			rad2deg(double radians);

//2d_map.c
void			prepare_player(t_data *data);
void			print_2d(t_data *data);

//raycasting_utils.c
void			save_cor_ver(float *ay, float *ax, t_data *data);
void			save_cor_hor(float *ay, float *ax, t_data *data);
void			render(t_data *data);

//raycasting.c
int				ray_functions(t_data *data);

//raylen.c
void			raylen(t_data *data);

//opentextures.c
void			load_all_textures(t_data *data);

//utils.c
int				ft_strlen(const char *str);
char			*ft_strj(char const *s1, char const *s2);
int				puterror(char *str);
void			printmap(char **map);
void			free2d(char **map);

//window_loop.c
int				window_loop(t_data *data);

//window_draw.c
void	img_pix_put(t_img *img, int x, int y, int color);
void	draw_floor_sky(t_data *data, int sky_color, int ground_color);
void	draw_walls(t_data *data, double distance, int ray_x, t_img *texture);
void 	create_img_addr(t_data *data, t_img *img);
void 	draw_minimap(t_data *data);

#endif
