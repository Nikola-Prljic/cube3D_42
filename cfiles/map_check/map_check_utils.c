
#include "../../cub3d.h"
#include "ft_getline/ft_getline.h"

int	charInStr(char c, char *valid_chars)
{
	int	i;

	i = 0;
	if (!valid_chars || c == 0)
		return (1);
	while (valid_chars[i])
	{
		if (c == valid_chars[i])
			return (0);
		i++;
	}
	return (1);
}

int	isValidchar(t_data *data, char *mapstr, char *valid_chars, int y)
{
	int	x;

	x = 0;
	if (!mapstr)
		return (0);
	while (mapstr[x])
	{
		if (mapstr[x] == 'N' || mapstr[x] == 'E' || mapstr[x] == 'W'
			|| mapstr[x] == 'S')
		{
			if (data->px != -1)
				return (1);
			data->px = x;
			data->py = y;
		}
		if (charInStr(mapstr[x], valid_chars))
			return (1);
		x++;
	}
	if (data->map_x < x)
		data->map_x = x;
	return (0);
}

int	free_map_exit(t_data *data, t_map *file, char *msg)
{
	free_data(data);
	if (file->buffer)
	{
		free(file->buffer);
		file->buffer = NULL;
	}
	if (msg)
		puterror(msg);
	if (file->fd != -1)
	{
		close(file->fd);
		file->fd = -1;
	}
	exit(1);
}

int	ft_matrix_push_back(t_data *data, t_map *file, char *str)
{
	int		i;
	char	**new_matrix;

	i = 0;
	if (!str)
		return (1);
	while (data->map[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i + 2));
	if (!new_matrix)
		return (free_map_exit(data, file,
				"Error\nMalloc failed in ft_matrix_push_back\n"));
	i = 0;
	while (data->map[i])
	{
		new_matrix[i] = ft_strdup(data->map[i]);
		i++;
	}
	new_matrix[i] = ft_strdup(str);
	new_matrix[i + 1] = NULL;
	free2d(data->map);
	data->map = new_matrix;
	return (0);
}

char	*saveline(t_data *data, t_map *file, int y, short *map_parts_after_nl)
{
	char	*line;

	line = NULL;
	line = ft_getline(data, file->fd, &file->buffer, '\n');
	if(line && line[0] == 0)
	{
		*map_parts_after_nl = 1;
		return (line);
	}
	if (line && (isValidchar(data, line, " 01NEWS", y) == 1))
	{
		free(line);
		free_map_exit(data, file, "Error\nWrong char in a map\n");
	}
	if (line && *map_parts_after_nl)
	{
		free(line);
		free_map_exit(data, file, "Error\nMap seperated by a new line\n");
	}
	ft_matrix_push_back(data, file, line);
	return (line);
}
