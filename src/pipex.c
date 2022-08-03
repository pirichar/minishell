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
void	parse_and_exec_cmd_shell(char **cmd, char **env)
{
	int			i;
	t_exec_ptrs	p;

	p.path = path_to_starrr(env, "PATH=");
	cmd[0] = ft_strjoin("/", cmd[0]);//verifier le leak ici il faudrait surement passer par adresse le s_line pour le modifier
	i = 0;
	while (p.path[i])
	{
		if (search_path_exec(p.path[i], cmd[0]) == true)
		{
			cmd[0] = ft_strjoin(p.path[i], cmd[0]); //leak ici for sur il faudrait que je free le s2
			execve(cmd[0], cmd, env);
			exit(1);
		}
		i++;
	}
	fprintf(stderr,"MINISHELL : Command not found\n"); // change this for an error function
	free_strrarr(p.path);
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

int	execute(char **cmd, int fd_in, int *p, char **env)
{
	int	pipes[2];
	int	pid;
	printf("WITHIN EXECUTE\n");
	for(int i = 0;cmd[i];i++)
		printf("CMD[%d] = %s\n",i, cmd[i]);
	pipe(pipes);
	if (fd_in != -1)
	{
		pid = fork();
		if (pid == 0)
		{
			if (fd_in != 0)
			{
				dup2(fd_in, 0);
				close(fd_in);
			}
			dup2(pipes[1], 1);
			close(pipes[1]);
			if (access (cmd[0], X_OK) == 0)
			{
				printf("LOCAL EXECUTION IN EXECUTE\n");
				execve(cmd[0], cmd, env);
				exit(1);
			}
			else
				parse_and_exec_cmd_shell(cmd, env);
			exit(1);
		}
	}
	if (fd_in != 0)
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
void	execute_out(char **cmd, int fds[2],char **env , t_parsing *parse)
{
	int	pid;

	printf("WITHIN EXECUTE_OUT\n");
	for(int i = 0;cmd[i];i++)
		printf("CMD[%d] = %s\n",i, cmd[i]);
	pid = fork();
	if (pid == 0)
	{
		dup2(fds[0], 0);
		close(fds[0]);
		if (parse->outfile != 1)
		{
			dup2(fds[1], 1);
			close(fds[1]);
		}
		if (access (cmd[0], X_OK) == 0)
		{
				printf("LOCAL EXECUTION IN EXECUTE\n");
				execve(cmd[0], cmd, env);
				exit(1);
		}
		else
			parse_and_exec_cmd_shell(cmd, env);
		exit(1);
	}
	close(fds[0]);
	if (parse->outfile != 1)
		close(fds[1]);
	parse->pids[parse->nb_of_pipes] = pid;
}

void	calling_the_execs_shell(char **cmd, char **new_env, t_parsing *parse)
{
	int	fd;
	int i;

	i = 1;
	if (parse->nb_of_pipes == 0)
		execute_solo(cmd, new_env, parse);
	else
	{
		//maybe I could start looking for builtins into each execute functinons or before it
		//mettre look for builtin ici
		//mettre un if parse->b_in = false ici et passer execute après
		fd = execute(cmd, parse->infile, &parse->pids[0], new_env);
		parse->tkns_list = parse->tkns_list->next;
		cmd = parse->tkns_list->vector_cmd;
		while (i < parse->nb_of_pipes)
		{
			fd = execute(cmd, fd, &parse->pids[i], new_env);
			i++;
			parse->tkns_list = parse->tkns_list->next;
			cmd = parse->tkns_list->vector_cmd;
		}
		execute_out(cmd, (int [2]){fd, parse->outfile}, new_env, parse);
	}
}

void	execute_solo(char **cmd, char **env, t_parsing *parse)
{
	int	pid;
	int	pipes[2];

	printf("WITHIN EXECUTE_SOLO\n");
	pipe(pipes);
	if (parse->infile != -1)
	{
		pid = fork();
		if (pid == 0)
		{
			if (parse->infile != 0)
			{
				dup2(parse->infile, 0);
				close(parse->infile);
			}
			if (parse->outfile != 1)
			{
				dup2(parse->outfile,1);
				close(parse->outfile);
			}
			if (access (cmd[0], X_OK) == 0)
			{
				execve(cmd[0], cmd, env);
				exit(1);
			}
			else
				parse_and_exec_cmd_shell(cmd, env);
		}
	}
	if (parse->infile != -1)
		parse->pids[0] = pid;
}