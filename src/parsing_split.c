#include "../include/minishell.h"

t_tkns *set_toktype(t_tkns *matrix)
{
	while (matrix -> next)
		matrix = matrix -> next;
	if (matrix->data[0] == '<' && matrix->data[1]  == '<')
		matrix->tok_type = TRUNC;
	else if (matrix->data[0] == '<' && matrix->data[1]  == '>')
		matrix->tok_type = IN_OUT; 
	else if (matrix->data[0] == '<')
		matrix->tok_type = INPUT;
	else if (matrix->data[0] == '>' && matrix->data[1]  == '>')
		matrix->tok_type = APPEND;
	else if (matrix->data[0] == '>' && matrix->data[1]  == '|')
		matrix->tok_type = SPECIAL_PIPE; 
	else if (matrix->data[0] == '>')
		matrix->tok_type = OUTPUT;
	else if (matrix->data[0] == '|')
		matrix->tok_type = PIPE;
	else
		matrix->tok_type = CMD;
	return (matrix);
}

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

t_tkns *make_node(t_tkns *matrix, char *s)
{
	t_tkns	*new;
	int		i;

	i = 0;
	new = (t_tkns *)malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->data = ft_calloc(MAX_INPUT, sizeof(char));
	while (s[i] && ft_isspace(s[i]) == false)
	{
		new->data[i] = s[i];
		i++;
	}
	new->next = NULL;
	nodeaddback(&matrix, new);
	return(set_toktype(matrix));
}

t_tkns *node_redir(t_tkns *matrix, char *s, int size)
{
	t_tkns	*new;
	int		i;

	i = 0;
	new = (t_tkns *)malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->data = malloc(sizeof(char *));
	while (i < size)
	{
		new->data[i] = s[i];
		i++;
	}
	new->data[i] = '\0';
	new->next = NULL;
	nodeaddback(&matrix, new);
	return(set_toktype(matrix));
}

t_tkns *init_list(char *s)
{
	t_tkns *list;

	list = (t_tkns *)malloc(sizeof(*list));
	if (list == NULL)
		return (NULL);
	list->dollar_sign = false;
//	list->argv_pos = 0;
	list->data = s;
	list->next = NULL;
	return (list);
}

t_parsing *new_split(char *s, t_parsing *parse_list) 
{
	parse_list->index = 0;
	parse_list->start = NULL;
	while (ft_isspace(s[parse_list->index]) == true)
		parse_list->index += 1;
	while (s[parse_list->index])
	{
		if (((s[parse_list->index] == '<' || s[parse_list->index] == '>') && (s[parse_list->index + 1]  == '<' || s[parse_list->index + 1]  == '>' || s[parse_list->index + 1]  == '|')) && ((parse_list->quotes == false) || (parse_list->quotes == true && (parse_list->index < parse_list->quote_start || parse_list->index > parse_list->quote_end))))
		{
			parse_list->tkns_list->next = node_redir(parse_list->tkns_list->next, &s[parse_list->index], 2);
			parse_list->index += 2;
		}
		else if ((s[parse_list->index] == '<' || s[parse_list->index] == '>' || s[parse_list->index] == '|') && ((parse_list->quotes == false) || (parse_list->quotes == true && (parse_list->index < parse_list->quote_start || parse_list->index > parse_list->quote_end))))
		{
			parse_list->tkns_list->next = node_redir(parse_list->tkns_list->next, &s[parse_list->index], 1);
			parse_list->index += 1;
		}
		else
		{
			parse_list->tkns_list->next = make_node(parse_list->tkns_list->next, &s[parse_list->index]);
			while (s[parse_list->index] && ft_isspace(s[parse_list->index]) == false)
				parse_list->index += 1;
			if (parse_list->tkns_list->tok_type == CMD)
				parse_list->cmd_count++;
		}
		if (parse_list->start == NULL)
			parse_list->start = parse_list->tkns_list->next;
		while (ft_isspace(s[parse_list->index]) == true)
			parse_list->index += 1;
	}
	parse_list->tkns_list = parse_list->start;
	return (parse_list);
}

