/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:00:58 by nprljic           #+#    #+#             */
/*   Updated: 2023/08/14 13:55:42 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getline.h"

// #1 creates a new malloc string just for the first time
char	*ft_new_str(int fd, char *remain, char delimiter)
{
	int		ret;
	char	*buf;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	ret = 1;
	while (!ft_strchr(remain, delimiter) && !ft_strchr(remain, '\n') && ret != 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free(remain);
			free(buf);
			return (NULL);
		}
		buf[ret] = '\0';
		remain = ft_linejoin(remain, buf);
	}
	free(buf);
	return (remain);
}

// #2 prints the line
char	*ft_putline(char *remain, char delimiter)
{
	char	*line;
	int		i;

	if (!*remain)
		return (NULL);
	i = 0;
	while (remain[i] && remain[i] != delimiter && remain[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (remain[i] && remain[i] != delimiter && remain[i] != '\n')
	{
		line[i] = remain[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

// #3 malloc a new without the printed string. frees the old one.
char	*ft_next_str(char *remain, char delimiter)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	while (remain[i] && remain[i] != delimiter && remain[i] != '\n')
		i++;
	if (!remain[i])
	{
		free(remain);
		return (NULL);
	}
	str = (char *)malloc((int_strlen(remain) - i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i++;
	x = 0;
	while (remain[i])
		str[x++] = remain[i++];
	str[x] = '\0';
	free(remain);
	return (str);
}

//buffer is for freeing if something remains
char	*ft_getline(int fd, char **remain, char delimiter)
{
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	*remain = ft_new_str(fd, *remain, delimiter);
	if (!remain)
		return (NULL);
	line = ft_putline(*remain, delimiter);
	*remain = ft_next_str(*remain, delimiter);
	return (line);
}

/* int main()
{
    int fd;
    int x = 0;
    char *str;
	char *buffer = NULL;

    fd = open("test.txt", O_RDONLY);
    while(x++ < 2)
	{
        printf("line %i = %s\n", x, str = ft_getline(fd, &buffer, 't'));
		free(str);
		printf("line %i = %s", x, str = get_next_line(fd, &buffer, 'c'));
		free(str);
	}
    printf("buffer = %s", buffer);
	if(buffer)
		free(buffer);
    close(fd);
    return(0);
} */