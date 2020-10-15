#include "../includes/ft_autocmp.h"

void		ft_alloc_node(t_dlist **node)
{
	*node = (t_dlist *)malloc(sizeof(t_dlist));
	(*node)->next = NULL;
	(*node)->data = NULL;
}

