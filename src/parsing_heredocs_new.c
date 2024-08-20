/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredocs_new.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adube <adube@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:36:08 by adube             #+#    #+#             */
/*   Updated: 2024/08/19 14:49:05 by adube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	do_pipe(t_parsing *parse_list)
{
	if (check_pipe_name(parse_list->tkns_list) == 1)
		return (2);
	return (0);
}

static t_parsing	*helper1(t_parsing *p_l)
{
	int	ret;

	ret = 0;
	if (p_l->tkns_list->tok_type == TRUNC)
		ret = do_trunc(p_l);
	if (p_l->tkns_list->tok_type == IN_OUT)
		ret = do_in_out(p_l);
	if (p_l->tkns_list->tok_type == INPUT)
		ret = do_input(p_l);
	if (p_l->tkns_list->tok_type == APPEND)
		ret = do_append(p_l);
	if (p_l->tkns_list->tok_type == PIPE)
		ret = do_pipe(p_l);
	if (p_l->tkns_list->tok_type == SPECIAL_PIPE
		|| p_l->tkns_list->tok_type == OUTPUT)
		ret = do_output(p_l);
	if (ret == 1 || ret == 2)
		return (p_l);
	return (NULL);
}

bool	check_meta(t_parsing *p_l)
{
	if (p_l->nb_of_pipes != 0 && ((p_l->cmd_count + 1) > p_l->nb_of_pipes)
		&& (p_l->tkns_list->next && p_l->tkns_list->next->tok_type == CMD)
		&& (p_l->tkns_list->tok_type == PIPE || ((p_l->tkns_list->next->next)
				&& p_l->tkns_list->next->next->tok_type == PIPE)))
		return (true);
	return (false);
}

t_parsing	*metachar_utils(t_parsing *p_l)
{
	if (p_l->tkns_list->tok_type == PIPE)
		p_l->nb_of_pipes += 1;
	if (p_l->tkns_list->tok_type == CMD)
		p_l->cmd_count += 1;
	if (p_l->tkns_list->tok_type == INPUT || p_l->tkns_list->tok_type == OUTPUT
		|| p_l->tkns_list->tok_type == APPEND)
		if (p_l->tkns_list->next && p_l->tkns_list->next->tok_type == CMD)
			p_l->tkns_list->next->tok_type = EMPTY;
	if (p_l->tkns_list->tok_type == PIPE)
	{
		while (p_l->tkns_list->next
			&& p_l->tkns_list->next->tok_type == CMD && p_l->cmd_count != 0)
		{
			p_l->tkns_list->next->tok_type = ARG;
			if (p_l->tkns_list->next)
				p_l->tkns_list = p_l->tkns_list->next;
		}
	}
	if (check_meta(p_l) == true)
		p_l->tkns_list->next->tok_type = ARG;
	if (p_l->tkns_list->tok_type == TRUNC && p_l->tkns_list->next)
		p_l->tkns_list->next->tok_type = TRUNC_ARG;
	return (p_l);
}

/**
 * @brief

 * @param parse_list
 * @return t_parsing*
 */
t_parsing	*check_metachar(t_parsing *p_l)
{
	t_parsing	*tmp;

	p_l->start = p_l->tkns_list;
	while (p_l->tkns_list != NULL)
	{
		if ((p_l->tkns_list->tok_type == APPEND || p_l->tkns_list->tok_type \
				== INPUT || p_l->tkns_list->tok_type == OUTPUT)
			&& p_l->tkns_list->next != NULL)
			p_l->tkns_list->next->tok_type = EMPTY;
		p_l->tkns_list = p_l->tkns_list->next;
	}
	p_l->tkns_list = p_l->start;
	while (p_l->tkns_list)
	{
		tmp = helper1(p_l);
		if (tmp)
			return (tmp);
		p_l = metachar_utils(p_l);
		if (p_l->tkns_list->next)
			p_l->tkns_list = p_l->tkns_list->next;
		else
			break ;
	}
	p_l->tkns_list = p_l->start;
	return (p_l);
}
