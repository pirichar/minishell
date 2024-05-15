#include "../include/minishell.h"

int	check_pipes(t_parsing *parse_list) //should work as-is
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (parse_list->tkns_array != NULL)
	{
		while (parse_list->tkns_array->data[j])
		{
			if (parse_list->tkns_array->data[j] == '|'
				&& parse_list->tkns_array->data[j + 1] == '\0'
				&& j == 0)
			{
				if (check_pipe_name(parse_list->tkns_array, j) != 0)
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
