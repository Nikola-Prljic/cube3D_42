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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	if ((unsigned int)ft_strlen(s) < start)
		len = 0;
	else if ((size_t)ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	while (i < len && s[i])
	{
		dest[i] = s[start];
		start++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}