/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandrinedube <alexandrinedube@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:36:31 by adube             #+#    #+#             */
/*   Updated: 2024/07/29 14:31:51 by alexandrine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_parsing	*get_cmd(t_parsing *parse_list)
{
	parse_list->cmd_count
		= count_cmd(parse_list->tkns_list);
	parse_list->vector_cmd
		= arena_alloc(&g_ex.arena,
			(parse_list->cmd_count + 1) * sizeof(char *));
	parse_list->start = parse_list->tkns_list;
	while (parse_list->tkns_list != NULL
		&& parse_list->tkns_list->data != NULL)
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
	parse_list->quoteadd = 0;
	parse_list->bin_do_not_wait = false;
	parse_list->quote_type = EMPTY;
	parse_list->cmd_count = 0;
	parse_list->nb_of_pipes = 0;
	parse_list->to_skip = 0;
	parse_list->index = 0;
	parse_list->new_i = 0;
	parse_list->pids = 0;
	parse_list->file
		= open("./div/here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
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

char	*del_quotes(t_parsing *parse_list, char *line)
{
	int		i;
	int		y;
	char	*newline;

	i = 0;
	y = 0;
	newline = arena_alloc(&g_ex.arena, ft_strlen(line) * sizeof(char *));
	while (line[i] != '\0')
	{
		if (((parse_list->quotes == true && line[i] == parse_list->quote_type)
				&& (i != parse_list->quote_start && i != parse_list->quote_end))
			|| (line[i] != parse_list->quote_type))
		{
			newline[y] = line[i];
			y++;
		}
		else
			parse_list->quote_count++;
		i++;
	}
	parse_list->quote_end = parse_list->quote_end - parse_list->quote_count;
	return (newline);
}

char	**prep_tab(t_tkns *tkns_list)
{
	char	**tab;
	int		count;

	count = 0;
	while (tkns_list->tok_type != PIPE)
	{
		count++;
		if (tkns_list->next != NULL)
			tkns_list = tkns_list->next;
		else
			break ;
	}
	tab = arena_alloc(&g_ex.arena, (count + 1) * sizeof(char *));
	return (tab);
}
