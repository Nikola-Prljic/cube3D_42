
#ifndef CUB3D_H
# define CUB3D_H

# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//input_handle.c
int		input_handle(int argc, char **argv);

//main.c

//mapcheck.c

//utils.c
int		ft_strlen(const char *str);
char	*ft_strj(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);

#endif