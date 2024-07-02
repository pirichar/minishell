#include "../include/minishell.h"

int	check_redir_in(t_parsing *parse_list)
{
	int	i;

	i = 0;
	while (parse_list->tkns_list != NULL)
	{
		while (parse_list->tkns_list->data[i])
		{
			if (parse_list->tkns_list->data[i] == '<' &&
				parse_list->tkns_list->data[i + 1] != '<' && i == 0)
			{
				if (parse_list->tkns_list->data[i + 1] == '>')
				{
					printf("do the <> special!\n");
					break ;
				}
				if (check_file_and_delim_name(parse_list->tkns_list) == 1)
					return (1);
				printf("do the redir in\n");
				break ;
			}
			i++;
		}
		i = 0;
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	return (0);
}
