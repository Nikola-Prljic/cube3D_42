#include "../../cub3d.h"

void	floodwalls(t_data *data, t_path pos, char *fill, char fill_with)
{
	if (pos.y < 0 || pos.x < 0 || !data->map_copy[pos.y] || pos.x > ft_strlen(data->map_copy[pos.y]) || data->map_copy[pos.y][pos.x] == 0 || (data->map_copy[pos.y][pos.x] != fill[0] && data->map_copy[pos.y][pos.x] != fill[1]))
		return ;
	data->map_copy[pos.y][pos.x] = fill_with;

	floodwalls(data, (t_path){pos.x, pos.y + 1}, fill, fill_with);
	floodwalls(data, (t_path){pos.x, pos.y - 1}, fill, fill_with);
	floodwalls(data, (t_path){pos.x + 1, pos.y}, fill, fill_with);
	floodwalls(data, (t_path){pos.x - 1, pos.y}, fill, fill_with);
}

int	is_all_w(t_data *data)
{
	int y;
	int x;

	y = 0;
	while(data->map_copy[y])
	{
		x = 0;
		while(data->map_copy[y][x])
		{
			if(data->map_copy[y][x] != 'W' && data->map_copy[y][x] != ' ')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

void map_check_walls(t_data *data)
{
	t_path	pos;
	char fill[2];

	fill[0] = '1';
	fill[1] = 'F';
	pos.x = 0;
	pos.y = 0;
	floodwalls(data, pos, fill, 'W');
	if(is_all_w(data))
		free_data_exit(data, "Error\nmaps not connected\n");
	return ;
}
