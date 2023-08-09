
#include "cub3d.h"

int	check_input(char *map, int argc)
{
	char	*mapf;
	int		i;

	i = -1;
	if (argc == 2)
	{
		mapf = ft_strj("maps/", map);
		if (check_map_start(mapf) == 0)
		{
			while (mapf[++i])
			{
				if (mapf[i] == '.' && mapf[i + 1] == 'b' && mapf[i + 1] != '\0'
					&& mapf[i + 2] == 'e' && mapf[i + 2] != '\0' && mapf[i
						+ 3] == 'r' && mapf[i + 3] != '\0'
					&& mapf[i + 4] == '\0')
				{
					free(mapf);
					return (0);
				}
			}
			printf("Error\n	%s\n", "Wrong map!");
		}
		free(mapf);
	}
	return (1);
}


int input_handle()
{
    if(check_input())
}

int	main(int argc, char **argv)
{
    if (input_handle ())
        return (0);
	return (0);
}
