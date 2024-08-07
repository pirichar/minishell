/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_pids.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:41:45 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/25 11:41:46 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if (parse->nb_of_pipes == 0 && parse->bin_do_not_wait == true)
	{
		if (parse->infile != 0 && parse->infile != -1)
			close(parse->infile);
		if (parse->outfile != 1 && parse->outfile != -1)
			close(parse->outfile);
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
		setup_signal_handlers();
	}
}
