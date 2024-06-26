#include "../include/minishell.h"

/**
 * @brief calling the execs shell take in input the cmd passed by the main
			(could only take parse and get the command throught it tho)
			Case A:
				It firstly checks the number of pipes in the line
				If the number is 0
				it will run the command alone with execute_solo
			Case B:
				If the number is greater then 0 it will 
				passe the first command to execute
				Execute will call the 
				Execute will then return the pipe reading end of 
				the pipe (pipe[0]) to the next command
				Then it will move the list forward to the next node
				If there is more then 2 commands it will get into the while 
				it will stay into this while until the last command
				Then the last command is executed with execute out
				every execution process places the pid in the right 
				place within the parse->pids array
			This function is called in main by execute_command_shell
 * 
 * @param cmd 
 * @param new_env 
 * @param parse 
 */
void	calling_the_execs_shell(char **cmd, char ***new_env, t_parsing *parse)
{
	int	fd;
	int	i;

	i = 1;
	if (parse->nb_of_pipes == 0)
		execute_solo(cmd, new_env, parse);
	else
	{
		fd = execute(parse->infile, &parse->pids[0], *(new_env), parse);
		parse->tkns_list = parse->tkns_list->next;
		cmd = parse->tkns_list->vector_cmd;
		while (i < parse->nb_of_pipes)
		{
			fd = execute(fd, &parse->pids[i], *(new_env), parse);
			i++;
			parse->tkns_list = parse->tkns_list->next;
			cmd = parse->tkns_list->vector_cmd;
		}
		execute_out(cmd, (int [2]){fd, parse->outfile}, *(new_env), parse);
	}
}

/**
 * @brief parse and exec CMD taks as input the command the be executed
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
	This function is called by executioin functions such as
	execute_out excute_solo our execute exec_child

// TO-DO verifier le leak ici il faudrait surement passer 
//par adresse le s_line pour le modifier
//les leaks sont sur les cmd[0] avec les strjoin 
//il faudrait que je fasse un strjoin free s2
// maybe change the fprintf for an error function
 * 
 * @param cmd to be executed
 * @param env variables passed 
 */
void	parse_and_exec_cmd_shell(char **cmd, char **env)
{
	int			i;
	t_exec_ptrs	p;

	p.path = path_to_starrr(env, "PATH=");
	if (p.path == NULL)
	{
		fprintf(stderr, "PATH environment variable not set\n");
		return ;
	}
	cmd[0] = ft_strjoin("/", cmd[0]);
	i = 0;
	while (p.path[i])
	{
		if (search_path_exec(p.path[i], cmd[0]) == true)
		{
			cmd[0] = ft_strjoin(p.path[i], cmd[0]);
			execve(cmd[0], cmd, env);
			exit(1);
		}
		i++;
	}
	fprintf(stderr, "%s: command not found\n", cmd[0] + 1);
	free_strrarr(p.path);
	exit(2);
}
