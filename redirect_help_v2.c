#include "sh.h"

int		print_n_x(char *file, int pipe)
{
	ft_putstr_fd("42sh: ", pipe);
	ft_putstr_fd(file, pipe);
	ft_putendl_fd(": no such file or directory", pipe);
	return (0);
}

int		help_redirect(char *file, char *line)
{
	int		p[2];

	pipe(p);
	while (1)
	{
		line = NULL;
		while (line == NULL || search_no_espace(line) == 0)
		{
			ft_strdel(&line);
			ft_putstr("herdoc> ");
			get_next_line(0, &line);
			if (!line)
			{
				ft_strdel(&line);
				line = ft_strdup(file);
			}
		}
		if (ft_strcmp(line, file) == 0)
			break ;
		ft_putendl_fd(line, p[1]);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(p[1]);
	return (p[0]);
}
