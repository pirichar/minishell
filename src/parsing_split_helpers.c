/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adube <adube@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:35:38 by adube             #+#    #+#             */
/*   Updated: 2024/08/01 13:32:57 by adube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief First we check if we find << >> or <| or >|
			Then we look if there is quotes or not
			If not we just execute the command
			If yes we check if the index is smaller then the start 
			or the index is bigger then the end
 * 
 * @param s 
 * @param parse_list 
 * @return true 
 * @return false 
 */
bool	check_double_redir(char *s, t_parsing *parse_list)
{
	if (((s[parse_list->index] == '<'
				|| s[parse_list->index] == '>')
			&& (s[parse_list->index + 1] == '<'
				|| s[parse_list->index + 1] == '>'
				|| s[parse_list->index + 1] == '|'))
		&& ((parse_list->quotes == false) || (parse_list->quotes == true
				&& (parse_list->index < parse_list->quote_start
					|| parse_list->index > parse_list->quote_end))))
		return (true);
	return (false);
}

/**
 * @brief First we look if we are a < > or a |
			Then we do the same mechanism as the previous
			function to see if we are within a quote
 * 
 * @param s 
 * @param parse_list 
 * @return true 
 * @return false 
 */

bool	check_in_out_file(char *s, t_parsing *parse_list)
{
	if ((s[parse_list->index] == '<'
			|| s[parse_list->index] == '>'
			|| s[parse_list->index] == '|')
		&& ((parse_list->quotes == false) || (parse_list->quotes == true
				&& (parse_list->index < parse_list->quote_start
					|| parse_list->index > parse_list->quote_end))))
		return (true);
	return (false);
}

/**
 * @brief To create a redirection node
			When there is two symbols
			like >> << 
 * @param s 
 * @param parse_list 
 */
void	init_redir_node_two_char(char *s, t_parsing *parse_list)
{
	parse_list->tkns_list->next
		= node_redir(parse_list->tkns_list->next,
			&s[parse_list->index], 2, parse_list);
	parse_list->index += 2;
}

/**
 * @brief To create a redirection node
 			When the node is a redir with only one
			symbol
 * 
 * @param s 
 * @param parse_list 
 */
void	init_redir_node_one_char(char *s, t_parsing *parse_list)
{
	parse_list->tkns_list->next
		= node_redir(parse_list->tkns_list->next,
			&s[parse_list->index], 1, parse_list);
	parse_list->index += 1;
}

/**
 * @brief When the node is a command
 * 
 * @param s 
 * @param parse_list 
 */
void	init_command_node(char *s, t_parsing *parse_list)
{
	parse_list->tkns_list->next
		= make_node(parse_list->tkns_list->next,
			&s[parse_list->index], parse_list);
	parse_list->index
		+= ft_strlen((const char *)parse_list->tkns_list->next->data);
	if (parse_list->quotes == true
		&& parse_list->quoteadd <= parse_list->quote_count)
	{
		parse_list->quoteadd += 1;
		parse_list->index += parse_list->quoteadd;
	}
	if (parse_list->tkns_list->tok_type == CMD)
		parse_list->cmd_count++;
}
