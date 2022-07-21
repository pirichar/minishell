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
			return (2);
		}
		printf("do the in redirection\n");
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
			printf("do the appends in the out\n");
			return (2);
		}
		else
		{
			printf("do the out redirect\n");
			return (1);
		}
	}
	return (0);
}
