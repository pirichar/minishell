#include "../include/minishell.h"

int	check_delim_name(t_parsing *parse_list, int i, int j)
{
	j += 2;
	if (parse_list->tkns_array[i] && (parse_list->tkns_array[i][j] || parse_list->tkns_array[i + 1] != NULL))
	{
		if (parse_list->tkns_array[i][j] == '<'
				|| parse_list->tkns_array[i + 1][0] == '<')
		{
			printf("Dundershell: syntax error near unexpected token `newline'\n");
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
		return (0);
	}
	if (parse_list->tkns_array[i + 1] == NULL)
	{
		printf("Dundershell: syntax error near unexpected token `newline'\n");
		return (1);
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
				break ;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	get_cmd(t_parsing *parse_list)
{
	int	count;
	int	ind_array;
	int	ind_str;
	int	ind_vector;

	count = 0;
	ind_array = 0;
	ind_str = 0;
	ind_vector = 0;
	while (parse_list->tkns_array[count] != NULL)
		count++;
	parse_list->tkns_list = calloc(sizeof(t_tkns), 1);
	parse_list->tkns_list->vector_cmd = calloc(sizeof(char *), count);
	while (count > ind_array)
	{
		parse_list->tkns_list->vector_cmd[ind_vector] = calloc(sizeof(char), ft_strlen(parse_list->tkns_array[ind_array]) + 1);
		while (parse_list->tkns_array[ind_array][ind_str])
		{
			if (ft_strchr("<>", parse_list->tkns_array[ind_array][ind_str]))
			{
				ind_array += 2;
				if (parse_list->tkns_array[ind_array - 1] == NULL || parse_list->tkns_array[ind_array] == NULL)
				{
					free(parse_list->tkns_list->vector_cmd[ind_vector]);
					return (0);
				}
			}
			else
			{
				parse_list->tkns_list->vector_cmd[ind_vector][ind_str] = parse_list->tkns_array[ind_array][ind_str];
				ind_str++;
			}
		}
		ind_str = 0;
		ind_array++;
		ind_vector++;
	}
	return (0);
}

void	print_tkns_array_debug(t_parsing *parse_list)
{
	int	i;

	i = 0;
	while (parse_list->tkns_list && parse_list->tkns_list->vector_cmd[i])
	{
		printf("array %d : %s\n", i, parse_list->tkns_list->vector_cmd[i]);
		i++;
	}
}

t_parsing	*start_parse(char *line)
{
	t_parsing	*parse_list;

	parse_list = init_master_list();
	parse_list->tkns_array = ft_split(line, ' ');
	if (parse_list->tkns_array == NULL)
		return (NULL);
	init_first_token_nodes(parse_list);
	if (check_heredocs(parse_list) != 0)
		return (NULL);
	get_cmd(parse_list);
	print_tkns_array_debug(parse_list);
	return (parse_list);
}
