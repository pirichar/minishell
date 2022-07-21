#include "../include/minishell.h"

t_parsing	*init_master_list(void)
{
	t_parsing	*parse_list;

	parse_list = calloc(1, sizeof(t_parsing));
	parse_list->index_array = 0;
	parse_list->index_str_array = 0;
	parse_list->i_str_list = 0;
	return (parse_list);
}

void	print_node_debug(t_parsing *parse_list)
{
	while (parse_list->tkns_list->tkn != NULL)
	{
		printf("tkns = %s, arg pos = %d, flags = %d, is dollar sign? = %d\n",
			parse_list->tkns_list->tkn,
			parse_list->tkns_list->argv_pos, parse_list->tkns_list->flags,
			parse_list->tkns_list->dollar_sign);
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	return ;
}

int	start_parse(char *line)
{
	t_parsing	*parse_list;

	parse_list = init_master_list();
	parse_list->tkns_array = split(line);
	if (parse_list->tkns_array == NULL)
		return (1);
	init_first_token_nodes(parse_list);
	init_other_token_nodes(parse_list);
	put_arg_pos(parse_list);
	check_tokens(parse_list);
	print_node_debug(parse_list);
	return (0);
}

int	init_first_token_nodes(t_parsing *parse_list)
{
	parse_list->tkns_list = calloc(1, sizeof(t_tkns));
	parse_list->tkns_list->dollar_sign = false;
	parse_list->tkns_list->flags = 400; //400 correspond a aucun flags de setter, a NULL
	parse_list->tkns_list->prev = NULL;
	parse_list->tkns_list->start = parse_list->tkns_list;
	return (0);
}

void	init_circular_list(t_parsing *parse_list)
{
	parse_list->tkns_list->tkn[parse_list->i_str_list] = '\0';
	if (parse_list->tkns_list->tkn == NULL)
		parse_list->tkns_list = parse_list->tkns_list->prev;
	parse_list->index_array++;
	parse_list->tkns_list->next = calloc(1, sizeof(t_tkns));
	parse_list->tkns_list->next->prev = parse_list->tkns_list;
	(parse_list->tkns_list->next)->start = parse_list->tkns_list->start;
	parse_list->tkns_list = parse_list->tkns_list->next;
	parse_list->tkns_list->dollar_sign = false;
	return ;
}

int	init_other_token_nodes(t_parsing *parse_list)
{
	//reecris ce qui est ds larrays split dans la node approprie
	while (cnt_tokens(parse_list->tkns_array) > parse_list->index_array)
	{
		parse_list->tkns_list->tkn = calloc(ft_strlen_delim(
					(parse_list->tkns_array[parse_list->index_array]))
				+ 1, sizeof(char));
		split_by_delims(parse_list);
		init_circular_list(parse_list);
	}
	parse_list->tkns_list = parse_list->tkns_list->start;
	return (0);
}

void	split_by_delims(t_parsing *parse_list)
{
	while (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array])
	{
		//compte le new nb de tkns en prenant compte des delims qui retourne la longuer du delims trouver
		//ou 0 si aucun delims, pour avoir la longueur du tkns de la nouvelle node si necessaire
		if (check_delims(parse_list))
		{
			if (parse_list->i_str_list == 0)
				//creer une node si il ny a pas de node precedentes
				i_str_list_0(parse_list, check_delims(parse_list));
			else
				//cree une si il y a des nodes precedentes
				i_str_list_no_0(parse_list, check_delims(parse_list));
		}
		if (parse_list->tkns_array[parse_list->index_array]
			[parse_list->index_str_array] == '\0')
			break ;
		parse_list->tkns_list->tkn[parse_list->i_str_list]
			= parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array];
		parse_list->index_str_array++;
		parse_list->i_str_list++;
	}
	return ;
}

int	check_delims(t_parsing *parse_list)
{
	if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] == '&'
		&& parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array + 1] == '&')
	{
		printf("do the &&\n");
		return (2);
	}
	else if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] == '|')
	{
		if (parse_list->tkns_array[parse_list->index_array]
			[parse_list->index_str_array + 1] == '|')
		{
			printf("do the double pipe\n");
			return (2);
		}
		else
		{
			printf("do the simple pipe\n");
			return (1);
		}
	}
	else if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] == '<')
	{
		if (parse_list->tkns_array[parse_list->index_array]
			[parse_list->index_str_array + 1] == '<')
		{
			printf("do the heredoc\n");
			return (2);
		}
		else
		{
			printf("do the in redirection\n");
			return (1);
		}
	}
	else if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] == '>')
	{
		if (parse_list->tkns_array[parse_list->index_array]
			[parse_list->index_str_array + 1] == '>')
		{
			printf("do the appends in the out\n");
			return (2);
		}
		else
		{
			printf("do the out redirect\n");
			return (1);
		}
	}
	else
		return (0);
}
