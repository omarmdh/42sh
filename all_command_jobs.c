#include "sh.h"

int		to_jobs(t_job *j)
{
	int		i;

	i = 1;
	while (i < NR_J)
	{
		if (shell->job[i] != NULL)
			print_job_status(i);
		i++;
	}
	if (j->mode == FORE)
		the_status = 0;
	return (0);
}

int		check_bug_fg_bg(t_process *process, int type)
{
	int id;
	int i;

	i = 0;
	while (process->argv[i])
		i++;
	if (i > 2)
		return (put_error_fg(type));
	if ((i == 1 && search_last() == 0) ||
		(i != 1 && (if_numeric(process->argv[1]) == 0 ||
		(id = atoi(process->argv[1])) > 29 ||
		shell->job[id] == NULL)))
		return (put_error_no_such(type));
	if (i == 1)
		id = search_last();
	return (id);
}

int		to_fg(t_process *process, t_job *j)
{
	pid_t	pid;
	int		id;

	if (j->mode == FORE)
	{
		if ((id = check_bug_fg_bg(process, COMMAND_FG)) == -1)
			return (-1);
		pid = shell->job[id]->pgid;
		if (kill(-pid, SIGCONT) < 0)
			return (put_error_not_found(COMMAND_FG));
		help_to_fg(pid, id);
		the_status = 0;
	}
	else if (j->mode == BACK)
	{
		ft_putendl_fd("42sh: fg: no job control", process->errorput);
		the_status = -1;
	}
	return (0);
}

int		to_bg(t_process *process, t_job *j)
{
	pid_t	pid;
	int		id;

	if (j->mode == FORE)
	{
		if ((id = check_bug_fg_bg(process, COMMAND_BG)) == -1)
			return (-1);
		pid = shell->job[id]->pgid;
		if (kill(-pid, SIGCONT) < 0)
			return (put_error_not_found(COMMAND_BG));
		set_job_status(id, STATUS_CONTINUED);
		print_job_status(id);
		the_status = 0;
	}
	else if (j->mode == BACK)
	{
		ft_putendl_fd("42sh: bg: no job control", process->errorput);
		the_status = -1;
	}
	return (-1);
}
