#include "sh.h"

void	make_the_put(t_process **process, t_job **j)
{
	int pi[2];

	process[0]->input = j[0]->p;
	if (process[0]->next)
	{
		pipe(pi);
		process[0]->output = pi[1];
		j[0]->p = pi[0];
	}
	else
	{
		process[0]->output = 1;
		j[0]->p = 0;
	}
	j[0]->p_input = process[0]->input;
	j[0]->p_output = process[0]->output;
}

void	close_pipe(t_process *process, t_job *job)
{
	if (job->p_input != 0 && job->p_input != -1)
		close(job->p_input);
	if (job->p_output != 1 && job->p_output != -1)
		close(job->p_output);
	if (process->errorput != 2 && process->errorput != -1)
		close(process->errorput);
}

void	pipe_execve(t_process *process, t_job *job)
{
	if (job->p != 0)
		close(job->p);
	if (process->output == -1)
		close(1);
	else
		dup2(process->output, 1);
	if (process->input == -1)
		close(0);
	else
		dup2(process->input, 0);
	if (process->errorput == -1)
		close(2);
	else
		dup2(process->errorput, 2);
}
