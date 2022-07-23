#include "../include/minishell.h"

int	is_it_heredoc_or_in_redirec(t_parsing *parse_list)
{
	if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] == '<')
	{
		if (parse_list->tkns_array[parse_list->index_array]
			[parse_list->index_str_array + 1] == '<')
		{
			printf("do the heredoc\n");
			parse_list->tkns_array[parse_list->index_array]++;
			parse_list->tkns_array[parse_list->index_array]++;
			if (parse_list->tkns_array[parse_list->index_array][parse_list->index_str_array] != '\0')
				prep_next_node(parse_list);
			return (2);
		}
		printf("do the in redirection\n");
		parse_list->tkns_array[parse_list->index_array]++;
		if (parse_list->tkns_array[parse_list->index_array][parse_list->index_str_array] != '\0')
			prep_next_node(parse_list);
		return (1);
	}
	return (0);
}

int	is_it_redirec_out_or_append(t_parsing *parse_list)
{
	if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] == '>')
	{
		if (parse_list->tkns_array[parse_list->index_array]
			[parse_list->index_str_array + 1] == '>')
		{
			if (parse_list->index_str_array == 0)
			{
				parse_list->tkns_array[parse_list->index_array]++;
				parse_list->tkns_array[parse_list->index_array]++;
				printf("lala %s\n", parse_list->tkns_array[parse_list->index_array]);
				return (2);
			}
			printf("do the appends in the out\n");
			printf("lala %s\n", parse_list->tkns_array[parse_list->index_array]);
			parse_list->index_str_array++;
			parse_list->index_str_array++;
			if (parse_list->tkns_array[parse_list->index_array][parse_list->index_str_array] != '\0')
				prep_next_node(parse_list);
			return (2);
		}
		else
		{
			if (parse_list->index_str_array == 0)
			{
				parse_list->tkns_array[parse_list->index_array]++;
				printf("lala %s\n", parse_list->tkns_array[parse_list->index_array]);
				return (2);
			}
			printf("do the out redirect\n");
			parse_list->tkns_array[parse_list->index_array]++;
			if (parse_list->tkns_array[parse_list->index_array][parse_list->index_str_array] != '\0')
				prep_next_node(parse_list);
			return (1);
		}
	}
	return (0);
}
