/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredocs_new2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandrinedube <alexandrinedube@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:36:02 by adube             #+#    #+#             */
/*   Updated: 2024/07/31 12:47:51 by alexandrine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	do_in_out(t_parsing *parse_list)
{
	if (check_file_and_delim_name(parse_list->tkns_list) == 1)
		return (1);
	return (0);
}

/**
 * @brief 

 * @param parse_list 
 * @return int 
 */
int	do_input(t_parsing *parse_list)
{
	if (check_file_and_delim_name(parse_list->tkns_list) == 1)
		return (1);
	if (parse_list->infile != 0 && parse_list->infile != -1)
		close(parse_list->infile);
	parse_list->infile = open(parse_list->tkns_list->next->data, O_RDONLY);
	if (parse_list->infile == -1)
		fprintf(stderr, "Could not open input file\n");
	return (0);
}

int	do_append(t_parsing *parse_list)
{
	if (check_file_and_delim_name(parse_list->tkns_list) == 1)
		return (1);
	parse_list->outfile = open(parse_list->tkns_list->next->data,
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (parse_list->outfile == -1)
	{
		fprintf(stderr, "MINISHELL: Could not open output file\n");
		return (1);
	}
	return (0);
}

int	do_output(t_parsing *parse_list)
{
	if (check_file_and_delim_name(parse_list->tkns_list) == 1)
		return (1);
	parse_list->outfile = open(parse_list->tkns_list->next->data,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (parse_list->outfile == -1)
	{
		fprintf(stderr, "MINISHELL: Could not open output file\n");
		return (1);
	}
	return (0);
}
