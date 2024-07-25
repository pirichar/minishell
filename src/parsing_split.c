/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adube <adube@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:35:32 by adube             #+#    #+#             */
/*   Updated: 2024/07/25 11:35:34 by adube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tkns	*set_toktype(t_tkns *matrix)
{
	while (matrix -> next)
		matrix = matrix -> next;
	if (matrix->data[0] == '<' && matrix->data[1] == '<'
		&& matrix->data[2] == '\0')
		matrix->tok_type = TRUNC;
	else if (matrix->data[0] == '<' && matrix->data[1] == '>'
		&& matrix->data[2] == '\0')
		matrix->tok_type = IN_OUT;
	else if (matrix->data[0] == '<' && matrix->data[1] == '\0')
		matrix->tok_type = INPUT;
	else if (matrix->data[0] == '>' && matrix->data[1] == '>'
		&& matrix->data[2] == '\0')
		matrix->tok_type = APPEND;
	else if (matrix->data[0] == '>' && matrix->data[1] == '|'
		&& matrix->data[2] == '\0')
		matrix->tok_type = SPECIAL_PIPE;
	else if (matrix->data[0] == '>' && matrix->data[1] == '\0')
		matrix->tok_type = OUTPUT;
	else if (matrix->data[0] == '|' && matrix->data[1] == '\0')
		matrix->tok_type = PIPE;
	else
		matrix->tok_type = CMD;
	return (matrix);
}

/**
 * @brief 
 * 
 * @param s 
 * @param parse_list 
 * @return t_parsing* 
 */
t_parsing	*new_split(char *s, t_parsing *parse_list)
{
	parse_list->index = 0;
	parse_list->start = NULL;
	while (ft_isspace(s[parse_list->index]) == true)
		parse_list->index += 1;
	while (s[parse_list->index])
	{
		if (check_double_redir(s, parse_list))
			init_redir_node_two_char(s, parse_list);
		else if (check_in_out_file(s, parse_list))
			init_redir_node_one_char(s, parse_list);
		else
			init_command_node(s, parse_list);
		if (parse_list->start == NULL)
		{
			parse_list->old = parse_list->tkns_list;
			parse_list->start = parse_list->tkns_list->next;
		}
		while ((ft_isspace(s[parse_list->index]) == true)
			|| (parse_list->quotes == true
				&& s[parse_list->index] == parse_list->quote_type))
			parse_list->index += 1;
	}
	parse_list->tkns_list = parse_list->start;
	return (parse_list);
}
