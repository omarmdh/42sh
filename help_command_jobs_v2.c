#include "sh.h"

void	help_to_fg(pid_t pid, int id)
{
	tcsetpgrp(0, pid);
	set_job_status(id, STATUS_CONTINUED);
	if ((the_status = wait_for_job(id, 0)) >= 0)
	{
		print_job_status(id);
		remove_job(id);
	}
	else
		print_job_status(id);
	signal(SIGTTOU, SIG_IGN);
	tcsetpgrp(0, getpid());
	signal(SIGTTOU, SIG_DFL);
}

int		if_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
