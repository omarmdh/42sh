#include "sh.h"

void	help_to_wait(t_job *j, int *status)
{
	tcsetpgrp(0, j->pgid);
	status[0] = wait_for_job(j->id, 0);
	signal(SIGTTOU, SIG_IGN);
	tcsetpgrp(0, getpid());
	signal(SIGTTOU, SIG_DFL);
}

void	final_help(t_process **process, t_job **j, int *count)
{
	t_env	*save;

	process[0]->argv = manage_variables(process[0]->argv, &save);
	if (process[0]->argv)
	{
		process[0]->type = get_command_type(process[0]->argv[0]);
		if (process[0]->type == COMMAND_EXTERNAL)
			help_trait(&j[0], &process[0], &count[0]);
		else
			back_or_fore(&j[0], &process[0]);
	}
	manage_variables2(save);
}
