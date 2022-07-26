#include "../include/minishell.h"

int	check_redir_in(t_parsing *parse_list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (parse_list->tkns_array[i])
	{
		while (parse_list->tkns_array[i][j])
		{
			if (parse_list->tkns_array[i][j] == '<' &&
				parse_list->tkns_array[i][j + 1] != '<'
				&& j == 0)
			{
				if (check_infile_name(parse_list, i, j) == 1)
					return (1);
				printf("do the redir in\n");
				break ;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	check_infile_name(t_parsing *parse_list, int i, int j)
{
	if (parse_list->tkns_array[i + 1])
	{
		if (parse_list->tkns_array[i + 1][0] == '<')
		{
			printf("Dundershell: syntax error near unexpected token `<'\n");
			return (1);
		}
		if (parse_list->tkns_array[i + 1][0] == '>')
		{
			printf("Dundershell: syntax error near unexpected token `>'\n");
			return (1);
		}
		if (parse_list->tkns_array[i + 1][0] == '|')
		{
			printf("Dundershell: syntax error near unexpected token `|'\n");
			return (1);
		}
	}
	if (!parse_list->tkns_array[i + 1])
	{
		printf("Dundershell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (parse_list->tkns_array[i][j + 1] != '\0')
	{
		printf("Dundershell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}
