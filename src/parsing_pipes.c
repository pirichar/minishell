#include "../include/minishell.h"

int	check_pipes(t_parsing *parse_list)
{
	while (parse_list->tkns_list != NULL)
	{
		if (parse_list->tkns_list->tok_type == PIPE)
		{
			if (check_pipe_name(parse_list->tkns_list) != 0)
				return (1);
			printf("do the pipe\n");
			break ;
		}
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	return (0);
}
