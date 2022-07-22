#include "../include/minishell.h"

/*reecris ce qui est ds larrays split dans la node approprie*/
int	init_all_token_nodes(t_parsing *parse_list)
{
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

/*compte le new nb de tkns en prenant compte des delims et creer une node si necessaire*/
void	split_by_delims(t_parsing *parse_list)
{
	int	len_delim;
	int	i;

	i = 0;
	while (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array])
	{
		len_delim = check_delims(parse_list);
		// if (len_delim)
		// {
		// 	if (parse_list->i_str_list == 0)
		// 		//creer une node si il ny a pas de node precedentes
		// 		delim_on_first_node(parse_list, len_delim);
		// 	else
		// 		//cree une si il y a des nodes precedentes
		// 		delim_on_other_node(parse_list, len_delim);
		// }
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

/* le retour est la longueur du delimiteur trouve, soit 1 ou 2 ou 0 si aucun trouve */
int	check_delims(t_parsing *parse_list)
{
	int	ret;

	ret = is_it_ampersand(parse_list);
	if (ret == 0)
		ret = is_it_pipes(parse_list);
	if (ret == 0)
		ret = is_it_heredoc_or_in_redirec(parse_list);
	if (ret == 0)
		ret = is_it_redirec_out_or_append(parse_list);
	return (ret);
}

int	is_it_ampersand(t_parsing *parse_list)
{
	if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] == '&'
		&& parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array + 1] == '&')
	{
		if (parse_list->index_str_array == 0)
		{
			printf("DunderShell: syntax error near unexpected token `%.2s'\n",
				parse_list->tkns_array[parse_list->index_array]);
			return (0);
		}
		if (parse_list->tkns_array[parse_list->index_array][parse_list->index_str_array + 2] == '\0')
		{
			printf("DunderShell: syntax error near unexpected token `&&'\n");
			return (0);
		}
		printf("do the &&\n");
		parse_list->tkns_array[parse_list->index_array]++;
		parse_list->tkns_array[parse_list->index_array]++;
		prep_next_node(parse_list);
		return (2);
	}
	return (0);
}

int	is_it_pipes(t_parsing *parse_list)
{
	if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] == '|')
	{
		if (parse_list->tkns_array[parse_list->index_array]
			[parse_list->index_str_array + 1] == '|')
		{
			printf("do the double pipe\n");
			parse_list->tkns_array[parse_list->index_array]++;
			parse_list->tkns_array[parse_list->index_array]++;
			prep_next_node(parse_list);
			return (2);
		}
		printf("do the simple pipe\n");
		parse_list->tkns_array[parse_list->index_array]++;
		prep_next_node(parse_list);
		return (1);
	}
	return (0);
}
