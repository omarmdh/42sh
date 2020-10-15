/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_for_bin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:47:17 by ommadhi           #+#    #+#             */
/*   Updated: 2020/10/15 14:03:20 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_autocmp.h"

static char				**ft_get_env_path(void)
{
	char				*path;
	char				**pathtab;

	if (!(path = getenv("PATH")))
		return (NULL);
	if (!(pathtab = ft_strsplit(path, ':')))
		return (NULL);
	return (pathtab);
}

void					ft_search_for_bin(t_tocmp cmp, t_dlist **matchs)
{
	char				**envpaths;
	int					i;
	DIR					*dir;
	struct dirent		*dirdata;
	t_dlist				*head;

	i = -1;
	if (!(envpaths = ft_get_env_path()))
		return ;
	ft_alloc_node(matchs);
	head = *matchs;
	while (envpaths[++i])
	{
		dir = opendir(envpaths[i]);
		while ((dirdata = readdir(dir)))
			if (!ft_strncmp(dirdata->d_name, cmp.tocmp, ft_strlen(cmp.tocmp)))
			{
				head->data = ft_strdup(dirdata->d_name);
				ft_alloc_node(&(head)->next);
				head = head->next;
			}
		closedir(dir);
	}
	ft_memdel((void**)head);
}
