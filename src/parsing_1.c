#include "../include/minishell.h"

int	check_delim_name(t_parsing *parse_list, int i, int j)
{
	j += 2;
	if (parse_list->tkns_array[i][j] || parse_list->tkns_array[i + 1] != NULL)
	{
		if (parse_list->tkns_array[i][j] == '<'
				|| parse_list->tkns_array[i + 1][0] == '<')
		{
			printf("Dundershell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		else if (parse_list->tkns_array[i][j] == '>'
				|| parse_list->tkns_array[i + 1][0] == '>')
		{
			printf("Dundershell: syntax error near unexpected token `>'\n");
			return (1);
		}
		else if (parse_list->tkns_array[i][j] == '|'
				|| parse_list->tkns_array[i + 1][0] == '|')
		{
			printf("Dundershell: syntax error near unexpected token `|'\n");
			return (1);
		}
	}
	return (0);
}

int	do_the_heredoc(t_parsing *parse_list)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	j = 0;
	temp = NULL;
	printf("do_heredoc(parse_list)\n");
	while (parse_list->tkns_array[i])
	{
		while (parse_list->tkns_array[i][j])
		{
		
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
				return (0);
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
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (parse_list->tkns_array[i] != NULL)
		i++;
	parse_list->tkns_list = calloc(sizeof(t_tkns), 1);
	parse_list->tkns_list->vector_cmd = calloc(sizeof(char *), i);
	while (i > j)
	{
		parse_list->tkns_list->vector_cmd[j] = calloc(sizeof(char), ft_strlen(parse_list->tkns_array[j]));
		while (parse_list->tkns_array[j][k])
		{
			if (ft_strchr("<>|", parse_list->tkns_array[i][j]) != NULL)
			{
				j++;
				parse_list->tkns_list->vector_cmd[j] = calloc(sizeof(char), ft_strlen(parse_list->tkns_array[j]));
				continue ;
			}
			parse_list->tkns_list->vector_cmd[j][k] = parse_list->tkns_array[j][k];
			k++;
		}
		k = 0;
		j++;
	}
	return (0);
}

void	print_tkns_array_debug(t_parsing *parse_list)
{
	int	i;

	i = 0;
	while (parse_list->tkns_array[i])
	{
		printf("array %d : %s\n", i, parse_list->tkns_array[i]);
		i++;
	}
}

int	start_parse(char *line)
{
	t_parsing	*parse_list;

	parse_list = init_master_list();
	parse_list->tkns_array = ft_split(line, ' ');
	if (parse_list->tkns_array == NULL)
		return (1);
	init_first_token_nodes(parse_list);
	if (check_heredocs(parse_list) != 0)
		return (2);
	get_cmd(parse_list);
	print_tkns_array_debug(parse_list);
	return (0);
}
