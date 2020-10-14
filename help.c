#include "sh.h"

int		get_command_type(char *command)
{
	if (ft_strcmp(command, "exit") == 0)
		return (COMMAND_EXIT);
	else if (ft_strcmp(command, "cd") == 0)
		return (COMMAND_CD);
	else if (ft_strcmp(command, "jobs") == 0)
		return (COMMAND_JOBS);
	else if (ft_strcmp(command, "fg") == 0)
		return (COMMAND_FG);
	else if (ft_strcmp(command, "bg") == 0)
		return (COMMAND_BG);
	else if (ft_strcmp(command, "export") == 0)
		return (COMMAND_EXPORT);
	else if (ft_strcmp(command, "unset") == 0)
		return (COMMAND_UNSET);
	else if (ft_strcmp(command, "set") == 0)
		return (COMMAND_SET);
	else if (ft_strcmp(command, "echo") == 0)
		return (COMMAND_ECHO);
	else if (ft_strcmp(command, "type") == 0)
		return (COMMAND_TYPE);
	else if (ft_strcmp(command, "env") == 0)
		return (COMMAND_ENV);
	else
		return (COMMAND_EXTERNAL);
}

int		to_exit(t_process *process, t_job *j)
{
	int		i;

	i = 0;
	while (process->argv[i])
		i++;
	if (i == 1 && j->mode == FORE)
	{
		help_to_exit(j);
		exit(0);
	}
	else if (i != 1)
		ft_putendl_fd("exit: too many arguments", process->errorput);
	the_status = -1;
	return (-1);
}

int		trait_built(t_job *j, t_process *process)
{
	if (process->type == COMMAND_EXIT)
		to_exit(process, j);
	else if (process->type == COMMAND_JOBS)
		to_jobs(j);
	else if (process->type == COMMAND_FG)
		to_fg(process, j);
	else if (process->type == COMMAND_BG)
		to_bg(process, j);
	else if (process->type == COMMAND_ENV)
		to_env(process);
	else if (process->type == COMMAND_TYPE)
		to_type(process);
	else if (process->type == COMMAND_ECHO)
		to_echo(process);
	else if (process->type == COMMAND_SET)
		to_set(process);
	else if (process->type == COMMAND_UNSET)
		to_unset(process, j);
	else if (process->type == COMMAND_EXPORT)
		to_export(process, j, process->argv);
	else if (process->type == COMMAND_CD)
		to_cd(process, j);
	return (0);
}

int		count_replace_env(char *line, int i, char c)
{
	i++;
	while (line[i] && line[i] != c)
		i++;
	return (i);
}

void	mini_mini_norme(char **line, char *str, int a, int i)
{
	if (str != NULL)
		join_with_something(&line[0], str, a, i);
	else
		join_with_anything2(&line[0], str, a, i);
}
