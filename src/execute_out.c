#include "../include/minishell.h"

static void	exec_out_child(int *fds[2], t_parsing *parse, char **cmd, char **env)
{
	dup2(*(fds[0]), 0);
	close(*(fds[0]));
	if (parse->outfile != 1)
	{
		dup2(*(fds[1]), 1);
		close(*(fds[1]));
	}
	look_for_builtins(&cmd, &env, parse);
	if (parse->b_in == false && access(cmd[0], X_OK) == 0)
	{
		execve(cmd[0], cmd, env);
		exit(1);
	}
	else if (parse->b_in == false)
	{
		parse_and_exec_cmd_shell(cmd, env);
		exit(1);
	}
	else
		exit(0);
}

/*
	Execute out function was created to respect the limit of inputs
	I was using only execute at first and had to switch it around
*/
//à mettre au début de la fonction entre pid et 
//le pipe pour voir ce qui est passé à la fonction
// printf("WITHIN EXECUTE_OUT\n");
// for(int i = 0;cmd[i];i++)
// 	printf("CMD[%d] = %s\n", i, cmd[i]);
void	execute_out(char **cmd, int fds[2], char **env, t_parsing *parse)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		exec_out_child(&fds, parse, cmd, env);
	close(fds[0]);
	if (parse->outfile != 1)
		close(fds[1]);
	parse->pids[parse->nb_of_pipes] = pid;
}
