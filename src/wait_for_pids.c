#include "../include/minishell.h"

/**
 * @brief Function from Pipex
			Design to wait for all the pids
			will also close infile
			and free the pids
 * @param parse struct containing all the info
 */
void	wait_for_pids(t_parsing *parse)
{
	int	i;

	i = 0;
	while (i <= parse->nb_of_pipes)
	{
		waitpid(parse->pids[i], &g_ex.cmd_rtn, 0);
		i++;
	}
	if (parse->infile != 0)
		close(parse->infile);
	setup_signal_handlers();
}
