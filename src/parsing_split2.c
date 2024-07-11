#include "../include/minishell.h"

t_tkns	*my_lstlast(t_tkns *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

void	nodeaddback(t_tkns **lst, t_tkns *new)
{
	t_tkns	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = my_lstlast(*lst);
	last -> next = new;
}

t_tkns	*make_node(t_tkns *matrix, char *s)
{
	t_tkns	*new;
	int		i;

	i = 0;
	new = (t_tkns *)arena_alloc(&g_ex.arena, sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->data = arena_alloc(&g_ex.arena, MAX_INPUT);
	while (s[i] && ft_isspace(s[i]) == false)
	{
		new->data[i] = s[i];
		i++;
	}
	new->next = NULL;
	nodeaddback(&matrix, new);
	return (set_toktype(matrix));
}

t_tkns	*node_redir(t_tkns *matrix, char *s, int size)
{
	t_tkns	*new;
	int		i;

	i = 0;
	new = (t_tkns *)arena_alloc(&g_ex.arena, sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->data = arena_alloc(&g_ex.arena, sizeof(char *));
	while (i < size)
	{
		new->data[i] = s[i];
		i++;
	}
	new->data[i] = '\0';
	new->next = NULL;
	nodeaddback(&matrix, new);
	return (set_toktype(matrix));
}

t_tkns	*init_list(char *s)
{
	t_tkns	*list;

	list = (t_tkns *)arena_alloc(&g_ex.arena, sizeof(*list));
	if (list == NULL)
		return (NULL);
	list->dollar_sign = false;
	list->data = s;
	list->next = NULL;
	return (list);
}
