/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_solo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:43:45 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/25 11:43:46 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Will first try cmd with absolue path, then within the path
			Will finally clean and exit with 1 or 2 depending 
			if a problem was encountered
 * 
 * @param parse 
 * @param env 
 * @param cmd 
 */
static void	process_cmd(t_parsing *parse, char ***env, char **cmd)
{
	if (parse->b_in == false)
	{
		if (access (cmd[0], X_OK) == 0)
		{
			execve(cmd[0], cmd, *(env));
			clean_and_exit(1);
		}
		else
		{
			parse_and_exec_cmd_shell(cmd, *(env));
		}
		clean_and_exit(1);
	}
	clean_and_exit(0);
}

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
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (parse->infile != 0)
	{
		dup2(parse->infile, 0);
		if (parse->infile != -1)
			close(parse->infile);
	}
	if (parse->outfile != 1)
	{
		dup2(parse->outfile, 1);
		if (parse->outfile != -1)
			close(parse->outfile);
	}
	look_for_builtins(&cmd, env, parse);
	process_cmd(parse, env, cmd);
}

/**
 * @brief This function is called when nb_of_pipes is 0
			It will try the builtins an run them directly
			If it cant it will then call execute solo child
			This function is called by calling_the_execs_shell
 * 
 * @param cmd 
 * @param env 
 * @param parse 
 */
void	execute_solo(char **cmd, char ***env, t_parsing *parse)
{
	int	pid;

	if (parse->infile != -1 || parse->nb_of_pipes > 0)
	{
		if (look_for_exit(cmd))
			mini_exit(cmd, parse, true);
		else if (look_for_export(cmd))
			mini_export(cmd, env, parse, true);
		else if (look_for_unset(cmd))
			mini_unset(cmd, env, parse, true);
		else if (look_for_cd(cmd))
			mini_cd(cmd, env, parse, true);
		else if (look_for_echo(cmd))
			mini_echo(cmd, parse, true);
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
