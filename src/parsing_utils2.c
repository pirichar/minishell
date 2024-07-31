/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandrinedube <alexandrinedube@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:45:17 by alexandrine       #+#    #+#             */
/*   Updated: 2024/07/31 12:49:31 by alexandrine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool ft_isredir(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return true;
	else
		return false;
}

t_parsing	*empty_quotes(char *line, t_parsing *p_l)
{
	char	*new_line;
	int		i;
	int		y;

	i = 0;
	y = 0;
	new_line = arena_alloc(&g_ex.arena, MAX_INPUT);
	while (line[i])
	{
		if(p_l->quote_start == i && p_l->quote_start + 1 == p_l->quote_end)
		{ 
			new_line[y++] = line[i++];
			new_line[y] = ' ';
			y++;
			p_l->quote_end += 1; 
		}
		new_line[y] = line[i];
		i ++;
		y++;
	}
	new_line[y] = '\0';
	return (p_l);
}