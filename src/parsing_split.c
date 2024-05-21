#include "../include/minishell.h"

t_tkns *set_toktype(t_tkns *matrix)
{
	if (matrix->data[0] == '<' && matrix->data[1]  == '<')
		matrix->tok_type = TRUNC;
	else if (matrix->data[0] == '<' && matrix->data[1]  == '>')
		matrix->tok_type = ; //whats its name??
	else if (matrix->data[0] == '<')
		matrix->tok_type = INPUT;
	if (matrix->data[0] == '>' && matrix->data[1]  == '>')
		matrix->tok_type = APPEND;
	if (matrix->data[0] == '>' && matrix->data[1]  == '|')
		matrix->tok_type = ; //whats its name??
	else if (matrix->data[0] == '>')
		matrix->tok_type = OUTPUT;
	if (matrix->data[0] == '|')
		matrix->tok_type = PIPE;
	else
		matrix->tok_type = CMD;
}

t_tkns *make_node(t_tkns *matrix, char *s)
{
	t_tkns	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_tkns));
	if (new == NULL)
		return (NULL);
	while (s[i] != '<' || s[i] != '>' || s[i] != '|')
	{
		new->data[i] = s[i];
		i++;
	}
	new->data[i] = '\0';
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
	while (i < size)
	{
		new->data[i] = s[i];
		i++;
	}
	new->data[i] = '\0';
	new->next = NULL;
	if (!matrix->data)
		matrix = new;
	else
		matrix->next = new;
	matrix = new;
	return(set_toktype(matrix));
}

t_tkns *new_split(char *s, char *set)
{
	t_tkns	*matrix;

	matrix = malloc(sizeof(t_tkns));
	if (matrix == NULL)
		return (NULL);
	while (*s)
	{
		if ((*s == '<' || *s == '>') && s[1]  == *s)
		{
			matrix = node_redir(matrix, s, 2);
			s += 2;
		}
		else if (*s == '<' || *s == '>' || *s == '|')			
			matrix = node_redir(matrix, s, 1); //change to a function like 'make_node' to have the <> and the >| tokens in mind (loop while s[i] = <, > or |) 
		else if (*s != '<' || *s != '>' || *s != '|')
		{
			matrix = make_node(matrix, s);
			while ((*s != '<' || *s != '>' || *s != '|'))
				s++;
		}
		s++;
	}
	return matrix;
}