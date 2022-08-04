#include "../include/minishell.h"

/*
	calling the execs shell take in input the cmd passed by the main
	(could only take parse and get the command throught it tho)
	Case A:
		It firstly checks the number of pipes in the line
		If the number is 0 it will run the command alone with execute_solo
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
		fd = execute(cmd, parse->infile,
				&parse->pids[0], *(new_env), parse);
		parse->tkns_list = parse->tkns_list->next;
		cmd = parse->tkns_list->vector_cmd;
		while (i < parse->nb_of_pipes)
		{
			fd = execute(cmd, fd, &parse->pids[i], *(new_env), parse);
			i++;
			parse->tkns_list = parse->tkns_list->next;
			cmd = parse->tkns_list->vector_cmd;
		}
		execute_out(cmd, (int [2]){fd, parse->outfile}, *(new_env), parse);
	}
}
