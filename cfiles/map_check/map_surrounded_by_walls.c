#include "../../cub3d.h"

void	floodfill(t_data *data, t_path pos, char fill, char fill_with)
{
	if(!data->map[pos.y] || pos.x > ft_strlen(data->map[pos.y]) || data->map[pos.y][pos.x] == 0)
		free_data_exit(data, "Error\nmap not sourundet by 1\n");
	if(data->map[pos.y][pos.x] != fill)
		return ;
	if(pos.y < 1 || pos.x < 1 || charInStr(data->map[pos.y][pos.x], "01F") )
		free_data_exit(data, "Error\nmap not sourundet by 1\n");
	if (pos.y < 0 || pos.x < 0 || data->map[pos.y][pos.x] != fill)
		return ;
	data->map[pos.y][pos.x] = fill_with;
	floodfill(data, (t_path){pos.x + 1, pos.y}, fill, fill_with);
	floodfill(data, (t_path){pos.x - 1, pos.y}, fill, fill_with);
	floodfill(data, (t_path){pos.x, pos.y + 1}, fill, fill_with);
	floodfill(data, (t_path){pos.x, pos.y - 1}, fill, fill_with);
}

int	look_for_zero_save_pos(t_data *data, t_path *pos)
{
	int y;
	int x;

	y = 0;
	while(data->map[y])
	{
		x = 0;
		while(data->map[y][x])
		{
			if(data->map[y][x] == '0')
			{
				pos->y = y;
				pos->x = x;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	surrounded_by_walls(t_data *data, int x, int y)
{
	t_path	pos;
	char	tmp;

	pos.x = x;
	pos.y = y;
	tmp = data->map[y][x];
	data->map[y][x] = '0';
	floodfill(data, pos, '0', 'F');
	while(look_for_zero_save_pos(data, &pos))
		floodfill(data, pos, '0', 'F');
	floodfill(data, pos, 'F', '0');
	data->map[y][x] = tmp;
	return (0);
}
