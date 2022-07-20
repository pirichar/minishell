#include "../include/minishell.h"

int	start_parse(char *line)
{
	t_parsing	*parse_list;

	//init la master list
	parse_list = calloc(1, sizeof(t_parsing));
	parse_list->index_array = 0;
	parse_list->index_str_array = 0;
	parse_list->i_str_list = 0;
	//split les tknsd selon le split a marie(space and quotes)
	parse_list->tkns_array = split(line); 
	if (parse_list->tkns_array == NULL)
		return (0);
	if (parse_list->tkns_array)
		// init des nodes par tokens et leurs variables
		put_on_the_props(parse_list);
	parse_list->tkns_list = parse_list->tkns_list->start;
	//ce while sers juste a imprimer les tkns POUR DEBUG
	while (parse_list->tkns_list->tkn != NULL)
	{
		printf("tkns = %s, arg pos = %d, flags = %d, is dollar sign? = %d\n",
			parse_list->tkns_list->tkn,
			parse_list->tkns_list->argv_pos, parse_list->tkns_list->flags,
			parse_list->tkns_list->dollar_sign);
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	return (0);
}

int	put_on_the_props(t_parsing *parse_list)
{
	parse_list->tkns_list = calloc(1, sizeof(t_tkns));
	parse_list->tkns_list->dollar_sign = false;
	parse_list->tkns_list->flags = 400;
	parse_list->tkns_list->prev = NULL;
	parse_list->tkns_list->start = parse_list->tkns_list;
	//functions qui 
	assign_the_list(parse_list);
	parse_list->tkns_list->next = NULL;
	parse_list->tkns_list->tkn = NULL;
	parse_list->tkns_list = parse_list->tkns_list->start;
	check_tokens(parse_list);
	return (0);
}

int	assign_the_list(t_parsing *parse_list)
{
	int	tks_cnt;

	tks_cnt = cnt_tokens(parse_list->tkns_array);
	while (tks_cnt > parse_list->index_array)
	{
		parse_list->tkns_list->argv_pos = parse_list->index_array;
		parse_list->tkns_list->tkn = calloc(ft_strlen_delim(
					(parse_list->tkns_array[parse_list->index_array]))
				+ 1, sizeof(char));
		check_index_array(parse_list);
		parse_list->tkns_list->tkn[parse_list->i_str_list] = '\0';
		if (parse_list->tkns_list->tkn == NULL)
			parse_list->tkns_list = parse_list->tkns_list->prev;
		parse_list->index_array++;
		parse_list->tkns_list->next = calloc(1, sizeof(t_tkns));
		parse_list->tkns_list->next->prev = parse_list->tkns_list;
		(parse_list->tkns_list->next)->start = parse_list->tkns_list->start;
		parse_list->tkns_list = parse_list->tkns_list->next;
		parse_list->tkns_list->dollar_sign = false;
	}
	parse_list->tkns_list = parse_list->tkns_list->start;
	put_arg_pos(parse_list);
	return (0);
}

void	check_index_array(t_parsing *parse_list)
{
	int	nb;

	while (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array])
	{
		nb = check_delims(parse_list);
		if (nb != 0)
		{
			if (parse_list->i_str_list == 0)
				i_str_list_0(parse_list, nb);
			else
				i_str_list_no_0(parse_list, nb);
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
