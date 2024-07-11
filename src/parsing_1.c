#include "../include/minishell.h"

// loop over the line to see if its only spaces 
// once you meet something else then a space return false
bool	is_empty(char *line)
{
	while (*line)
	{
		if (*line != ' ')
			return (false);
		line++;
	}
	if (*line == '\0')
		return (true);
	else
		return (false);
}

t_parsing	*start_parse(char *line, int status)
{
	t_parsing	*parse_list;

	if (is_empty(line))
		return (NULL);
	parse_list = ft_calloc(1, sizeof(t_parsing));
	init_master_list(parse_list, status);
	parse_list = quotes_line(line, parse_list);
	line = expand_var(line, *&parse_list);
	if (parse_list->quotes == true)
		line = del_quotes(*&parse_list, line);
	parse_list->tkns_list = init_list(line);
	parse_list = new_split(line, parse_list);
	parse_list = check_metachar(parse_list);
	parse_list->pids = ft_calloc(parse_list->nb_of_pipes + 1, sizeof(int));
	parse_list = get_cmd(parse_list);
	if (parse_list->nb_of_pipes != 0)
		parse_list->pipes_args = get_argarray(parse_list);
	return (parse_list);
}

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '	')
		return (true);
	return (false);
}

t_parsing	*do_copy_cmd(t_parsing *parse_list, char *str)
{
	int	i;

	i = 0;
	parse_list->vector_cmd[parse_list->i_vect]
		= ft_calloc(ft_strlen(str) + 1, (sizeof(char)));
	while (parse_list && parse_list->tkns_list
		&& str[i] != '\0' && (parse_list->i_vect < parse_list->cmd_count))
	{
		parse_list->vector_cmd[parse_list->i_vect][i] = str[i];
		i++;
	}
	parse_list->i_vect++;
	return (parse_list);
}
