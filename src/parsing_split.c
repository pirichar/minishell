#include "../include/minishell.h"

t_tkns *set_toktype(t_tkns *matrix)
{
	if (matrix->data[0] == '<' && matrix->data[1]  == '<')
		matrix->tok_type = TRUNC;
	else if (matrix->data[0] == '<' && matrix->data[1]  == '>')
		matrix->tok_type = OUT_IN; 
	else if (matrix->data[0] == '<')
		matrix->tok_type = INPUT;
	if (matrix->data[0] == '>' && matrix->data[1]  == '>')
		matrix->tok_type = APPEND;
	if (matrix->data[0] == '>' && matrix->data[1]  == '|')
		matrix->tok_type = SPECIAL_PIPE; 
	else if (matrix->data[0] == '>')
		matrix->tok_type = OUTPUT;
	if (matrix->data[0] == '|')
		matrix->tok_type = PIPE;
	else
		matrix->tok_type = CMD;
	return (matrix);
}

t_tkns *make_node(t_tkns *matrix, char *s)
{
	t_tkns	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_tkns));
	if (new == NULL)
		return (NULL);
	new->data = malloc(sizeof(char *));
	while (s[i] != '\0' && (s[i] != '<' && s[i] != '>' && s[i] != '|'))
	{
		new->data[i] = s[i];
		printf("letters inside node ==== %c\n", new->data[i]);
		i++;
	}
	new->data[i] = '\0';
	printf("line inside node ==== %s\n", new->data);
	new->next = NULL;
	if (!matrix->data)
		matrix = new;
	else
		matrix->next = new;
	matrix = new;
	return(set_toktype(matrix));
}

t_tkns *node_redir(t_tkns *matrix, char *s, int size)
{
	t_tkns	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_tkns));
	if (new == NULL)
		return (NULL);
	new->data = malloc(sizeof(char *));
	while (i < size)
	{
		new->data[i] = s[i];
		printf("letters inside noderedir ==== %c\n", new->data[i]);
		i++;
	}
	new->data[i] = '\0';
	printf("line inside nodredire ==== %s\n", new->data);
	new->next = NULL;
	if (!matrix->data)
		matrix = new;
	else
		matrix->next = new;
	matrix = new;
	return(set_toktype(matrix));
}

t_parsing *new_split(char *s, t_parsing *parse_list)
{
	parse_list->tkns_list = malloc(sizeof(t_tkns *));
	if (parse_list->tkns_list == NULL)
		return (NULL);
	printf("line in newsplit start ==== %s\n", s);	
	while (*s)
	{
		if ((*s == '<' || *s == '>') && (s[1]  == '<' || s[1]  == '>' || s[1]  == '|'))
		{
			parse_list->tkns_list = node_redir(parse_list->tkns_list, s, 2);
			s += 2;
		}
		else if (*s == '<' || *s == '>' || *s == '|')
		{
			parse_list->tkns_list = node_redir(parse_list->tkns_list, s, 1);
			s += 1;
		}
		else if (*s != '<' && *s != '>' && *s != '|')
		{
			printf("line in newsplit ==== %s\n", s);
			parse_list->tkns_list = make_node(parse_list->tkns_list, s);
			printf("line in newsplit after node made ==== %s\n", s);
			while (*s != '\0' && (*s != '<' && *s != '>' && *s != '|'))
				s += 1;
		}
	}
	printf("hello before returning parse list\n");
	return parse_list;
}