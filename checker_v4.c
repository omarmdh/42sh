#include "sh.h"

int		help_check_curch(char *str, int *count)
{
	int i;

	i = count[0];
	i++;
	while (str[i] && str[i] != '}')
	{
		if (str[i] == '{')
			break ;
		i++;
	}
	if (str[i] != '}')
	{
		ft_putendl_fd("42sh: bad substitution", 2);
		return (0);
	}
	count[0] = i;
	return (1);
}

int		error_check_cursh(void)
{
	ft_putendl_fd("42sh: parse error near `}'", 2);
	return (0);
}

int		check_cursh(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		c = str[i];
		if (c == 34 || c == 39)
		{
			i++;
			while (str[i] && str[i] != c)
				i++;
		}
		else if (str[i] == '}')
			return (error_check_cursh());
		else if (str[i] == '{')
		{
			if (help_check_curch(str, &i) == 0)
				return (0);
		}
		if (str[i] != '\0')
			i++;
	}
	return (1);
}

int		help_check_if_and_and(char **str, int i)
{
	char	*new;

	if (str[0][i] != ' ' && str[0][i] != '\t' && str[0][i] != '\n'
		&& str[0][i] != '&' && str[0][i] != '|')
		return (1);
	else if (str[0][i] == '|' ||
		(str[0][i] == '&' && str[0][i + 1] == '&'))
	{
		help_to_finish_the_pipe(&str[0]);
		return (-1);
	}
	new = ft_strdup(str[0]);
	str[0] = ft_filter_quote(0, str[0]);
	if (ft_strcmp(new, str[0]) != 0)
	{
		free(new);
		return (-1);
	}
	free(new);
	return (0);
}
