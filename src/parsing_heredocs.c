#include "../include/minishell.h"

int	check_delim_name(t_parsing *parse_list, int i, int j)
{
	j += 2;
	if (!parse_list->tkns_array[i + 1])
	{
		if (parse_list->tkns_array[i][j] && parse_list->tkns_array[i][j] != '<')
		{
			printf("Dundershell: syntax error near unexpected token `%c'\n", parse_list->tkns_array[i][j]);
			return (1);
		}
		printf("Dundershell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (parse_list->tkns_array[i] && (parse_list->tkns_array[i][j] || parse_list->tkns_array[i + 1] != NULL))
	{
		if (parse_list->tkns_array[i][j] == '<'
				|| parse_list->tkns_array[i + 1][0] == '<')
		{
			printf("Dundershell: syntax error near unexpected token `<'\n");
			return (1);
		}
		if (parse_list->tkns_array[i][j] == '>'
				|| parse_list->tkns_array[i + 1][0] == '>')
		{
			printf("Dundershell: syntax error near unexpected token `>'\n");
			return (1);
		}
		if (parse_list->tkns_array[i][j] == '|'
				|| parse_list->tkns_array[i + 1][0] == '|')
		{
			printf("Dundershell: syntax error near unexpected token `|'\n");
			return (1);
		}
		if (parse_list->tkns_array[i][j] != '\0')
		{
			printf("Dundershell: syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	return (0);
}

int	check_heredocs(t_parsing *parse_list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (parse_list->tkns_array[i])
	{
		while (parse_list->tkns_array[i][j])
		{
			if (parse_list->tkns_array[i][j] == '<'
				&& parse_list->tkns_array[i][j + 1] == '<')
			{
				if (check_delim_name(parse_list, i, j) == 1)
					return (1);
				printf("do_heredoc(parse_list)\n");
				j++;
				break ;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
