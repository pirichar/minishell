/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adube <adube@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:35:12 by adube             #+#    #+#             */
/*   Updated: 2024/07/25 11:35:15 by adube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_first_token_nodes(t_parsing *parse_list)
{
	parse_list->tkns_list = calloc(1, sizeof(t_tkns));
	parse_list->tkns_list->dollar_sign = false;
	parse_list->tkns_list->prev = NULL;
	parse_list->start = NULL;
	return (0);
}

int	count_cmd(t_tkns *tkns_list)
{
	int	count;

	count = 0;
	while (tkns_list != NULL)
	{
		if (tkns_list->tok_type == CMD)
			count++;
		tkns_list = tkns_list->next;
	}
	return (count);
}

int	check_file_and_delim_name(t_tkns *tkns_list)
{
	if (tkns_list->next != NULL)
	{
		if (ft_strchr("<|>", tkns_list->next->data[0]))
		{
			printf("Dundershell: syntax error near unexpected token `%c'\n",
				tkns_list->next->data[0]);
			return (1);
		}
	}
	if (!tkns_list->next)
	{
		printf("Dundershell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	check_pipe_name(t_tkns *tkns_list) //may 21, should be ok
{
	if (tkns_list->next
		&& tkns_list->next->data[0] == '|')
	{
		printf("Dundershell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (!tkns_list->next)
	{
		printf("Dundershell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

bool	check_cmd_quotes(char *s, t_parsing *parse_list, int index)
{
	int	i;

	if (parse_list->quotes == true && index != parse_list->index
		&& parse_list->index != 0)
		i = parse_list->index;
	else
		i = index;
	if (ft_isspace(s[index]) == true)
		return (false);
	if ((parse_list->quotes == false)
		&& (ft_isspace(s[i]) == false))
		return (true);
	if (parse_list->quotes == true
		&& (i >= parse_list->quote_start
			|| i <= parse_list->quote_end) && s[i] != parse_list->quote_type)
		return (true);
	if ((parse_list->quote_type == 39 && s[i] == 39)
		|| (parse_list->quote_type == 34 && s[i] == 34))
		return (true);
	return (false);
}
