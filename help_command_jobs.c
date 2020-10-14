#include "sh.h"

int		put_error_fg(int type)
{
	if (type == COMMAND_FG)
		ft_putendl("42sh: fg: too many arguments");
	else if (type == COMMAND_BG)
		ft_putendl("42sh: bg: too many arguments");
	the_status = -1;
	return (-1);
}

int		put_error_no_such(int type)
{
	if (type == COMMAND_FG)
		ft_putendl("42sh: fg: no such job");
	else if (type == COMMAND_BG)
		ft_putendl("42sh: bg: no such job");
	the_status = -1;
	return (-1);
}

int		search_last(void)
{
	int i;

	i = 29;
	while (i > 0)
	{
		if (shell->job[i])
			return (i);
		i--;
	}
	return (0);
}

int		put_error_not_found(int type)
{
	if (type == COMMAND_FG)
		ft_putendl("42sh: fg: job not found");
	else if (type == COMMAND_BG)
		ft_putendl("42sh: bg: job not found");
	the_status = -1;
	return (-1);
}

void	set_job_status(int id, int status)
{
	t_process *process;

	process = shell->job[id]->process;
	while (process)
	{
		if (process->status != STATUS_DONE)
			process->status = status;
		process = process->next;
	}
}
