#include "sh.h"

int		jump_quote(char *s, int end)
{
	char	c;

	c = s[end];
	if (c == 34 || c == 39)
	{
		end++;
		while (s[end] && s[end] != c)
			end++;
	}
	if (s[end] != '\0')
		end++;
	return (end);
}

int		leno(char *s)
{
	int	start;
	int end;
	int i;

	i = 0;
	end = 0;
	start = 0;
	while (s[start] != '\0')
	{
		while (s[start] != '\0' && (s[start] == ' ' || s[start] == '\t'))
			start++;
		if (s[start] == '\0')
			break ;
		end = start;
		while ((s[end] != ' ' && s[end] != '\0' && s[start] != '\t') ||
			(s[end] == ' ' && s[end - 1] == 92))
			end = jump_quote(s, end);
		start = end;
		i++;
	}
	return (i);
}

char	**ft_strsplito(char *s)
{
	int		start;
	int		end;
	char	**str;
	int		i;

	i = 0;
	start = 0;
	end = 0;
	str = (char **)malloc(sizeof(char *) * (leno(s) + 1));
	while (i < leno(s))
	{
		while (s[start] != '\0' && (s[start] == ' ' || s[start] == '\t'))
			start++;
		end = start;
		while ((s[end] != ' ' && s[end] != '\0' && s[start] != '\t') ||
			(s[end] == ' ' && s[end - 1] == 92))
			end = jump_quote(s, end);
		str[i] = ft_strsub(s, start, (end - start));
		str[i] = move_slash(str[i]);
		str[i] = move_quote(str[i], i);
		start = end;
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**mini_filter_h(char **str, t_env *env)
{
	int			i;
	char		**tabb;
	char		*new;

	i = 0;
	str[0] = replace_with_env(str[0], env, i);
	str[0] = replace_home(str[0], env);
	if (search_no_espace(str[0]) == 0)
		return (NULL);
	new = move_slash(str[0]);
	tabb = ft_strsplito(str[0]);
	return (tabb);
}
