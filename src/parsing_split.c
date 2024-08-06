/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adube <adube@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:35:32 by adube             #+#    #+#             */
/*   Updated: 2024/08/06 10:11:05 by adube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_toktype_utils(t_tkns *matrix)
{
	if (matrix->data[0] == '<' && matrix->data[1] == '<'
		&& matrix->data[2] == '\0')
		matrix->tok_type = TRUNC;
	else if (matrix->data[0] == '<' && matrix->data[1] == '>'
		&& matrix->data[2] == '\0')
		matrix->tok_type = IN_OUT;
	else if (matrix->data[0] == '<' && matrix->data[1] == '\0')
		matrix->tok_type = INPUT;
	else
		matrix->tok_type = EMPTY;
	return (matrix->tok_type);
}

t_tkns	*set_toktype(t_tkns *matrix, t_parsing *p_l)
{
	while (matrix -> next)
		matrix = matrix -> next;
	if (p_l->quotes == false || (p_l->quotes == true
			&& (p_l->index < p_l->quote_start || p_l->index > p_l->quote_end)))
	{
		if (matrix->data[0] == '<')
			matrix->tok_type = check_toktype_utils(matrix);
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
	}
	if (matrix->tok_type == EMPTY)
		matrix->tok_type = CMD;
	return (matrix);
}

int	how_split(t_parsing *p_l, char *s)
{
	int	i;

	i = p_l->index;
	if (p_l->quotes == true && s[p_l->index - 1] == p_l->quote_type)
	{
		while (ft_isspace(s[i]) == true)
			i++;
		if ((p_l->quotes == true && s[i] == p_l->quote_type))
			p_l->index = i;
		return (p_l->index);
	}
	while ((ft_isspace(s[p_l->index]) == true && (p_l->index \
			< p_l->quote_start || p_l->index > p_l->quote_end))
		|| (p_l->quotes == true && s[p_l->index] == p_l->quote_type))
		p_l->index++;
	return (p_l->index);
}

/**
 * @brief 
 * 
 * @param s 
 * @param parse_list 
 * @return t_parsing* 
 */
t_parsing	*new_split(char *s, t_parsing *p_l)
{
	p_l->index = 0;
	p_l->start = NULL;
	p_l->quote_count = 0;
	while (ft_isspace(s[p_l->index]) == true)
		p_l->index += 1;
	while (s[p_l->index])
	{
		if (check_double_redir(s, p_l) == true)
			init_redir_node_two_char(s, p_l);
		else if (check_in_out_file(s, p_l) == true)
			init_redir_node_one_char(s, p_l);
		else
			init_command_node(s, p_l);
		if (p_l->start == NULL)
		{
			p_l->old = p_l->tkns_list;
			p_l->start = p_l->tkns_list->next;
		}
		p_l->index = how_split(p_l, s);
	}
	p_l->tkns_list = p_l->start;
	return (p_l);
}
