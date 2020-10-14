#include "sh.h"

char	*check_env(char *str, t_env *env)
{
	if (ft_strcmp(str, "?") == 0)
		return (ft_itoa(the_status));
	while (env)
	{
		if (ft_strcmp(str, env->name) == 0)
			return (ft_strdup(env->environ));
		else
			env = env->next;
	}
	return (NULL);
}

char	*help_replace_env(int *a, char *line, int i, t_env *env)
{
	char	*new;
	char	*str;

	if (line[*a] == '{')
	{
		while (line[*a] != '}')
			(*a)++;
		new = ft_strsub(line, i + 2, *a - (i + 2));
		(*a)++;
	}
	else
	{
		while (line[*a] == '_' || (line[*a] >= 'a' && line[*a] <= 'z') ||
			(line[*a] >= 'A' && line[*a] <= 'Z') ||
			(line[*a] >= '0' && line[*a] <= '9'))
			(*a)++;
		new = ft_strsub(line, i + 1, *a - (i + 1));
	}
	if (new[0] == '\0')
		str = ft_strsub(line, i, *a - i);
	else
		str = check_env(new, env);
	free(new);
	return (str);
}

void	join_with_something(char **line, char *str, int a, int i)
{
	char	*first;
	char	*new;

	first = ft_strsub(*line, 0, i);
	new = ft_strjoin(first, str);
	free(first);
	free(str);
	str = ft_strdup(&line[0][a]);
	free(*line);
	line[0] = ft_strjoin(new, str);
	free(new);
	free(str);
}

void	join_with_anything2(char **line, char *str, int a, int i)
{
	char	*first;

	first = ft_strsub(*line, 0, i);
	str = ft_strdup(&line[0][a]);
	free(*line);
	line[0] = ft_strjoin(first, str);
	free(first);
	free(str);
}

char	*replace_with_env(char *line, t_env *env, int b)
{
	int		i;
	char	*str;
	int		a;
	char	c;

	i = 0;
	b = 0;
	while (line[i])
	{
		c = line[i];
		if (c == 34 || c == 39)
			i = count_replace_env(line, i, c);
		else if (line[i] == '$')
		{
			a = i + 1;
			str = help_replace_env(&a, line, i, env);
			if (str != NULL)
				b = ft_strlen(str);
			mini_mini_norme(&line, str, a, i);
			i = i + b;
		}
		else if (line[0] != '\0')
			i++;
	}
	return (line);
}
