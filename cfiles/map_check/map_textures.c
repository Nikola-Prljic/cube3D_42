
#include "../../cub3d.h"

//need to replace with open xpm texture!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! <----
int open_textures(char *line, char *dir)
{
	int fd;
	char *path_texture;

	dir++; //placeholder check for 
	path_texture = ft_substr(line, 3, ft_strlen(line - 3));
	if(!path_texture)
		return(puterror("Error: ft_substr faild"));;
	fd = open(path_texture, O_RDONLY);
	if(path_texture)
		free(path_texture);
	if(fd == -1)
		return(puterror("Error: Can't open texture"));
	close(fd);
	return(0);
}

/* int handel_textures(t_texture *texture, int fd, char *buffer, char **map)
{
	char *line;

	line = ft_getline(fd, buffer, ' ');
	if(ft_strcmp(line, "NO"))
		open_textures(texture->north);
	else if(ft_strcmp(line, "SO"))
		open_textures(texture->south);
	else if(ft_strcmp(line, "WE"))
		open_textures(texture->west);
	else if(ft_strcmp(line, "EA"))
		open_textures(texture->east);
	else
	{
		if(line)
			free(line);
		return (1);
	}
	if(line)
		free(line);
	return (0);
} */