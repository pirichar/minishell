#include "../include/minishell.h"

int	check_tokens(t_parsing *parse_list)
{
	parse_list->tkns_list = parse_list->tkns_list->start;
	while (parse_list->tkns_list->next != NULL)
	{
		if (ft_strchr(parse_list->tkns_list->tkn, '$'))
			parse_list->tkns_list->dollar_sign = true;
		else if ((!ft_strncmp(parse_list->tkns_list->tkn, "&&\0", 3)))
			put_ampers_props(parse_list);
		else if ((!ft_strncmp(parse_list->tkns_list->tkn, "|", 1)))
			put_pipe_props(parse_list);
		else if ((!ft_strncmp(parse_list->tkns_list->tkn, "<", 1))
			|| (!ft_strncmp(parse_list->tkns_list->tkn, ">", 1)))
			put_redirect_props(parse_list);
		else if (parse_list->tkns_list->argv_pos == 0)
		{
			parse_list->tkns_list->flags = 0;
			printf("do_the_exe\n");
		}
		else if (parse_list->tkns_list->flags == 400)
			parse_list->tkns_list->flags = 2;
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	parse_list->tkns_list = parse_list->tkns_list->start;
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

int	argv0(t_parsing *parse_list)
{
	if (!ft_strncmp(parse_list->tkns_list->tkn, "<\0", 2))
		put_redirect_props(parse_list);
	else if (!ft_strncmp(parse_list->tkns_list->tkn, "&", 1)
		|| (!ft_strncmp(parse_list->tkns_list->tkn, "|", 1)))
		printf("DunderShell: syntax error near unexpected token `%.2s'\n",
			parse_list->tkns_list->tkn);
	return (0);
}
