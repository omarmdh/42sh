#include "sh.h"

void	free_2d(char **str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

void	free_job(t_job *job)
{
	t_process	*process;
	t_process	*tmp;

	process = job->process;
	while (process)
	{
		tmp = process->next;
		free(process->command);
		free_2d(process->argv);
		free(process);
		process = tmp;
	}
	free(job->command);
	free(job);
}

void	help_trait(t_job **j, t_process **process, int *count)
{
	count[0]++;
	exec_command(&j[0], &process[0]);
}

char	*concate(char *path, char *str)
{
	char	*new;
	char	*ptr;

	new = ft_strjoin(path, "/");
	ptr = new;
	new = ft_strjoin(new, str);
	free(ptr);
	return (new);
}

int		h_f_f(char *file2, t_process *process, int ifnot)
{
	if (atoi(file2) == 0)
		return (process->input);
	else if (atoi(file2) == 1)
		return (process->output);
	else if (atoi(file2) == 2)
		return (process->errorput);
	else
		return (ifnot);
}
