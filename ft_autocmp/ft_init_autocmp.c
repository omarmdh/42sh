#include "../includes/ft_autocmp.h"

void		ft_get_path(t_tocmp *cmd)
{
	char *ptr;

	if (cmd->type == 1)
	{
		cmd->path = ft_strdup("./");
		return;
	}
	if (cmd->type == 2)
	{
		ptr = ft_strdup(cmd->tocmp);
		ft_strdel(&cmd->tocmp);
		cmd->tocmp = ft_strdup(ft_strrchr(ptr, '/'));
		ft_strclr(ft_strrchr(ptr, '/'));
		cmd->path = ft_strdup(ptr);
		ft_strdel(&ptr);
	}
}

char		*ft_cutcmd_and_gettype(char *cmd, int index, int *type)
{
	int i;

	if (index > ft_strlen(cmd))
		index = ft_strlen(cmd);
	i = index;
	if (ft_is_whitespace(cmd[i]) && i > 0)
		i--;
	while (i > 0 && !ft_is_whitespace(cmd[i])
	&& cmd[i] != '/' && cmd[i] != '$')
		i--;
	if (ft_is_whitespace(cmd[i]))
		*type = 1;
	if (cmd[i] == '/')
	{
		*type = 2;
		i = index;
		while (!ft_is_whitespace(cmd[i]) && i > 0)
			i--;
		return (ft_strcut(cmd, i + 1, index));
	}
	if (cmd[i] == '$')
		*type = 3;
	if (i == 0)
		*type = 4;
	i > 0 ? i++ : 0;
	return (ft_strcut(cmd, i, index));
}

int init_autocmp(char *cmd, int index)
{
	t_tocmp cmp;
	t_dlist *matchs;

	matchs = NULL;
	cmp.fullcmd = ft_strdup(cmd);
	cmp.tocmp = ft_cutcmd_and_gettype(cmd, index, &cmp.type);
	ft_get_path(&cmp);
	if (cmp.type == 4)
		ft_search_for_bin(cmp, &matchs);
	if (cmp.type == 1 || cmp.type == 2)
		ft_search_in_dirs(cmp, &matchs);
	ft_print_matchs(matchs, 0);
/*	while (matchs)
	{
		ft_putendl(matchs->data);
		matchs = matchs->next;
	}*/
	return (0);
}

int main(int ac, char **av)
{
	init_autocmp(av[1], ft_atoi(av[2]));
	return (0);
}
