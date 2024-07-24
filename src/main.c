#include "../include/minishell.h"
#include "arena.h"

t_exec		g_ex;

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
	g_ex.prompt = set_prompt(g_ex.new_env);
	if (g_ex.line && g_ex.only_delim == false)
		free(g_ex.line);
	g_ex.line = readline(g_ex.prompt);
	g_ex.only_delim = false;
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
	calling_the_execs_shell(g_ex.s_line, &g_ex.new_env, parse);
	wait_for_pids(parse);
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
 * @return true if line is not NULL 
 * @return false if line is NULL
 */
static bool	process_command(void)
{
	t_parsing	*parse;

	if (*g_ex.line)
	{
		add_history(g_ex.line);
		parse = start_parse(g_ex.line, g_ex.status);
		if (g_ex.fail_heredoc)
		{
			g_ex.fail_heredoc = false;
			return (false);
		}
		if (parse == NULL)
		{
			return (true);
		}
		parse->tkns_list = parse->start;
		g_ex.s_line = parse->tkns_list->vector_cmd;
		if (g_ex.s_line && g_ex.s_line[0] == NULL)
		{
			g_ex.only_delim = true;
			free(g_ex.line);
			if (*g_ex.s_line != NULL)
				free_strrarr(g_ex.s_line);
			return (true);
		}
		execute_command_shell(parse);
	}
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
		return (1);
	while (1)
	{
		prompt_and_read_input();
		if (g_ex.line == NULL)
		{
			write(1, "exit\n", 5);
			free(g_ex.line);
			free_strrarr(g_ex.new_env);
			break ;
		}
		if (process_command())
			continue ;
		arena_clear(&g_ex.arena);
	}
	arena_log_watermark(&g_ex.arena);
	arena_free(&g_ex.arena);
}
