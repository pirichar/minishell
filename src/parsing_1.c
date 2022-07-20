#include "../include/minishell.h"

int	assign_the_list(t_parsing *parse_list)
{
	int	tks_cnt;

	tks_cnt = cnt_tokens(parse_list->tkns_array);
	while (tks_cnt > parse_list->index_array)
	{
		parse_list->tkns_list->argv_pos = parse_list->index_array;
		parse_list->tkns_list->tkn = calloc(ft_strlen_delim(
					(parse_list->tkns_array[parse_list->index_array]))
				+ 1, sizeof(char));
		check_index_array(parse_list);
		parse_list->tkns_list->tkn[parse_list->i_str_list] = '\0';
		if (parse_list->tkns_list->tkn == NULL)
			parse_list->tkns_list = parse_list->tkns_list->prev;
		parse_list->index_str_array = 0;
		parse_list->i_str_list = 0;
		parse_list->index_str_array = 0;
		parse_list->index_array++;
		parse_list->tkns_list->next = calloc(1, sizeof(t_tkns));
		parse_list->tkns_list->next->prev = parse_list->tkns_list;
		(parse_list->tkns_list->next)->start = parse_list->tkns_list->start;
		parse_list->tkns_list = parse_list->tkns_list->next;
		parse_list->tkns_list->dollar_sign = false;
	}
	parse_list->tkns_list = parse_list->tkns_list->start;
	put_arg_pos(parse_list);
	return (0);
}

void	put_arg_pos(t_parsing *parse_list)
{
	int	i;

	i = 0;
	while (parse_list->tkns_list->tkn)
	{
		if (parse_list->tkns_list->tkn == NULL)
			break ;
		parse_list->tkns_list->argv_pos = i;
		parse_list->tkns_list = parse_list->tkns_list->next;
		i++;
	}
	return ;
}

void	check_index_array(t_parsing *parse_list)
{
	int	nb;

	while (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array])
	{
		nb = check_delims(parse_list);
		if (nb != 0)
		{
			if (parse_list->i_str_list == 0)
				i_str_list_0(parse_list, nb);
			else
				i_str_list_no_0(parse_list, nb);
		}
		if (parse_list->tkns_array[parse_list->index_array]
			[parse_list->index_str_array] == '\0')
			break ;
		parse_list->tkns_list->tkn[parse_list->i_str_list]
			= parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array];
		parse_list->index_str_array++;
		parse_list->i_str_list++;
	}
	return ;
}

int	check_delims(t_parsing *parse_list)
{
	if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] == '&'
		&& parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array + 1] == '&')
	{
		printf("do the &&\n");
		return (2);
	}
	else if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] == '|')
	{
		if (parse_list->tkns_array[parse_list->index_array]
			[parse_list->index_str_array + 1] == '|')
		{
			printf("do the double pipe\n");
			return (2);
		}
		else
		{
			printf("do the simple pipe\n");
			return (1);
		}
	}
	else if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] == '<')
	{
		if (parse_list->tkns_array[parse_list->index_array]
			[parse_list->index_str_array + 1] == '<')
		{
			printf("do the heredoc\n");
			return (2);
		}
		else
		{
			printf("do the in redirection\n");
			return (1);
		}
	}
	else if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] == '>')
	{
		if (parse_list->tkns_array[parse_list->index_array]
			[parse_list->index_str_array + 1] == '>')
		{
			printf("do the appends in the out\n");
			return (2);
		}
		else
		{
			printf("do the out redirect\n");
			return (1);
		}
	}
	else
		return (0);
}

void	i_str_list_0(t_parsing *parse_list, int nb)
{
	int	i;

	i = 1;
	parse_list->tkns_list->tkn[parse_list->i_str_list]
		= parse_list->tkns_array[parse_list->index_array]
	[parse_list->index_str_array];
	parse_list->i_str_list++;
	if (nb > 1)
	{
		parse_list->tkns_list->tkn[parse_list->i_str_list]
			= parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array];
		parse_list->i_str_list++;
		while (i < nb)
		{
			parse_list->tkns_array[parse_list->index_array]++;
			i++;
		}
	}
	parse_list->tkns_list->tkn[parse_list->i_str_list] = '\0';
	parse_list->tkns_array[parse_list->index_array]++;
	if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] != '\0')
	{
		parse_list->tkns_list->next = calloc(1, sizeof(t_tkns));
		parse_list->tkns_list->next->prev = parse_list->tkns_list;
		(parse_list->tkns_list->next)->start = parse_list->tkns_list->start;
		parse_list->tkns_list = parse_list->tkns_list->next;
		parse_list->tkns_list->dollar_sign = false;
		parse_list->tkns_list->flags = 400;
		parse_list->tkns_list->tkn = calloc(ft_strlen_delim(
					(parse_list->tkns_array[parse_list->index_array]))
				+ 1, sizeof(char));
		parse_list->i_str_list = 0;
		parse_list->index_str_array = 0;
	}
	return ;
}

void	i_str_list_no_0(t_parsing *parse_list, int nb)
{
	char	temp;

	parse_list->tkns_list->next = calloc(1, sizeof(t_tkns));
	parse_list->tkns_list->next->prev = parse_list->tkns_list;
	(parse_list->tkns_list->next)->start = parse_list->tkns_list->start;
	parse_list->tkns_list = parse_list->tkns_list->next;
	parse_list->tkns_list->dollar_sign = false;
	parse_list->tkns_list->flags = 400;
	parse_list->tkns_list->tkn = calloc(ft_strlen_delim(
				(parse_list->tkns_array[parse_list->index_array]))
			+ 1, sizeof(char));
	parse_list->i_str_list = 0;
	temp = parse_list->tkns_array[parse_list->index_array]
	[parse_list->index_str_array];
	while (*parse_list->tkns_array[parse_list->index_array] != temp)
		parse_list->tkns_array[parse_list->index_array]++;
	parse_list->i_str_list = 0;
	parse_list->index_str_array = 0;
	parse_list->tkns_list->tkn[parse_list->i_str_list]
		= parse_list->tkns_array[parse_list->index_array]
	[parse_list->index_str_array];
	parse_list->i_str_list++;
	still_no_0(parse_list, nb);
	return ;
}

void	still_no_0(t_parsing *parse_list, int nb)
{
	int	i;

	i = 1;
	if (nb > 1)
	{
		parse_list->tkns_list->tkn[parse_list->i_str_list]
			= parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array];
		parse_list->i_str_list++;
		while (i < nb)
		{
			parse_list->tkns_array[parse_list->index_array]++;
			i++;
		}
	}
	parse_list->tkns_list->tkn[parse_list->i_str_list] = '\0';
	parse_list->tkns_array[parse_list->index_array]++;
	if (parse_list->tkns_array[parse_list->index_array]
		[parse_list->index_str_array] != '\0')
	{
		parse_list->tkns_list->next = calloc(1, sizeof(t_tkns));
		parse_list->tkns_list->next->prev = parse_list->tkns_list;
		(parse_list->tkns_list->next)->start = parse_list->tkns_list->start;
		parse_list->tkns_list = parse_list->tkns_list->next;
		parse_list->tkns_list->dollar_sign = false;
		parse_list->tkns_list->flags = 400;
		parse_list->tkns_list->tkn = calloc(ft_strlen_delim(
					(parse_list->tkns_array[parse_list->index_array]))
				+ 1, sizeof(char));
		parse_list->i_str_list = 0;
		parse_list->index_str_array = 0;
	}
	return ;
}

int	ft_strlen_delim(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '&' || str[i] != '|' || str[i] != '<')
	{
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (i);
}

int	check_tokens(t_parsing *parse_list)
{
	parse_list->tkns_list = parse_list->tkns_list->start;
	while (parse_list->tkns_list->next != NULL)
	{
		if ((!ft_strncmp(parse_list->tkns_list->tkn, "\\", 1)))
			printf("do the wait for input or do the error ig,"
				"idk i dont even work here\n");
		else if (ft_strchr(parse_list->tkns_list->tkn, '$'))
			parse_list->tkns_list->dollar_sign = true;
		else if ((!ft_strncmp(parse_list->tkns_list->tkn, "&&\0", 3)))
			put_ampers_props(parse_list);
		else if ((!ft_strncmp(parse_list->tkns_list->tkn, "|", 1)))
			put_pipe_props(parse_list);
		else if ((!ft_strncmp(parse_list->tkns_list->tkn, "<", 1))
			|| (!ft_strncmp(parse_list->tkns_list->tkn, ">", 1)))
			put_redirect_props(parse_list);
		else if (parse_list->tkns_list->argv_pos == 0)
			argv0(parse_list);
		else if (parse_list->tkns_list->flags == 400)
			parse_list->tkns_list->flags = 2;
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	return (0);
}

int	start_parse(char *line)
{
	t_parsing	*parse_list;

	parse_list = calloc(1, sizeof(t_parsing));
	parse_list->index_array = 0;
	parse_list->index_str_array = 0;
	parse_list->i_str_list = 0;
	parse_list->tkns_array = split(line);
	if (parse_list->tkns_array == NULL)
		return (0);
	if (parse_list->tkns_array)
		put_on_the_props(parse_list);
	parse_list->tkns_list = parse_list->tkns_list->start;
	while (parse_list->tkns_list->tkn != NULL)
	{
		printf("tkns = %s, arg pos = %d, flags = %d, is dollar sign? = %d\n",
			parse_list->tkns_list->tkn,
			parse_list->tkns_list->argv_pos, parse_list->tkns_list->flags,
			parse_list->tkns_list->dollar_sign);
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	return (0);
}

int	put_on_the_props(t_parsing *parse_list)
{
	parse_list->tkns_list = calloc(1, sizeof(t_tkns));
	parse_list->tkns_list->dollar_sign = false;
	parse_list->tkns_list->flags = 400;
	parse_list->tkns_list->prev = NULL;
	parse_list->tkns_list->start = parse_list->tkns_list;
	assign_the_list(parse_list);
	parse_list->tkns_list->next = NULL;
	parse_list->tkns_list->tkn = NULL;
	parse_list->tkns_list = parse_list->tkns_list->start;
	check_tokens(parse_list);
	return (0);
}

int	argv0(t_parsing *parse_list)
{
	if (!ft_strncmp(parse_list->tkns_list->tkn, "<\0", 2))
		put_redirect_props(parse_list);
	else if (!ft_strncmp(parse_list->tkns_list->tkn, "&", 1)
		|| (!ft_strncmp(parse_list->tkns_list->tkn, "|", 1)))
		printf("DunderShell: syntax error near unexpected token `%.2s'\n",
			parse_list->tkns_list->tkn);
	else
	{
		printf("do_the_exe_baby(parse_list) tkn %s, argv pos %d, flags %d\n",
			parse_list->tkns_list->tkn, parse_list->tkns_list->argv_pos,
			parse_list->tkns_list->flags);
	}
	return (0);
}

int	put_ampers_props(t_parsing *parse_list)
{
	parse_list->tkns_list->flags = 3;
	if (parse_list->tkns_list->next != NULL)
		parse_list->tkns_list->next->flags = 0;
	return (0);
}

int	put_pipe_props(t_parsing *parse_list)
{
	if (parse_list->tkns_list->tkn != NULL)
	{
		if (!ft_strncmp(parse_list->tkns_list->tkn, "|\0", 2))
		{
			parse_list->tkns_list->flags = 5;
			parse_list->tkns_list->next->flags = 0;
		}
		else if (!ft_strncmp(parse_list->tkns_list->tkn, "||\0", 3))
		{
			parse_list->tkns_list->flags = 4;
			parse_list->tkns_list->next->flags = 0;
		}
	}
	return (0);
}

int	put_redirect_props(t_parsing *parse_list)
{
	if (parse_list->tkns_list->next->tkn != NULL)
	{
		if (!ft_strncmp(parse_list->tkns_list->tkn, "<\0", 2))
		{
			parse_list->tkns_list->flags = 1;
			parse_list->tkns_list->next->flags = 7;
		}
		else if (!ft_strncmp(parse_list->tkns_list->tkn, "<<\0", 3))
		{
			parse_list->tkns_list->flags = 8;
			parse_list->tkns_list->next->flags = 9;
		}
		else if (!ft_strncmp(parse_list->tkns_list->tkn, ">\0", 2))
		{
			parse_list->tkns_list->flags = 10;
			parse_list->tkns_list->next->flags = 11;
		}
		else if (!ft_strncmp(parse_list->tkns_list->tkn, ">>\0", 3))
		{
			parse_list->tkns_list->flags = 12;
			parse_list->tkns_list->next->flags = 11;
		}
	}
	else
	{
		parse_list->tkns_list->flags = 69;
		printf("DunderShell: syntax error near unexpected token `newline' \n");
		return (1);
	}
	return (0);
}

int	cnt_tokens(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}
