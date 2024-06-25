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

t_tkns *make_node(t_tkns *matrix, char *s, t_parsing *parse_list, int i)
{
	t_tkns	*new;
	int		y;

	y = 0;
	new = (t_tkns *)malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->data = malloc(sizeof(char *));
	while (s[i])
	{
		if (ft_isspace(s[i]) == true && (parse_list->quotes == false || (parse_list->quotes == true && (i < parse_list->quote_start || i > parse_list->quote_end))))
			break;
		if ((s[i] == '<' || s[i] == '>' || s[i] == '|') && (parse_list->quotes == false || (parse_list->quotes == true && (i < parse_list->quote_start || i > parse_list->quote_end))))
		break ;
		if (s[i] == '$' && ((parse_list->quotes == false) || ((parse_list->quotes == true && (parse_list->quote_type == '\'' && (i < parse_list->quote_start || i > parse_list->quote_end))) || (parse_list->quote_type == '"' && (i >= parse_list->quote_start || i <= parse_list->quote_end)))))
			s = expend_var(s, parse_list, i);
		new->data[y] = s[i];
		i++;
		y++;
	}
	new->data[y] = '\0';
	new->next = NULL;
	nodeaddback(&matrix, new);
	return(set_toktype(matrix));
}

t_tkns *node_redir(t_tkns *matrix, char *s, int size, int i)
{
	t_tkns	*new;
	int		y;

	y = 0;
	new = (t_tkns *)malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->data = malloc(sizeof(char *));
	while (y++ < size)
	{
		new->data[y] = s[i];
		i++;
	}
	new->data[y] = '\0';
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
	list->data = s;
	list->next = NULL;
	return (list);
}

t_parsing *new_split(char *s, t_parsing *parse_list) 
{
	int i;

	i = 0;
	parse_list->start = NULL;
	while (ft_isspace(s[i]) == true)
		i += 1;
	parse_list->old_quote_end = parse_list->quote_end;
	parse_list->quote_pos = false;
	while (s[i] != '\0')
	{
		if (((s[i] == '<' || s[i] == '>') && (s[i + 1]  == '<' || s[i + 1]  == '>' || s[i + 1]  == '|')) && (parse_list->quotes == false || (parse_list->quotes == true && (i < parse_list->quote_start || i > parse_list->old_quote_end))))
		{
			parse_list->tkns_list->next = node_redir(parse_list->tkns_list->next, s, 2, i);
			i += 2;
		}
		else if ((s[i] == '<' || s[i] == '>' || s[i] == '|') && (parse_list->quotes == false || (parse_list->quotes == true && (i < parse_list->quote_start || i > parse_list->old_quote_end))))
		{
			parse_list->tkns_list->next = node_redir(parse_list->tkns_list->next, s, 1, i);
			i += 1;
		}
		else
		{
			parse_list->tkns_list->next = make_node(parse_list->tkns_list->next, s, parse_list, i);
			if (parse_list->old_quote_end != parse_list->quote_end && parse_list->quote_pos == false)
			{
				i = parse_list->old_quote_end + 1;
				parse_list->quote_pos = true;
			}
			else
				i += ft_strlen(parse_list->tkns_list->next->data);
			if (parse_list->tkns_list->tok_type == CMD)
				parse_list->cmd_count++;
		}
		if (parse_list->start == NULL)
			parse_list->start = parse_list->tkns_list->next;
		while (ft_isspace(s[i]) == true)
			i += 1;
	}
	parse_list->tkns_list = parse_list->start;
	return (parse_list);
}

