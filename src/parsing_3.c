/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adube <adube@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:36:23 by adube             #+#    #+#             */
/*   Updated: 2024/08/19 13:54:38 by adube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	helper_get_arg(t_parsing	*parse_list, int i, char ***tab_tab)
{
	int	y;
	int	z;

	y = 0;
	z = 0;
	while (parse_list->tkns_list->tok_type == ARG)
	{
		z = 0;
		tab_tab[i][y] = arena_alloc(&g_ex.arena,
				ft_strlen(parse_list->tkns_list->data + 1));
		while (parse_list->tkns_list->data[z] != '\0')
		{
			tab_tab[i][y][z] = parse_list->tkns_list->data[z];
			z++;
		}
		tab_tab[i][y][z] = '\0';
		if (parse_list->tkns_list->next != NULL
			&& parse_list->tkns_list->next->tok_type == ARG)
		{
			y++;
			parse_list->tkns_list = parse_list->tkns_list->next;
		}
		else
			break ;
	}
}

char	***get_argarray(t_parsing *p_l)
{
	char	***tab_tab;

	tab_tab = arena_alloc(&g_ex.arena,
			(p_l->nb_of_pipes + 1) * sizeof(char **));
	while (p_l->tkns_list != NULL)
	{
		if ((p_l->tkns_list->tok_type == ARG
				&& p_l->tkns_list->tok_type == TRUNC)
			|| (p_l->tkns_list->tok_type == TRUNC_ARG
				&& p_l->tkns_list->tok_type == ARG))
			p_l->nb_pipearg--;
		if (p_l->tkns_list->tok_type == ARG
			&& p_l->tab_i < (p_l->nb_of_pipes))
		{
			tab_tab[p_l->tab_i] = prep_tab(p_l->tkns_list);
			helper_get_arg(p_l, p_l->tab_i, tab_tab);
			p_l->tab_i++;
			p_l->nb_pipearg++;
		}
		if (p_l->tkns_list->next != NULL)
			p_l->tkns_list = p_l->tkns_list->next;
		else
			break ;
	}
	return (tab_tab);
}

char	*search_env(char *s, int search, t_parsing *p_list)
{
	p_list->p_x = 0;
	p_list->p_start = search;
	while (g_ex.new_env[p_list->p_x])
	{
		p_list->p_y = 0;
		search = p_list->p_start;
		while (g_ex.new_env[p_list->p_x][p_list->p_y] && s[search] != '\0'
			&& ft_isspace(s[search]) == false)
		{
			if (s[search] != g_ex.new_env[p_list->p_x][p_list->p_y])
				break ;
			if ((ft_isspace(s[search + 1]) == true || s[search + 1] == '\0'
					|| s[search + 1] == 34 || s[search + 1] == 39)
				&& g_ex.new_env[p_list->p_x][p_list->p_y + 1] == '=')
			{
				p_list->index += p_list->p_y + 2;
				p_list->to_skip = p_list->p_y + 2;
				return (g_ex.new_env[p_list->p_x]);
			}
			p_list->p_y++;
			search++;
		}
		p_list->p_x++;
	}
	return (NULL);
}

char	*joining(char *s1, char *s2, t_parsing *parse_list)
{
	char	*str;
	int		j;
	int		i;

	i = 0;
	j = parse_list->to_skip;
	if (!s1)
		return (s2);
	str = arena_alloc(&g_ex.arena, MAX_INPUT);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	if (!s2)
	{
		parse_list->new_i = i;
		return (str);
	}
	while (s2[j])
		str[i++] = s2[j++];
	parse_list->new_i = i;
	return (str);
}

//when type single quote ignore (while) until next single quote is found

char	*expand_var(char *line, t_parsing *p_l)
{
	p_l->p_new = arena_alloc(&g_ex.arena, MAX_INPUT);
	p_l = empty_quotes(*&p_l->p_new, p_l);
	while (line[p_l->index] != '\0')
	{
		if (line[p_l->index] == '$' && line[p_l->index + 1] != '\0'
			&& ft_isspace(line[p_l->index + 1]) == false)
		{
			if ((p_l->quotes == false) || (p_l->quotes == true && ((p_l->index
							< p_l->quote_start || p_l->index > p_l->quote_end)
						|| (p_l->quote_type == 34
							&& (p_l->index > p_l->quote_start
								|| p_l->index < p_l->quote_end)))))
			{
				p_l->p_new = joining(p_l->p_new, search_env(line,
							p_l->index + 1, p_l), *&p_l);
				p_l = expand_return(p_l, line);
			}
		}
		if ((p_l->quotes == true && p_l->index == p_l->quote_end)
			&& (line[p_l->index] == p_l->quote_type))
			p_l->quote_end = p_l->new_i;
		if (line[p_l->index] != '\0')
			p_l->p_new [p_l->new_i++] = line[p_l->index++];
	}
	return (p_l->p_new);
}
