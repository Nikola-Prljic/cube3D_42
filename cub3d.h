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

# define WINDOW_HEIGT 512
# define WINDOW_WITH 512
# define PI 3.141592

typedef struct s_ray_cast
{
	int			f_h_x;
	int			f_h_y;
	int			v_x;
	int			v_y;
	int			h_x;
	int			h_y;
	char		view_point;
	int			player_exists;
	float		player_dir;
	float		player_dir_x;
	float		player_dir_y;
	int			plane;
	int			pm_x;
	int			pm_y;
	int			pcor_x;
	int			pcor_y;
	void		*player;
	void		*space;
	void		*wall;
}				t_ray_cast;

typedef struct s_texture
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
}				t_texture;

typedef struct s_xpm_img
{
	char		**img;
	int			width;
	int			height;
}				t_xpm_img;

typedef struct s_data
{
	t_texture	*texture;
	t_xpm_img	*north;
	t_xpm_img	*south;
	t_xpm_img	*west;
	t_xpm_img	*east;
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
}				t_data;

typedef struct s_map
{
	int			fd;
	char		*buffer;
}				t_map;

typedef struct s_path
{
	int x;
	int y;
}				t_path;

//input_handle.c
int				input_handle(int argc, char **argv, int *fd);

//main.c
int				free_data(t_data *data);

//ft_atoi
int				ft_atoi(const char *nptr);

//map_check_utils.c
int				charInStr(char c, char *valid_chars);
int 			isValidchar(t_data *data, char *mapstr, char *valid_chars, int y);
int				free_map_exit(t_data *data, t_map *file, char *msg);
int 			ft_matrix_push_back(t_data *data, t_map *file, char *str);
char 			*saveline(t_data *data, t_map *file, int y, short *map_parts_after_nl);

//map_check_walls.c
void			map_check_walls(t_data *data);

//map_check.c
int				map_check(t_data *data, int fd);

//map_colors.c
void			handel_color_codes( t_data *data, t_map *file );

//map_surrounded_by_walls.c
int				surrounded_by_walls(t_data *data, int x, int y);


//map_textures
void			handel_textures(t_data *data, t_map *file);

//map_utils.c
char			*ft_strdup(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
void 			free_data_exit(t_data *data, char *msg);
void 			free_set_null(char **ptr);

//convertions.c
double			deg2rad(double degrees);
double 			rad2deg(double radians);

//2d_map.c
void			prepare_player(t_data *data);
void			print_2d(t_data *data);

//raycasting.cs
int				ray_functions(t_data *data);

//raylen.c
void			raylen(t_data *data);

//opentextures.c
void load_all_textures(t_data *data);

//utils.c
int				ft_strlen(const char *str);
char			*ft_strj(char const *s1, char const *s2);
int				puterror(char *str);
void			printmap(char **map);
void			free2d(char **map);

//window_loop.c
int				window_loop(t_data *data);

#endif
