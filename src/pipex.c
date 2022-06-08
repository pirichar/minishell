/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:58:15 by pirichar          #+#    #+#             */
/*   Updated: 2022/06/07 16:33:38 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**split_cmd(const char *path, const char *cmd)
{
	char	**rtn;
	char	*cmd_with_path;

	cmd_with_path = ft_strjoin(path, cmd);
	rtn = ft_split(cmd_with_path, ' ');
	free (cmd_with_path);
	return (rtn);
}

/*
	parse and exec CMD taks as input the command
	It also takes as input the environment variable
	First it ill get the path within the env variable and put it in a 2d array
	Then it will add a slash to the cmd so 
	it can look at the end of each line of the 2d array
	It will then loop trough all the element of the path line by line 
	It will look with s_argv1 using access if 
	the command is accessible with any of the proved path
	CASE A:
		If it is iit will split the command to 
		create the final vector wanted by execve
		Run EXECVE and add an exit for safety if anything goes wrong
	BASE B:
		It will display an error message an says that 
		command is not found and free everything	
*/

void	parse_and_exec_cmd(const char *cmd, char **env)
{
	int			i;
	t_exec_ptrs	p;

	p.path = var_to_strarr(env,"PATH=");
	p.cmd_with_slash = ft_strjoin("/", cmd);
	p.cmd_split = ft_split(cmd, ' ');
	i = 0;
	while (p.path[i])
	{
		if (search_path(p.path[i], p.cmd_split[0]) == true)
		{
			p.final_cmd = split_cmd(p.path[i], p.cmd_with_slash);
			execve(p.final_cmd[0], p.final_cmd, env);
			exit(1);
		}
		i++;
	}
	printf("MINISHELL : Command not found\n"); // change this for an error function
	free (p.path);
	free (p.cmd_split);
	free (p.cmd_with_slash);
	exit(1);
}

/*
	Execute take as input the CMD to execute
	It will at first create a pipe for each command
	The second input is the fd for its input
	The third input is a pointer to an array of PIDS 
	(the user passes the right section of the array)
	The last intput is the environement we gather 
	from the main function and that we
	use to call our command

	CASE A:
		If the fd_in is -1 execute will close the fd_in
		It will then close the write part of the pipe
		 without writing anything in it
		Then it will return the empty reading part of the pipe
	CASE B:
		if the fd is other then -1 (is valid) execute will fork

		The child process will then dup the passed fd_in into stdin and close fd_in
		Then the process will dup the writing part of the pipe 
		into the stdin then close the pipe[1]
		Finally its gonna call parse and exec cmd which 
		will result in killing the process if it can run the command
		Otherwise we run exit(1) after to be sure everything is exited correctly

		The main process will just close the fd_in
		It will also close the writing part of the pipe
		Finally it will give to the passed 

*/

int	execute(const char *cmd, int fd_in, int *p, char **env)
{
	int	pipes[2];
	int	pid;

	pipe(pipes);
	if (fd_in != -1)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(fd_in, 0);
			close(fd_in);
			dup2(pipes[1], 1);
			close(pipes[1]);
			parse_and_exec_cmd(cmd, env);
			exit(1);
		}
	}
	close(fd_in);
	close(pipes[1]);
	if (fd_in != -1)
		*p = pid;
	return (pipes[0]);
}

/*
	Execute out function was created to respect the limit of inputs
	I was using only execute at first and had to switch it around
*/
void	execute_out(const char *cmd, int fds[2], int *p, char **env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(fds[0], 0);
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		parse_and_exec_cmd(cmd, env);
	}
	close(fds[0]);
	*p = pid;
}

void	execute_solo(const char *cmd, int fds[2], int *p, char **env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		parse_and_exec_cmd(cmd, env);
	}
	close(fds[0]);
	*p = pid;
}
/* 
	Calling the exec goes through all the commands and run execute on that command
	It will give execute different parameters depending on 
	the command on are working with
	If it is the first command you will pas the infile to execute instead of fd

	argc == 8
	argc - 2 == 6
	process count == 5
	pendant que J (3) est plus petit que 6
	PREMIER PROCESS pid[0]
	j = 2e process = 3 = pids[3 - 2 (1)]
	j = 3e process == 4 = pids[4 -2 (2)]
	j = 4e process == 5 = pids[5 -2 (3)]
	j = 5e process == 6 = I GET OUT OF THE LOOP
	LAST PROCESS = pids[process_count-1 (5) - 1 (4)]
*/

int	calling_the_execs(int argc, char **argv, char **env, t_files *f)
{
	int	fd;
	int	j;

	fd = execute(argv[2], f->infile, &f->pids[0], env);
	j = 3;
	while (j < argc - 2)
	{
		fd = execute(argv[j], fd, &f->pids[j - 2], env);
		j++;
	}
	f->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (f->outfile == -1)
	{
		printf("MINISHELL : could not open output file\n"); //change this for an error function
		return (1);
	}
	execute_out(argv[argc - 2], (int [2]){fd, f->outfile},
		&f->pids[f->process_count - 1], env);
	return (0);
}
