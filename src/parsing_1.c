#include "../include/minishell.h"


/*
	// DEBUG - HERE WE HAD A PROBLEM WHEN WE HAVE A LINE LIKE 
	< notes.txt > out where there is not parse_lit->tkns_array[parse_list->i_arr] (no command)
	I added some check in the while loop 
*/


t_parsing	*get_cmd(t_parsing *parse_list)
{
	parse_list->cmd_count = count_cmd(parse_list->tkns_list);
	parse_list->vector_cmd = ft_calloc((parse_list->cmd_count) + 1, sizeof(char *));
	parse_list->start = parse_list->tkns_list;
	while (parse_list->tkns_list != NULL && parse_list->tkns_list->data != NULL && (parse_list->i_vect < parse_list->cmd_count))
	{
		if (parse_list->tkns_list->tok_type == CMD)
			parse_list = do_copy_cmd(parse_list, parse_list->tkns_list->data);
		if (parse_list->tkns_list->next)
			parse_list->tkns_list = parse_list->tkns_list->next;
		else
			break ;
	}
	parse_list->tkns_list = parse_list->start;
	parse_list->tkns_list->vector_cmd = parse_list->vector_cmd;
	return (parse_list);
}


void	init_master_list(t_parsing *parse_list, int status)
{
	parse_list->i_vect = 0;
	parse_list->infile = 0;
	parse_list->outfile = 1;
	parse_list->status = status;
	parse_list->quote_count = 0;
	parse_list->quote_start = 0;
	parse_list->quote_end = 0;
	parse_list->quote_type = EMPTY;
	parse_list->cmd_count = 0;
	parse_list->pids = ft_calloc(parse_list->nb_of_pipes + 1, sizeof(int));
	parse_list->file = open("./div/here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	close(parse_list->file);

}

t_parsing	*quotes_line(char *line, t_parsing *parse_list)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != 34 && line[i] != 39)
		i++;
	if (line[i] == 34 || line[i] == 39)
	{
		parse_list->quote_start = i;
		parse_list->quote_type = line[i];
	}
	i = ft_strlen(line) - 1;
	while (line[i] != '\0' && line[i] != parse_list->quote_type && i > 0)
		i--;
	if (parse_list->quote_start != i)
	{
		parse_list->quote_end = i;
		parse_list->quotes = true;
	}
	return (parse_list);
}

char *del_quotes(t_parsing *parse_list, char *line)
{
	int i;
	int y;

	char *newline;
	i = 0;
	y = 0;

	newline = ft_calloc(ft_strlen(line), sizeof(char *));
	while (line[i] != '\0')
	{
		if (line[i] != parse_list->quote_type)
		{
			newline[y] = line[i];
			y++;
		}
		else
			parse_list->quote_count++;
		i++;
	}
	parse_list->quote_end = parse_list->quote_end - parse_list->quote_count;
	newline[y] = '\0';
	return (newline);
}

t_parsing	*start_parse(char *line, int status)
{
	t_parsing	*parse_list;

	parse_list = ft_calloc(1, sizeof(t_parsing));
	init_master_list(parse_list, status);
	parse_list = quotes_line(line, parse_list);
	if (parse_list->quotes == true)
		line = del_quotes(*&parse_list, line);
	parse_list->tkns_list = init_list(line);
	parse_list = new_split(line, parse_list);
	parse_list = check_metachar(parse_list);
	parse_list = get_cmd(parse_list);
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
	int i;

	i = 0;
	parse_list->vector_cmd[parse_list->i_vect] = ft_calloc(ft_strlen(str) + 1, (sizeof(char)));
	while (parse_list && parse_list->tkns_list && str[i] != '\0' && (parse_list->i_vect < parse_list->cmd_count))
	{
		parse_list->vector_cmd[parse_list->i_vect][i] = str[i];
		i++;
	}
	parse_list->i_vect++;
	return (parse_list);
}
