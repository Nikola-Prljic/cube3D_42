
#include "../../cub3d.h"
#include "ft_getline/ft_getline.h"

int isValidchar(char *mapstr, char *valid_chars)
{
	int i;
	int x;

	x = 0;
	if(!mapstr)
		return(0);
	while(mapstr[x])
	{
		i = 0;
		while(valid_chars[i])
		{
			if(mapstr[x] == valid_chars[i])
				break ;
			i++;
			if(valid_chars[i] == 0)
				return (1);
		}
		x++;
	}
	return (0);
}

/* int map_open(int *fd, char *map_name)
{
	char	*path;

	path = ft_strj( "maps/", map_name );
	*fd = open( path, O_RDONLY );
    if(path)
	    free(path);
	if(*fd == -1)
        return (puterror("Error: map open faild\n"));
	return (0);
}  */

int free_map_exit(t_data *data, t_map *file, char *msg)
{
	free_data(data);
	if(file->buffer)
	{
		file->buffer = NULL;
		free(file->buffer);
	}
	if(msg)
		puterror(msg);
	if(file->fd != -1)
	{
		file->fd = -1;
		close(file->fd);
	}
	exit(1);
}

int ft_matrix_push_back(t_data *data, char *str)
{
	int i;
	char **new_matrix;

	i = 0;
	if(!str)
		return (1);
	while(data->map[i])
		i++;
	new_matrix = malloc(sizeof(char*) * (i + 2));
	if(!new_matrix)
		return (1);
	i = 0;
	while(data->map[i])
	{
		new_matrix[i] = ft_strdup(data->map[i]);
		i++;
	}
	new_matrix[i] = ft_strdup(str);
	new_matrix[i + 1] = NULL;
	i = 0;
	while(data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = new_matrix;
	return 0;
}

void malloc_data_map_first_line(t_data *data, t_map *file)
{
	data->map = malloc(sizeof(char*) * 2);
	if(!data->map)
		free_map_exit(data, file, "Error: map_open faild");
	data->map[0] = NULL;
}

char *saveline(t_data *data, t_map *file)
{
	char *line;

	line = NULL;
	line = ft_getline(file->fd, &file->buffer, '\n');
	if(isValidchar(line, " 01NEWS") == 1)
	{
		free(line);
		free_map_exit(data, file, "Error: wrong char in map\n");
	}
	ft_matrix_push_back(data, line);
	return (line);
}

int map_check(t_data *data, int fd)
{
	char	*line;
	t_map	file;

	line = NULL;
	file.fd = fd;
	file.buffer = NULL;
	handel_textures(data, &file);
	malloc_data_map_first_line(data, &file);
	line = saveline(data, &file);
	while(line)
	{
		free(line);
		line = saveline(data, &file);
	}
	printmap(data->map);
	if(file.buffer)
		free(file.buffer);
	if(fd != -1)
		close(file.fd);
	return (0);
}
