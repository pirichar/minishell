#include "../include/minishell.h"

int	init_first_token_nodes(t_parsing *parse_list)
{
	parse_list->tkns_list = calloc(1, sizeof(t_tkns));
	parse_list->tkns_list->dollar_sign = false;
	parse_list->tkns_list->prev = NULL;
	parse_list->start = NULL;
	return (0);
}

int	count_cmd(t_tkns *tkns_list)
{
	int	count;

	count = 0;
	while (tkns_list != NULL)
	{
		if (tkns_list->tok_type == CMD)
			count++;
		tkns_list = tkns_list->next;
	}
	return (count);
}

int	check_file_and_delim_name(t_tkns *tkns_list)
{
	if (tkns_list->next != NULL)
	{
		if (ft_strchr("<|>", tkns_list->next->data[0]))
		{
			printf("Dundershell: syntax error near unexpected token `%c'\n",
				tkns_list->next->data[0]);
			return (1);
		}
	}
	if (!tkns_list->next)
	{
		printf("Dundershell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	check_pipe_name(t_tkns *tkns_list) //may 21, should be ok
{
	if (tkns_list->next
		&& tkns_list->next->data[0] == '|')
	{
		printf("Dundershell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (!tkns_list->next)
	{
		printf("Dundershell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

bool	check_cmd_quotes(char *s, t_parsing *parse_list, int index)
{
	int i;

	if (index != parse_list->index && parse_list->index != 0)
		i = parse_list->index;
	else
		i = index;
	if ((parse_list->quotes == false) 
		&& (ft_isspace(s[index]) == true))
		return(false);
	if (ft_isspace(s[index]) == true && parse_list->quotes == true 
		&& (i < parse_list->quote_start || i > parse_list->quote_end))
		return (false);
	if (ft_isspace(s[index]) == true && parse_list->quotes == true 
		&& (i >= parse_list->quote_start && i <= parse_list->quote_end))
		return (true);
	if (parse_list->quote_type == 39 && s[i] == 39)
		return (false);
	if ((parse_list->quotes == false || parse_list->quote_type == 34) 
		&& (ft_isspace(s[i]) == false))
		return(true);
	if  (parse_list->quote_type == 39 
		&& (i >= parse_list->quote_start 
		|| i <= parse_list->quote_end))
		return(true);
	return (false);
}
