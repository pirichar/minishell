/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:39:01 by pirichar          #+#    #+#             */
/*   Updated: 2024/08/03 18:39:19 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Function called at the end of each cycle of minishell
	
* 	PARSING STRUCT
	// free parse_list->tkn->list 
	// free parse->vector->cmd and s_line 
	// free parse->pipe_args
	//free parse->p_new (expand variables)
	// free parse_list

	EXEC
	// free g_ex.line

	Pids are freed in wait for pids
 * 
 * @param parse struct to free
 */
void	ft_clean(t_parsing	**parse)
{
	t_tkns	*tmp;

	if ((*parse) && (*parse)->tkns_list)
	{
		while ((*parse)->tkns_list)
		{
			tmp = (*parse)->tkns_list->next;
			free((*parse)->tkns_list->data);
			free((*parse)->tkns_list);
			(*parse)->tkns_list = tmp;
		}
	}
	if ((*parse) && *(*parse)->vector_cmd)
		free_strrarr((*parse)->vector_cmd);
	if ((*parse) && (*parse)->pipes_args)
	{
		(*parse)->i = 0;
		while ((*parse)->pipes_args[(*parse)->i])
			free_strrarr((*parse)->pipes_args[(*parse)->i++]);
	}
	free ((*parse)->pipes_args);
	free ((*parse)->p_new);
	free ((*parse));
	*parse = NULL;
	free (g_ex.line);
}

/**
 * @brief Function called when the program is closing
	
* 	PARSING STRUCT
	// free parse_list->tkn->list 

	EXEC
	// free g_ex.line
	// free env
	// free ex
 * 
 * @param parse struct to free
 */
void	ft_exit(t_parsing	*parse)
{
	(void)parse;
	free (g_ex.line);
	if (g_ex.fail_heredoc == false)
		free_strrarr(g_ex.new_env);
	arena_log_watermark(&g_ex.arena);
	arena_free(&g_ex.arena);
}

/**
 * @brief 
 * 
 * @param to_exit 
 */
void	clean_and_exit(int to_exit)
{
	arena_free(&g_ex.arena);
	free_strrarr(g_ex.new_env);
	exit (to_exit);
}
