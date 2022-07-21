#include "../include/minishell.h"

void	prep_next_node(t_parsing *parse_list)
{
	parse_list->tkns_list->next = calloc(1, sizeof(t_tkns));
	parse_list->tkns_list->next->prev = parse_list->tkns_list;
	(parse_list->tkns_list->next)->start = parse_list->tkns_list->start;
	parse_list->tkns_list = parse_list->tkns_list->next;
	parse_list->tkns_list->dollar_sign = false;
	parse_list->tkns_list->flags = 400;
	parse_list->tkns_list->tkn = calloc(ft_strlen_delim(
				(parse_list->tkns_array[parse_list->index_array]))
			+ 1, sizeof(char));
		parse_list->i_str_list = 0;
}

void	how_many_letters_in_delim(t_parsing *parse_list, int nb)
{
	int	i;

	i = 1;
	if (nb > 1)
	{
		parse_list->tkns_list->tkn[parse_list->i_str_list]
			= parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array];
		parse_list->i_str_list++;
		while (i++ < nb)
			parse_list->tkns_array[parse_list->index_array]++;
	}
}

void	delim_on_first_node(t_parsing *parse_list, int nb)
{
	parse_list->tkns_list->tkn[parse_list->i_str_list++]
		= parse_list->tkns_array[parse_list->index_array]
	[parse_list->index_str_array];
	how_many_letters_in_delim(parse_list, nb);
	parse_list->tkns_list->tkn[parse_list->i_str_list] = '\0';
	parse_list->tkns_array[parse_list->index_array]++;
	if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] != '\0')
	{
		prep_next_node(parse_list);
		parse_list->index_str_array = 0;
	}
	return ;
}

void	init_node_for_delim(t_parsing *parse_list)
{
	char	temp;

	temp = parse_list->tkns_array[parse_list->index_array]
	[parse_list->index_str_array];
	while (*parse_list->tkns_array[parse_list->index_array] != temp)
		parse_list->tkns_array[parse_list->index_array]++;
	parse_list->i_str_list = 0;
	parse_list->index_str_array = 0;
	parse_list->tkns_list->tkn[parse_list->i_str_list]
		= parse_list->tkns_array[parse_list->index_array]
	[parse_list->index_str_array];
	parse_list->i_str_list++;
}

void	delim_on_other_node(t_parsing *parse_list, int nb)
{
	prep_next_node(parse_list);
	init_node_for_delim(parse_list);
	how_many_letters_in_delim(parse_list, nb);
	parse_list->tkns_list->tkn[parse_list->i_str_list] = '\0';
	parse_list->tkns_array[parse_list->index_array]++;
	if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] != '\0')
	{
		prep_next_node(parse_list);
		parse_list->index_str_array = 0;
	}
	return ;
}
