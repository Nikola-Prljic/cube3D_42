
#include "../cub3d.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (*s)
	{
		if (*s != c && x == 0)
		{
			x = 1;
			i++;
		}
		else if (*s == c)
			x = 0;
		s++;
	}
	return (i);
}

static int	len_just_str(const char *s, int start, char c)
{
	int	i;

	i = 0;
	while (s[start] != c && start < (int)ft_strlen(s))
	{
		start++;
		i++;
	}
	return (i);
}

static char	**head(char **s2d, char const *s, char c)
{
	size_t	i;
	size_t	x;
	int		len;

	i = 0;
	x = 0;
	len = 0;
	while (i <= (size_t)ft_strlen(s))
	{
		if (s[i] != c && i != (size_t)ft_strlen(s))
		{
			len = len_just_str(s, i, c);
			s2d[x] = ft_substr(s, i, len);
			i += len;
			x++;
		}
		i++;
	}
	s2d[x] = 0;
	return (s2d);
}

char	**ft_split(char const *s, char c)
{
	char	**s2d;

	if (!s)
		return (0);
	s2d = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s2d)
		return (0);
	return (head(s2d, s, c));
}
