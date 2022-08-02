#include "../include/minishell.h"

void	wait_for_pids(t_parsing *parse)
{
	int	i;

	i = 0;
	while (i <= parse->nb_of_pipes)
	{
		waitpid(parse->pids[i], &parse->status, 0);
		i++;
	}
	if (parse->infile != 0)
		close(parse->infile);
	free(parse->pids);
}