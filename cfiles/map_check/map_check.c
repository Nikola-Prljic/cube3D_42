
#include "../../cub3d.h"
#include "ft_getline/ft_getline.h"

int isValidchar(char *mapstr, char *valid_chars)
{
	int i;

	while(*mapstr)
	{
		i = 0;
		while(valid_chars[i])
		{
			if(*mapstr == valid_chars[i])
				break ;
			i++;
			if(valid_chars[i] == 0)
				return (1);
		}
		mapstr++;
	}
	return (0);
}

int map_open(int *fd, char *map_name)
{
	char	*path;

	path = ft_strj( "maps/", map_name );
	*fd = open( path, O_RDONLY );
    if(path)
	    free(path);
	if(*fd == -1)
        return (puterror("Error: map open faild\n"));
	return (0);
} 

int free_map_exit(t_data *data, t_map *file, char *msg)
{
	free_data(data);
	if(file->buffer)
		free(file->buffer);
	if(msg)
		puterror(msg);
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

int map_check( t_data *data, char *map_name )
{
	t_map file;
	char *line;

	file.buffer = NULL;
	if(map_open(&file.fd, map_name))
		return (free_map_exit(data, &file, "Error: map_open faild"));
	data->map = malloc(sizeof(char*) * 2);
	if(!data->map)
		exit(puterror("Error: Malloc faild\n"));
	line = ft_getline(file.fd, &file.buffer, '\n');
	data->map[0] = ft_strdup(line);
	data->map[1] = NULL;
	while(line)
	{
		free(line);
		line = ft_getline(file.fd, &file.buffer, '\n');
		ft_matrix_push_back(data, line);
	}
	printmap(data->map);
	if(file.buffer)
		free(file.buffer);

	/* exit(1); */

	return (0);
}
