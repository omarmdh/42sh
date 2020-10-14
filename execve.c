#include "sh.h"

char	**list_to_tab(t_env *env)
{
	int		i;
	char	**tabb;
	char	*new;
	t_env	*head;

	head = env;
	i = 0;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	tabb = (char **)malloc(sizeof(char *) * i + 1);
	tabb[i] = NULL;
	i = 0;
	while (head != NULL)
	{
		new = ft_strjoin(head->name, "=");
		tabb[i++] = ft_strjoin(new, head->environ);
		free(new);
		head = head->next;
	}
	return (tabb);
}

char	*join_path(char *path1, char *path2)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(path1, "/");
	tmp2 = ft_strjoin(tmp, path2);
	free(tmp);
	return (tmp2);
}

char	*search_join(char **path, char *str, char **print)
{
	int			i;
	char		*command;
	struct stat	l;
	DIR			*dir;

	i = 0;
	dir = NULL;
	print[0] = NULL;
	while (path[i])
	{
		command = join_path(path[i], str);
		if (lstat(command, &l) > -1)
			return (command);
		free(command);
		i++;
	}
	if (ft_strchr(str, '/') && (lstat(str, &l) > -1))
		return (help_search_join(str, dir, &print[0]));
	print[0] = ft_strjoin("42sh : command not found: ", str);
	return (NULL);
}

char	*search_env(t_env *list)
{
	t_env	*first;

	first = list;
	while (first)
	{
		if (ft_strcmp(first->name, "PATH") == 0)
			return (first->environ);
		first = first->next;
	}
	return (NULL);
}

void	exec_command(t_job **job, t_process **process)
{
	char	**path;
	char	*command;
	char	*print;

	process[0]->status = STATUS_DONE;
	print = NULL;
	if (search_env(shell->env))
	{
		path = ft_strsplit(search_env(shell->env), ':');
		command = search_join(path, process[0]->argv[0], &print);
		free_2d(path);
		execve_help(&process[0], &job[0], command, print);
		if (command != NULL)
			free(command);
		else
			the_status = 127;
		if (print != NULL)
			free(print);
	}
}
