#include "../include/minishell.h"

void	wait_for_pids(t_parsing *parse)
{
	int	i;

	i = 0;
	while (i <= parse->nb_of_pipes)
	{
		waitpid(parse->pids[i], &parse->ex->cmd_rtn, 0);
		i++;
	}
	if (parse->infile != 0)
		close(parse->infile);
	free(parse->pids);
	printf("This is &parse->ex->cmd_rtn %d\n", parse->ex->cmd_rtn);
}