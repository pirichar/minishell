#include "../include/minishell.h"

int	check_redir_out(t_parsing *parse_list) //simplify with token types, but now works
{
	int	i;

	i = 0;
	while (parse_list->tkns_list != NULL)
	{
		while (parse_list->tkns_list->data[i])
		{
			if (parse_list->tkns_list->data[i] == '>'
				&& i == 0)
			{
				if (parse_list->tkns_list->data[i + 1] == '|')
				{
					printf("do the >| special\n");
					break ;
				}
				if (parse_list->tkns_list->data[i + 1] == '>')
					i++;
				if (check_file_and_delim_name(parse_list->tkns_list, i) == 1)
					return (1);
				if (i == 1)
					printf("do the append out\n");
				else
					printf("do the redir out\n");
				break ;
			}
			i++;
		}
		i = 0;
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	return (0);
}
