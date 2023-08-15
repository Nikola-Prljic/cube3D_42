#include "../../cub3d.h"

char	*ft_strdup(const char *s)
{
	char	*tmp;
	int		i;

	i = 0;
	if(!s)
		return(NULL);
	tmp = malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!tmp)
		return (NULL);
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void free_data_exit(t_data *data, char *msg)
{
	free_data(data);
	if(msg)
		puterror(msg);
	exit(1);
}

void floodfill(t_data *data, t_path pos, char fill, char fill_with)
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

int	ft_fillmap(t_data *data, int x, int y)
{
	t_path	pos;
	char	tmp;

	pos.x = x;
	pos.y = y;
	tmp = data->map[y][x];
	data->map[y][x] = '0';
	floodfill(data, pos, '0', 'F');
	floodfill(data, pos, 'F', '0');
	data->map[y][x] = tmp;
	return (0);
}
