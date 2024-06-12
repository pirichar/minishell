#include "../include/minishell.h"

/**
 * @brief First function called in our while(1)
			It sets the prompt
NOTE:We update_sigquit_handling
	So that ctrl \ does not send us to 
	the start of the line when we start dundershell
	its the only occurence where it would happend
	but we chose to let it this way
			Read the line with the promp
			Free the prompt
			For now only called locally but its 
			probably to be called by sigint
 */
void	prompt_and_read_input(void)
{
	ex->prompt = set_prompt(ex->new_env);
	update_sigquit_handling();
	ex->line = readline(ex->prompt);
	free(ex->prompt);
}

/**
 * @brief Pretty much the last function
 			called at the end of process of a command
			will indicate that a job is starting 
			by setting foregroundjobactive to 1
			will then update the sigquit signal handler
			will then execute the command
			by using calling_the_execs_shell
			Finally it will wait for pids
			Update the foreground active
			Update the sigquit handler
			Free the splitted line
 * 
 * @param parse to give to wait to pids
				only using parse->nb_of_pipes
 */
static void	execute_command_shell(t_parsing *parse)
{
	ex->foreground_job_active = 1;
	update_sigquit_handling();
	calling_the_execs_shell(ex->s_line, &ex->new_env, parse);
	wait_for_pids(parse);
	ex->foreground_job_active = 0;
	update_sigquit_handling();
	free_strrarr(ex->s_line);
}

/**
 * @brief Last function called by main in the while(1)
			Create a parsing struct
			Then if line and not interrupted
			We will add the line to history, initiate our  parsing
			If parse == NULL we free the line and return true
			to skip the remaining process in the main loop

			Then if line[0] is NULL (when ?)
			we free the line 
			we free s_line
			we printf(ëxit with ctrl-dwight)
			and return true
			to skip the remaining process in the main loop

			Finally we execute command shell with parse struct
			at the end of the process we free the line and return false 
			To continue the main loop normally

// TO-DO Clarify the parsing stuff with Alexandrine cuz jpa sure
// TO-DO Calrify what situation could end
	 up givinng s_line[0] == NULL ? For now I cant recreate it
// TO-DO Calrify if we correctly free all the parse at the end
 *
 * @return true if line is not NULL and ex->interrupted is false 
 * @return false if line is NULL or ex->interrupted is true 
 */
static bool	process_command(void)
{
	t_parsing	*parse;

	if (*ex->line)
	{
		add_history(ex->line);
		parse = start_parse(ex->line, ex->status);
		if (parse == NULL)
		{
			free(ex->line);
			return (true);
		}
		parse->ex = ex;
		parse->tkns_list = parse->tkns_list->start;
		ex->s_line = parse->tkns_list->vector_cmd;
		if (ex->s_line[0] == NULL)
		{
			free(ex->line);
			free_strrarr(ex->s_line);
			printf("exit with CTRL-Dwight\n");
			return (true);
		}
		execute_command_shell(parse);
	}
	free(ex->line);
	return (false);
}

/**
 * @brief Will setup by calling setupminishell
			If it returns 1 it means we have an error
			we will prompt an error message to the client
			free ex and return 1;

			Then we start the main loop
			we prompt adn read the input of the client

			Then if line == NULL (when ctrl D is pressed)
			we free line
			write exit
			free the new env
			return (0)

			Finally we process then command and continue to the next one

// TO-DO valider comment bien free toute la structure, valider
valider aussi que l'on oublie de rien free jamais
genre quand line == NULL
 * 
 * @param argc 
 * @param argv 
 * @param env 
 * @return int 
 */
int	main(int argc, char **argv, char **env)
{
	(void)argv;
	if (setup_minishell(argc, env) == 1)
	{
		fprintf(stderr, "Why U put params?!?!\n");
		free(ex);
		return (1);
	}
	while (1)
	{
		prompt_and_read_input();
		if (ex->line == NULL)
		{
			free(ex->line);
			write(1, "exit\n", 5);
			free_strrarr(ex->new_env);
			exit (0);
		}
		if (process_command())
			continue ;
	}
	free_strrarr(ex->path);
	free (ex);
}
