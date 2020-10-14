#include "sh.h"

int		print_error_num(char *file, int error)
{
	ft_putstr_fd("42sh: syntax error near unexpected token `",
		error);
	ft_putstr_fd(file, error);
	ft_putendl_fd("'", error);
	the_status = -1;
	return (0);
}

int		help_type_one(char *file, int error)
{
	struct stat	l;

	close(open(file, O_CREAT, 0644));
	lstat(file, &l);
	if (S_ISDIR(l.st_mode))
		return (print_i_d(file, error));
	return (1);
}

int		print_p_d(char *file, int pipe)
{
	ft_putstr_fd("42sh: ", pipe);
	ft_putstr_fd(file, pipe);
	ft_putendl_fd(": Permission denied", pipe);
	return (0);
}

int		print_i_d(char *file, int pipe)
{
	ft_putstr_fd("42sh: ", pipe);
	ft_putstr_fd(file, pipe);
	ft_putendl_fd(": Is a directory", pipe);
	return (0);
}

int		error_type_three(char *file, int error)
{
	struct stat l;

	if (lstat(file, &l) == -1)
		return (print_n_x(file, error));
	if (S_ISDIR(l.st_mode))
		return (print_i_d(file, error));
	return (1);
}
