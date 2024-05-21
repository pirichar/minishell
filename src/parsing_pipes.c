#include "../include/minishell.h"

int	check_pipes(t_parsing *parse_list) //should work as-is, can simplify with PIPE tok_type
{
	int	i;

	i = 0;
	while (parse_list->tkns_list != NULL)
	{
		while (parse_list->tkns_list->data[i])
		{
			if (parse_list->tkns_list->data[i] == '|'
				&& parse_list->tkns_list->data[i + 1] == '\0'
				&& i == 0)
			{
				if (check_pipe_name(parse_list->tkns_array, i) != 0)
					return (1);
				printf("do the pipe\n");
				break ;
			}
			i++;
		}
		i = 0;
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	return (0);
}
