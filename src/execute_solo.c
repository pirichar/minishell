#include "../include/minishell.h"
#include <stdio.h>

/**
 * @brief Function made to execute a solo child
 			if parse->infile is not the default
 			(0, which stands for standard input),
			the function redirects the standard input
			to parse->infile using dup2 and
			then closes parse->infile.
			If parse->outfile is not the default
			(1, which stands for standard output),
			the function redirects the standard output
			to parse->outfile using dup2
			and then closes parse->outfile.
 * 
 * @param parse is used for the b_in
 * @param cmd to be processed
 * @param env required by execve
 */
static void	exec_solo_child(t_parsing *parse, char **cmd, char ***env)
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
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (parse->b_in == false && access (cmd[0], X_OK) == 0)
	{
		g_ex.status = execve(cmd[0], cmd, *(env));
		exit(1);
	}
	else if (parse->b_in == false)
	{
		parse_and_exec_cmd_shell(cmd, *(env));
		exit (1);
	}
	exit (0);
}

/**
 * @brief This function is called when nb_of_pipes is 0
			It will try the builtins an run them directly
			If it cant it will then call execute solo child
			This function is called by calling_the_execs_shell
 * 
	// for(int i = 0;cmd[i];i++)
	// 	printf("CMD[%d] = %s\n",i, cmd[i]);
 * @param cmd 
 * @param env 
 * @param parse 
 */
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
			mini_echo(cmd, parse);
		else
		{
			signal(SIGINT, SIG_IGN);
			pid = fork();
			if (pid == 0)
				exec_solo_child(parse, cmd, env);
		}
	}
	if (parse->infile != -1)
		parse->pids[0] = pid;
}
