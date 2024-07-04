#include "../include/minishell.h"

t_tkns	*set_toktype(t_tkns *matrix)
{
	while (matrix -> next)
		matrix = matrix -> next;
	if (matrix->data[0] == '<' && matrix->data[1] == '<')
		matrix->tok_type = TRUNC;
	else if (matrix->data[0] == '<' && matrix->data[1] == '>')
		matrix->tok_type = IN_OUT;
	else if (matrix->data[0] == '<')
		matrix->tok_type = INPUT;
	else if (matrix->data[0] == '>' && matrix->data[1] == '>')
		matrix->tok_type = APPEND;
	else if (matrix->data[0] == '>' && matrix->data[1] == '|')
		matrix->tok_type = SPECIAL_PIPE;
	else if (matrix->data[0] == '>')
		matrix->tok_type = OUTPUT;
	else if (matrix->data[0] == '|')
		matrix->tok_type = PIPE;
	else
		matrix->tok_type = CMD;
	return (matrix);
}

t_parsing	*new_split(char *s, t_parsing *parse_list)
{
	parse_list->index = 0;
	parse_list->start = NULL;
	while (ft_isspace(s[parse_list->index]) == true)
		parse_list->index += 1;
	while (s[parse_list->index])
	{
		if (should_do_it(s, parse_list))
			helper1(s, parse_list);
		else if (should_do_it_else(s, parse_list))
			helper2(s, parse_list);
		else
		{
			helper3(s, parse_list);
		}
		if (parse_list->start == NULL)
			parse_list->start = parse_list->tkns_list->next;
		while (ft_isspace(s[parse_list->index]) == true)
			parse_list->index += 1;
	}
	parse_list->tkns_list = parse_list->start;
	return (parse_list);
}
