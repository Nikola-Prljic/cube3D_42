
#include "../cub3d.h"

int map_check( char ***map, char *map_name )
{
	int fd;
	char *mapstr;

	mapstr = NULL;
	if(map_open( map_name, &fd ) || map_read( fd, &mapstr ))
		return (1);
	*map = ft_split(mapstr, '\n');
	free(mapstr);
	if(!map)
		return(puterror("Error: ft_split faild."));
	return (0);
}
