/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:43:41 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/25 11:43:43 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/**
 * @brief Will first try cmd with absolue path, then within the path
			Will finally clean and exit with 1 or 2 depending 
			if a problem was encountered
 * 
 * @param parse 
 * @param cmd 
 * @param env 
 * @param fds 
 */
static void	process_cmd(t_parsing *parse, char **cmd, char **env, int *fds)
{
	if (parse->b_in == true)
		close(fds[1]);
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
	else if (parse->b_in == true)
	{
		arena_free(&g_ex.arena);
		free_strrarr(g_ex.new_env);
		exit(0);
	}
}

/**
 * @brief Function made to exectute the last child
			It will first look fit the outfile isnt 1
			It will then look for builtins
			If not successfull with builtins
			It will try to run the command locally
			If it cant it will try parse_exec_cmd
			Which will run every possible paths
 * 
 * @param input and ouputfds passed by exec_out 
 * @param parse mostly for the builtins
 * @param cmd to be executed
 * @param env 
 */
static void	exec_out_child(int fds[2], t_parsing *parse,
	char **cmd, char **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup2(fds[0], 0);
	close(fds[0]);
	if (parse->outfile != 1)
	{
		dup2(fds[1], 1);
		if (parse->outfile != -1)
			close(fds[1]);
	}
	look_for_builtins(&cmd, &env, parse);
	process_cmd(parse, cmd, env, fds);
}

/**
 * @brief Execute out function was created to respect the limit of inputs
			I was using only execute at first and had to switch it around

			This function is called by calling_the_execs shell
	//à mettre au début de la fonction entre pid et 
	//le pipe pour voir ce qui est passé à la fonction
	// printf("WITHIN EXECUTE_OUT\n");
	// for(int i = 0;cmd[i];i++)
	// 	printf("CMD[%d] = %s\n", i, cmd[i]);
 * 
 * @param cmd 
 * @param fds 
 * @param env 
 * @param parse 
 */
void	execute_out(char **cmd, int fds[2], char **env, t_parsing *parse)
{
	int	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	g_ex.cmd_rtn = 0;
	if (pid == 0)
		exec_out_child(fds, parse, cmd, env);
	close(fds[0]);
	if (parse->outfile != 1 && parse->outfile != -1)
		close(fds[1]);
	parse->pids[parse->nb_of_pipes] = pid;
}
