/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandrinedube <alexandrinedube@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:35:22 by adube             #+#    #+#             */
/*   Updated: 2024/07/29 14:39:25 by alexandrine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_tkns	*make_node(t_tkns *matrix, char *s, t_parsing *parse_list)
{
	t_tkns	*new;
	int		i;
	int		y;

	i = 0;
	y = 0;
	new = (t_tkns *)arena_alloc(&g_ex.arena, sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->data = arena_alloc(&g_ex.arena, MAX_INPUT);
	while (s[i] && check_cmd_quotes(s, parse_list, i) == true)
	{
		if ((parse_list->quote_type == 39 && s[i] == 39)
			|| (parse_list->quote_type == 34 && s[i] == 34))
		{
			parse_list->quote_count++;
			i++;
			continue ;
		}
		new->data[y++] = s[i++];
	}
	new->next = NULL;
	nodeaddback(&matrix, new);
	return (set_toktype(matrix, parse_list));
}

t_tkns	*node_redir(t_tkns *matrix, char *s, int size, t_parsing *parse_list)
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
	return (set_toktype(matrix, parse_list));
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
