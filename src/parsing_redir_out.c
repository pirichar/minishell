#include "../include/minishell.h"

int	check_redir_out(t_parsing *parse_list) //simplify with token types
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (parse_list->tkns_array[i])
	{
		while (parse_list->tkns_array[i][j])
		{
			if (parse_list->tkns_array[i][j] == '>'
				&& j == 0)
			{
				if (parse_list->tkns_array[i][j + 1] == '|')
				{
					printf("do the >| special\n");
					break ;
				}
				if (parse_list->tkns_array[i][j + 1] == '>')
					j++;
				if (check_file_and_delim_name(parse_list, i, j) == 1)
					return (1);
				if (j == 1)
					printf("do the append out\n");
				else
					printf("do the redir out\n");
				break ;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
