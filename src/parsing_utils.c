/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandrinedube <alexandrinedube@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:35:12 by adube             #+#    #+#             */
/*   Updated: 2024/07/31 12:50:34 by alexandrine      ###   ########.fr       */
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

bool	check_cmd_quotes(char *s, t_parsing *p_l, int index)
{
	int	i;

	if (p_l->quotes == true && index != p_l->index
		&& p_l->index != 0 && p_l->index > index && p_l->index >= p_l->quote_start
			&& p_l->index <= p_l->quote_end)
		i = p_l->index;
	else
		i = index;
	if (p_l->quotes == true
		&& (i >= p_l->quote_start
			&& i <= p_l->quote_end) && s[i] == p_l->quote_type
		&& ft_isspace(s[i + 1]))
		return (false);
	if (p_l->quotes == true
		&& (i >= p_l->quote_start
			&& i <= p_l->quote_end))
		return (true);
	if (p_l->quotes == true
		&& (i < p_l->quote_start
			|| i > p_l->quote_end) && ft_isspace(s[i]) == false && ft_isredir(s[i]) == false)
		return (true);
	if ((p_l->quotes == false)
		&& (ft_isspace(s[i]) == false) && ft_isredir(s[i]) == false)
		return (true);
	return (false);
}
