#include "../include/minishell.h"

static int	do_pipe(t_parsing *parse_list)
{
	if (check_pipe_name(parse_list->tkns_list) == 1)
		return (1);
	return (0);
}

static t_parsing	*helper1(t_parsing *p_l)
{
	if (p_l->tkns_list->tok_type == TRUNC)
	{
		if (do_trunc(p_l) == 1)
			return (p_l);
		else
			return (NULL);
	}
	if (p_l->tkns_list->tok_type == IN_OUT)
		if (do_in_out(p_l) == 1)
			return (p_l);
	if (p_l->tkns_list->tok_type == INPUT)
		if (do_input(p_l) == 1)
			return (p_l);
	if (p_l->tkns_list->tok_type == APPEND)
		if (do_append(p_l) == 1)
			return (p_l);
	if (p_l->tkns_list->tok_type == PIPE)
		if (do_pipe(p_l) == 1)
			return (p_l);
	if (p_l->tkns_list->tok_type == SPECIAL_PIPE
		|| p_l->tkns_list->tok_type == OUTPUT)
		if (do_output(p_l) == 1)
			return (p_l);
	return (NULL);
}

t_parsing	*metachar_utils(t_parsing *p_l)
{
	if (p_l->tkns_list->tok_type == PIPE)
		p_l->nb_of_pipes += 1;
	if ((p_l->tkns_list->tok_type == OUTPUT
			|| p_l->tkns_list->tok_type == APPEND)
		|| p_l->tkns_list->tok_type == PIPE)
	{
		while (p_l->tkns_list->next
			&& p_l->tkns_list->next->tok_type == CMD)
		{
			p_l->tkns_list->next->tok_type = ARG;
			p_l->tkns_list = p_l->tkns_list->next;
		}
	}
	if (p_l->tkns_list->tok_type == INPUT)
		if (p_l->tkns_list->next && p_l->tkns_list->next->tok_type == CMD)
			p_l->tkns_list->next->tok_type = ARG;
	if (p_l->tkns_list->tok_type == TRUNC)
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
