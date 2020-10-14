#include "sh.h"

void	help_back_built(t_job **job, t_process **process)
{
	process[0]->pid = getpid();
	if (job[0]->pgid > 0)
		setpgid(0, job[0]->pgid);
	else
	{
		job[0]->pgid = process[0]->pid;
		setpgid(0, job[0]->pgid);
	}
	trait_built(job[0], process[0]);
	exit(0);
}

void	back_or_fore(t_job **job, t_process **process)
{
	pid_t	pid;

	pid = 0;
	if (job[0]->mode == BACK)
	{
		pid = fork();
		if (pid == 0)
			help_back_built(&job[0], &process[0]);
		else
		{
			process[0]->pid = pid;
			if (job[0]->pgid > 0)
				setpgid(pid, job[0]->pgid);
			else
			{
				job[0]->pgid = pid;
				setpgid(pid, job[0]->pgid);
			}
		}
	}
	else
		trait_built(job[0], process[0]);
}
