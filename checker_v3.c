#include "sh.h"

void	help_to_finish_the_pipe(char **line)
{
	char	*new;
	char	*str;
	int		i;

	i = 0;
	new = NULL;
	while (!i || search_no_espace(new) == 0)
	{
		i++;
		ft_strdel(&new);
		ft_putstr("> ");
		get_next_line(0, &new);
	}
	if (!new && i)
		ft_strdel(&line[0]);
	str = line[0];
	line[0] = ft_strjoin(line[0], new);
	free(new);
	free(str);
}

int		ft_filter_2eme(int len, char *cont, int index)
{
	len++;
	while (cont[len])
	{
		if (cont[len] == index)
			return (len);
		len++;
	}
	return (0);
}

char	*read_quote(char *cont, int index)
{
	char	*lire;
	char	*tmp;
	char	*tmp2;

	lire = NULL;
	if (index == 39)
	{
		ft_putstr("quote>");
		get_next_line(0, &lire);
	}
	else
	{
		ft_putstr("dquote>");
		get_next_line(0, &lire);
	}
	if (!lire)
	{
		ft_strdel(&cont);
		return (NULL);
	}
	tmp = ft_strjoin(cont, "\n");
	tmp2 = ft_strjoin(tmp, lire);
	free(cont);
	ft_strdel(&tmp);
	ft_strdel(&lire);
	return (tmp2);
}

char	*ft_filter_quote(int i, char *cont)
{
	int		resul;
	int		c;
	int		len;

	c = 0;
	len = 0;
	resul = 0;
	i = 0;
	while (cont[len])
	{
		if (cont[len] == 34 || cont[len] == 39)
		{
			c = ((int)cont[len]);
			if ((resul = ft_filter_2eme(len, cont, c)) == 0)
				cont = read_quote(cont, c);
			if (!cont)
				return (NULL);
			len = -1;
			if (resul != 0)
				len = resul;
		}
		len++;
	}
	return (cont);
}
