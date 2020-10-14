#include "sh.h"

void	help_split_and_and(char *line, char **command, int i, char s)
{
	char	c;
	int		j;
	int		a;

	a = 0;
	j = 0;
	while (line[i])
	{
		c = line[i];
		if (c == 34 || c == 39)
		{
			i++;
			while (line[i] && line[i] != c)
				i++;
		}
		else if (c == s && line[i + 1] == s && line[i + 2] != s)
		{
			command[a++] = ft_strsub(line, j, i - j);
			i++;
			j = i + 1;
		}
		if (line[i] != '\0')
			i++;
	}
	command[a] = ft_strsub(line, j, i - j);
}

int		count_and_and(char *line, char s)
{
	int		i;
	int		count;
	char	c;

	count = 1;
	i = 0;
	while (line[i])
	{
		c = line[i];
		if (c == 34 || c == 39)
		{
			i++;
			while (line[i] != c)
				i++;
		}
		else if (c == s && line[i + 1] == s && line[i + 2] != s)
		{
			count++;
			i++;
		}
		if (line[i] != '\0')
			i++;
	}
	return (count);
}

char	**split_and_and(char *line, char c)
{
	char	**command;
	int		count;

	count = count_and_and(line, c);
	command = (char **)malloc(sizeof(char *) * count + 1);
	command[count] = NULL;
	help_split_and_and(line, command, 0, c);
	return (command);
}
