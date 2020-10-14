#include "sh.h"

void	init_shell(void)
{
	pid_t	pid;
	int		i;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	pid = getpid();
	setpgid(pid, pid);
	tcsetpgrp(0, pid);
	semicolon = NULL;
	the_status = 0;
	the_jobs = NULL;
	or_or = NULL;
	and_and = NULL;
	shell = (t_shell *)malloc(sizeof(t_shell));
	i = 0;
	while (i < NR_J)
		shell->job[i++] = NULL;
	STATUS_STRING = (char **)malloc(sizeof(char *) * 6);
	STATUS_STRING[5] = NULL;
	STATUS_STRING[0] = ft_strdup("running");
	STATUS_STRING[1] = ft_strdup("done");
	STATUS_STRING[2] = ft_strdup("suspended");
	STATUS_STRING[3] = ft_strdup("continued");
	STATUS_STRING[4] = ft_strdup("terminated");
}

void	free_jobs(void)
{
	t_job	*j;
	int		i;

	i = 1;
	while (i < NR_J)
	{
		j = shell->job[i];
		if (j != NULL)
			remove_job(i);
		i++;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*next;
	t_env	*list;

	list = env;
	while (list != NULL)
	{
		free(list->name);
		free(list->environ);
		next = list->next;
		free(list);
		list = next;
	}
}

void	help_to_exit(t_job *job)
{
	free_job(job);
	free_jobs();
	free_env_list(shell->env);
	free_2d(STATUS_STRING);
	free(shell);
	free_2d(semicolon);
	free_2d(and_and);
	free_2d(or_or);
	free_2d(the_jobs);
}
