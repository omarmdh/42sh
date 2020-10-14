#include "sh.h"

int		print_and_of_number(char s, int count)
{
	if (s == '<' || s == '>')
		return (print_fu_redirect_error());
	ft_putstr_fd("42sh: syntax error near unexpected token `", 2);
	if (count == 1)
		ft_putchar_fd(s, 2);
	if (count > 1)
	{
		ft_putchar_fd(s, 2);
		ft_putchar_fd(s, 2);
	}
	ft_putendl_fd("'", 2);
	return (0);
}

int		some_norme_again(char *str, int j, char c, int count)
{
	if (c == 34 || c == 39)
		return (1);
	if ((str[j] == '\0' || search_no_espace(&str[j]) == 0) &&
		(str[j - 1] == '<' || str[j - 1] == '>' ||
		(str[j - 1] == '&' && (str[j - 2] == '>' || str[j - 2] == '<'))))
		return (print_and_of_number(c, count));
	return (1);
}

int		check_count_and(char *str, int count)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		c = str[i];
		if (c == 34 || c == 39)
		{
			i++;
			while (str[i] && str[i] != c)
				i++;
		}
		else if (str[i] == '|' || str[i] == '&' || str[i] == '|'
				|| str[i] == '>' || str[i] == '<' || str[i] == ';')
		{
			if (some_name(&i, &j, str, c) == 0)
				return (0);
		}
		if (str[i] != '\0')
			i++;
	}
	return (some_norme_again(str, j, c, count));
}

int		check_if_and_and(char **str, int i)
{
	while (1)
	{
		i = 0;
		if (!str[0] || check_count_and(str[0], 0) == 0 ||
			check_cursh(str[0]) == 0)
			return (0);
		str[0] = ft_filter_quote(0, str[0]);
		while (str[0][i])
			i++;
		i--;
		if (i == 0 && str[0][i] != 34 && str[0][i] != 39)
			break ;
		while (i != 0 || (i == 0 && (str[0][i] == 34 || str[0][i] == 39)))
		{
			if (help_check_if_and_and(&str[0], i) == 1)
				return (1);
			else if (help_check_if_and_and(&str[0], i) == -1)
				break ;
			i--;
		}
	}
	return (1);
}
