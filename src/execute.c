#include "../include/minishell.h"

/**
 * @brief cette fonction remplace tout ce qui était 
			dans la partie if pid==0 de la fonction execute
			En gros elle prend le fd in;
			s'il n'est pas à 0(donc qui a été changé)
			elle va dup2 le fdin dans le stdin pour la fonction appelée plus tard
			elle ferme ensuite le fdin,
			dup2 le pipe_1 dans stdout afin que la sortie
			de la commande sorte dans le pipe et non dans le stdout
			par la suite on verifie pour une builtin; 
			s'il n,y en a pas on execute la commande
			soit localement soit avec parse_and_exec_cmd_shell 

			
 * 
 * @param fd_in input file descriptor
 * @param pipe_1 the end to be duped to stdout
 * @param parse used to know if parse->b_in is true
 * @param env required for execve
 */
static void	exec_child(int fd_in, int pipe_1, t_parsing *parse, char **env)
{
	if (fd_in != 0)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
	dup2(pipe_1, 1);
	close(pipe_1);
	look_for_builtins(&parse->tkns_list->vector_cmd, &env, parse);
	if (parse->b_in == false
		&& access(parse->tkns_list->vector_cmd[0], X_OK) == 0)
	{
		execve(parse->tkns_list->vector_cmd[0],
			parse->tkns_list->vector_cmd, env);
		exit (1);
	}
	else if (parse->b_in == false)
	{
		parse_and_exec_cmd_shell(parse->tkns_list->vector_cmd, env);
		exit (1);
	}
	exit (0);
}

/*
	OLD DESCRIPTION FOR PIPEX MIGHT HAVE TO BE UPDATED
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

		The child process will then dup the passed
		fd_in into stdin and close fd_in
		Then the process will dup the writing part of the pipe 
		into the stdin then close the pipe[1]
		Finally its gonna call parse and exec cmd which 
		will result in killing the process if it can run the command
		Otherwise we run exit(1) after to be sure everything is exited correctly

		The main process will just close the fd_in
		It will also close the writing part of the pipe
		Finally it will give to the passed 

*/
//à mettre au début de la fonction entre pid et le 
//pipe pour voir ce qui est passé à la fonction
// printf("WITHIN EXECUTE\n");
// for(int i = 0;cmd[i];i++)
// 	printf("CMD[%d] = %s\n",i, cmd[i]);
int	execute(int fd_in, int *p, char **env, t_parsing *parse)
{
	int	pipes[2];
	int	pid;

	pipe(pipes);
	if (fd_in != -1)
	{
		pid = fork();
		if (pid == 0)
			exec_child(fd_in, pipes[1], parse, env);
		*p = pid;
	}
	if (fd_in != 0)
		close(fd_in);
	close(pipes[1]);
	return (pipes[0]);
}
