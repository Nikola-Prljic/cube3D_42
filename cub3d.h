
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

# define WINDOW_HEIGT 400
# define WINDOW_WITH 400
# define PI 3.1415926535

typedef struct s_ray_cast
{
	char		view_point;
	int			player_exists;
	float		player_dir;
	float		player_dir_x;
	float		player_dir_y;
	float		player_x;
	float		player_y;
}				t_ray_cast;

typedef struct s_data
{
	char		**map;
	void		*mlx_ptr;
	void		*win_ptr;
	t_ray_cast	*rays;
}				t_data;

//ft_split.c
char			**ft_split(char const *s, char c);

//ft_substr.c
char			*ft_substr(char const *s, unsigned int start, size_t len);

//input_handle.c
int				input_handle(int argc, char **argv);

//main.c

//map_check.c
int				map_check(char ***map, char *map_name);

//map_open.c
int				map_open(char *map_name, int *fd);
int				map_read(int fd, char **mapstr);

//map_open_utils.c
char			*ft_linejoin(char *s1, char *s2);

//raycasting.c
int				ray_functions(t_data *data);

//utils.c
int				ft_strlen(const char *str);
char			*ft_strj(char const *s1, char const *s2);
void			ft_putstr_fd(char *s, int fd);
int				puterror(char *str);
void			printmap(char **map);
void			free2d(char **map);

//window_loop.c
int				window_loop(t_data *data);

#endif
