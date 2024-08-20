/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_pids.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adube <adube@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:41:45 by pirichar          #+#    #+#             */
/*   Updated: 2024/08/19 14:35:04 by adube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	close_in_out(t_parsing *parse)
{
	if (parse->infile != 0 && parse->infile != -1)
		close(parse->infile);
	if (parse->outfile != 1 && parse->outfile != -1)
		close(parse->outfile);
}

/**
 * @brief Function from Pipex
			Design to wait for all the pids
			will also close infile
			and free the pids
		This was removed at the end to stop double close of fd
		// if (parse->infile != 0 && parse->infile != -1)
		// 	close(parse->infile);
		// if (parse->outfile != 1 && parse->outfile != -1)
		// 	close(parse->outfile);
 * @param parse struct containing all the info
 */

void	wait_for_pids(t_parsing *parse)
{
	int	i;

	i = 0;
	if ((parse->nb_of_pipes == 0 && parse->bin_do_not_wait == true)
		|| (parse->nb_pipearg == 0 && parse->bin_do_not_wait == true))
	{
		close_in_out(parse);
		setup_signal_handlers();
	}
	else
	{
		while (i <= parse->nb_of_pipes)
		{
			waitpid(parse->pids[i], &g_ex.cmd_rtn, 0);
			if (WIFEXITED(g_ex.cmd_rtn))
				g_ex.status = WEXITSTATUS(g_ex.cmd_rtn);
			i++;
		}
		if (parse->nb_pipearg == 0)
			close_in_out(parse);
		setup_signal_handlers();
	}
}
