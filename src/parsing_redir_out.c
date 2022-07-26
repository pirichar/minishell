#include "../include/minishell.h"

int	check_outfile_name(t_parsing *parse_list, int i, int j)
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

int	check_redir_out(t_parsing *parse_list)
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
				if (parse_list->tkns_array[i][j + 1] == '>')
					j++;
				if (check_outfile_name(parse_list, i, j) == 1)
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
