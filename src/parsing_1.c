/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adube <adube@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:36:54 by adube             #+#    #+#             */
/*   Updated: 2024/07/29 10:35:25 by adube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// loop over the line to see if its only spaces 
// once you meet something else then a space return false
bool	is_empty(char *line)
{
	while (*line)
	{
		if (*line != ' ')
			return (false);
		line++;
	}
	if (*line == '\0')
		return (true);
	else
		return (false);
}

t_parsing	*start_parse(char *line, int status)
{
	t_parsing	*parse_list;

	if (is_empty(line))
		return (NULL);
	parse_list = arena_alloc(&g_ex.arena, sizeof(t_parsing));
	init_master_list(parse_list, status);
	parse_list = quotes_line(line, parse_list);
	line = expand_var(line, *&parse_list);
	if (parse_list->quotes == true)
		line = del_quotes(*&parse_list, line);
	parse_list->tkns_list = init_list(line);
	parse_list = new_split(line, parse_list);
	parse_list = check_metachar(parse_list);
	parse_list->pids = arena_alloc(&g_ex.arena,
			(parse_list->nb_of_pipes + 1) * sizeof(int));
	parse_list = get_cmd(parse_list);
	if (parse_list->nb_of_pipes != 0)
		parse_list->pipes_args = get_argarray(parse_list);
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
	int	i;

	i = 0;
	parse_list->vector_cmd[parse_list->i_vect]
		= arena_alloc(&g_ex.arena, ft_strlen(str) + 1);
	while (parse_list && parse_list->tkns_list
		&& str[i] != '\0' && (parse_list->i_vect < parse_list->cmd_count))
	{
		parse_list->vector_cmd[parse_list->i_vect][i] = str[i];
		i++;
	}
	parse_list->i_vect++;
	return (parse_list);
}

char	*str_del_one(char *str)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = arena_alloc(&g_ex.arena, ft_strlen(str) - 1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n' && str[i + 1] == '\0')
			break ;
		new_str[i] = str[i];
		i++;
	}
	return (new_str);
}
