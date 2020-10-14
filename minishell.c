#include "sh.h"

int		search_no_espace(char *str)
{
	int i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int		help_main(int argc, char **argv, char **env)
{
	t_env	*list;

	argc = 0;
	argv = NULL;
	if (!env[0])
	{
		ft_putstr(" ⛔️ \x1b[31m \x1b[1m We need The Linux ");
		ft_putendl("Environment to run this programme ! \033[0m");
		return (0);
	}
	list = create_env(env);
	init_shell();
	shell->env = list;
	return (1);
}

int		main(int argc, char **argv, char **env)
{
	char	*line;
	t_his *his;

	if (help_main(argc, argv, env) == 0)
		return (0);
	line = NULL;
	his = NULL;
	while (1)
	{
		line = my_readline(&his, "(42 shell)$> ");
		if (line)
			ft_add_his(&his, line);
		check_zombie();
		if (line && (search_no_espace(line) == 0 ||
			check_if_and_and(&line, 0) == 0))
		{
			free(line);
			continue;
		}
		if (!line || ft_strlen(line) == 0)
			free(line);
		else
			semicolon_parse(line);
	}
	ft_free_his(&his);
	return (0);
}
