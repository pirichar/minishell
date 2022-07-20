#include "../include/minishell.h"

void	i_str_list_0(t_parsing *parse_list, int nb)
{
	int	i;

	i = 1;
	parse_list->tkns_list->tkn[parse_list->i_str_list]
		= parse_list->tkns_array[parse_list->index_array]
	[parse_list->index_str_array];
	parse_list->i_str_list++;
	if (nb > 1)
	{
		parse_list->tkns_list->tkn[parse_list->i_str_list]
			= parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array];
		parse_list->i_str_list++;
		while (i < nb)
		{
			parse_list->tkns_array[parse_list->index_array]++;
			i++;
		}
	}
	parse_list->tkns_list->tkn[parse_list->i_str_list] = '\0';
	parse_list->tkns_array[parse_list->index_array]++;
	//regarde si il y a autre chose apres le delims, et cree la next node et init ses variables si cest le cas
	if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] != '\0')
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
		parse_list->index_str_array = 0;
	}
	return ;
}

void	i_str_list_no_0(t_parsing *parse_list, int nb)
{
	char	temp;

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
	still_no_0(parse_list, nb);
	return ;
}

void	still_no_0(t_parsing *parse_list, int nb)
{
	int	i;

	i = 1;
	if (nb > 1)
	{
		parse_list->tkns_list->tkn[parse_list->i_str_list]
			= parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array];
		parse_list->i_str_list++;
		while (i < nb)
		{
			parse_list->tkns_array[parse_list->index_array]++;
			i++;
		}
	}
	parse_list->tkns_list->tkn[parse_list->i_str_list] = '\0';
	parse_list->tkns_array[parse_list->index_array]++;
	if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] != '\0')
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
		parse_list->index_str_array = 0;
	}
	return ;
}
