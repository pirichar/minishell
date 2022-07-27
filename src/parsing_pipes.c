#include "../include/minishell.h"

int	check_pipes(t_parsing *parse_list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (parse_list->tkns_array[i])
	{
		while (parse_list->tkns_array[i][j])
		{
			if (parse_list->tkns_array[i][j] == '|'
				&& parse_list->tkns_array[i][j + 1] == '\0'
				&& j == 0)
			{
				if (check_pipe_name(parse_list, i, j) != 0)
					return (1);
				printf("do the pipe\n");
				break ;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
