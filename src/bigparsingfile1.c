#include "../include/minishell.h"

int	ft_strlen_without_delim(char *array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strchr("&|()<>", array[i]))
			break ;
		i++;
	}
	return (i);
}

int	next_or_not(t_parsing *parse_list, char *flag)
{
	if (*parse_list->tkns_array[parse_list->index_array] != '\0' || parse_list->tkns_array[parse_list->index_array + 1]) 
	{
		prep_next_node(parse_list);
		parse_list->tkns_list = parse_list->tkns_list->prev;
		parse_list->tkns_list = parse_list->tkns_list->next;
		return (0);
	}
	printf("Dundershell: syntax error near unexpected token `%s'\n", flag);
	return (1);
}
int	check_for_triple(t_parsing *parse_list)
{
	if (*parse_list->tkns_array[parse_list->index_array] == '<')
	{
		printf("Dundershell: syntax error near unexpected token `newline'\n");
		parse_list->tkns_array[parse_list->index_array]--;
		return (1);
	}
	return (0);
}

int	do_the_redir_in_or_heredoc(t_parsing *parse_list)
{
	parse_list->tkns_array[parse_list->index_array]++;
	if (*parse_list->tkns_array[parse_list->index_array] == '<')
	{
		parse_list->tkns_array[parse_list->index_array]++;
		if (next_or_not(parse_list, "newline") == 1)
			return (1);
		if (check_for_triple(parse_list) == 1)
			return (1);
		printf("do the heredoc(UTILISER SOIT LA FIN DE LA STR SI LE * NET PAS \\0 SINON LAUTRE index_array)\n");
		return (0);
	}
	if (next_or_not(parse_list, "newline") == 1)
		return (1);
	printf("do the redirect in(UTILISER SOIT LA FIN DE LA STR SI LE * NET PAS \\0 SINON LAUTRE index_array)\n");
	return (0);
}

void	parse_delim(t_parsing *parse_list)
{
	parse_list->index_str_array = 0;
	parse_list->tkns_list->tkn = calloc(ft_strlen_without_delim(parse_list->tkns_array[parse_list->index_array]), sizeof(char));
	while (*parse_list->tkns_array[parse_list->index_array] != '\0')
	{
		if (*parse_list->tkns_array[parse_list->index_array] == '<')
		{
			if (do_the_redir_in_or_heredoc(parse_list) == 1)
				return ;
		}
		parse_list->tkns_list->tkn[parse_list->index_str_array] = *parse_list->tkns_array[parse_list->index_array];
		parse_list->tkns_array[parse_list->index_array]++;
		parse_list->index_str_array++;
		// if (*parse_list->tkns_array[parse_list->index_array] == '>')
		// {
		// 	if (do_the_redir_out(parse_list) == 1)
		// 		return ;
		// }
		// if (*parse_list->tkns_array[parse_list->index_array] == '&')
		// 	{
		// 		if (do_the_ampersand(parse_list) == 1)
		// 			return ;
		// 	}
		// if (*parse_list->tkns_array[parse_list->index_array] == '|')
		// {
		// 	if (do_the_pipes(parse_list) == 1)
		// 		return ;
		// }
	}
	parse_list->tkns_list = parse_list->tkns_list->start;
	print_node_debug(parse_list);
}


int	start_parse(char *line)
{
	t_parsing	*parse_list;

	parse_list = init_master_list();
	parse_list->tkns_array = split(line);
	if (parse_list->tkns_array == NULL)
		return (1);
	init_first_token_nodes(parse_list);
	parse_delim(parse_list);


	// init_all_token_nodes(parse_list);
	// put_arg_pos(parse_list);
	// check_tokens(parse_list);
	// print_node_debug(parse_list);
	return (0);
}
