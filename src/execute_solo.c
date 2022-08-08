#include "../include/minishell.h"
#include <stdio.h>

void	exec_solo_child(t_parsing *parse, char **cmd, char ***env)
{
	if (parse->infile != 0)
	{
		dup2(parse->infile, 0);
		close(parse->infile);
	}
	if (parse->outfile != 1)
	{
		dup2(parse->outfile, 1);
		close(parse->outfile);
	}
	look_for_builtins(&cmd, env, parse);
	if (parse->b_in == false && access (cmd[0], X_OK) == 0)
	{
		execve(cmd[0], cmd, *(env));
		exit(1);
	}
	else if (parse->b_in == false)
	{
		parse_and_exec_cmd_shell(cmd, *(env));
		exit (1);
	}
	exit (0);
}

// for(int i = 0;cmd[i];i++)
// 	printf("CMD[%d] = %s\n",i, cmd[i]);
void	execute_solo(char **cmd, char ***env, t_parsing *parse)
{
	int	pid;
	if (parse->infile != -1)
	{
		if (look_for_exit(cmd))
			mini_exit(cmd, parse);
		else if (look_for_export(cmd))
			mini_export(cmd, env, parse);
		else if (look_for_unset(cmd))
			mini_unset(cmd, env, parse);
		else if (look_for_cd(cmd))
			mini_cd(cmd, env, parse);
		else if (look_for_echo(cmd))
			mini_echo(cmd,parse);
		else
		{
			pid = fork();
			if (pid == 0)
				exec_solo_child(parse, cmd, env);
		}
	}
	if (parse->infile != -1)
		parse->pids[0] = pid;
}
