#include "../include/minishell.h"


t_exec		*ex;

// This function handles the Ctrl-C (SIGINT) event
// Move to a new line
void handle_sigint(int sig)
{
	(void)sig;
    write(STDOUT_FILENO, "\n", 1);
	char* prompt = set_prompt(ex->new_env);
	write(STDOUT_FILENO, prompt, ft_strlen(prompt));
	free(prompt);
}

// This function handles the Ctrl-\ (SIGINT) event
// Move to a new line
void handle_sigquit(int sig)
 {
    (void)sig;
	if (ex->foreground_job_active)
	{
		write(STDOUT_FILENO, "\nQuit signal (SIGQUIT) received by job.\n", 40);
		// Here you might handle the SIGQUIT for the job, e.g., terminate it
	}
}

void setup_signal_handlers() {
    struct sigaction sa_int;

    // Setup for SIGINT
	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART; // Auto-restart functions if interrupted
	sigaction(SIGINT, &sa_int, NULL);

    // Setup for SIGTSTP
	struct sigaction sa_quit;
   // SIGQUIT handler setup
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;  // No flags
    sa_quit.sa_handler = handle_sigquit;  // Set our custom handler

    sigaction(SIGQUIT, &sa_quit, NULL);
}

void update_sigquit_handling()
 {
    if (ex->foreground_job_active) {
        // Set to custom handler when a job is active
        signal(SIGQUIT, handle_sigquit);
    } else {
        // Ignore SIGQUIT when no job is active
        signal(SIGQUIT, SIG_IGN);
    }
}

void configure_terminal() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);  // Get the current terminal attributes
    term.c_lflag &= ~ECHOCTL;        // Clear the ECHOCTL flag to stop echoing Ctrl characters
    tcsetattr(STDIN_FILENO, TCSANOW, &term);  // Apply the modified settings
}

int	nb_of_charstrstr(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	return (i);
}

/*
	So here we have 2 struct one for the execution and one for the parsing
	We malloc ex and give the stats of 0 (I don't understand why yet tho)

*/
int	main(int argc, char **argv, char **env)
{
	t_parsing 	*parse;
	(void)argv;

    configure_terminal(); // Configure terminal settings to suppress ^C

	ex = ft_calloc(1, sizeof(t_exec));
	ex->status = 0;
	ex->foreground_job_active = 0;
	if (argc > 1)
	{
		fprintf(stderr, "Why U put params?!?!\n");
		free(ex);
		return (1);
	}
	print_logo(env);
	ex->new_env = copy_strarr(env);
	setup_signal_handlers(); // Set up signal handling
	while (1)
	{
		ex->prompt = set_prompt(ex->new_env);
		update_sigquit_handling();
		ex->line = readline(ex->prompt);
		free(ex->prompt);
		if (ex->line == NULL)
		{
			free(ex->line);
			free_strrarr(ex->new_env);
			printf("exit\n");
			return (0);
		}
		if (*ex->line)
		{
			add_history(ex->line);
			parse = start_parse(ex->line, ex->status);
			if (parse == NULL)
			{
				free(ex->line);
				continue;
			}
			parse->ex = ex;  //valider si ca ca ne fait pas un leak je pense que oui
			parse->tkns_list = parse->tkns_list->start;
			ex->s_line = parse->tkns_list->vector_cmd;
			if (ex->s_line[0] == NULL)// pas certain de savoir  à quoi ça sert ce if là
			{
				free(ex->line);
				free_strrarr(ex->s_line);
				continue ;
			}
			ex->foreground_job_active = 1; // Job is starting
			update_sigquit_handling();

			calling_the_execs_shell(ex->s_line, &ex->new_env, parse);
			wait_for_pids(parse); 
			ex->foreground_job_active = 0; // Job is complete
			update_sigquit_handling();

			free_strrarr(ex->s_line);
		}
		free(ex->line);
	}
	free_strrarr(ex->path);
	// free(ex->prompt);
	free (ex); // valider comment bien free toute la structure
}

void	print_logo(char **env)
{
	char	*lol[15];
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		lol[0] = "/usr/bin/clear";
		lol[1] = NULL;
		execve(lol[0], lol, env);
	}
	wait(NULL);
	printf(RED"\n __________________________________________________________________\n");
	printf("|    ____                  __             __  ____ ___________     |\n");
	printf("|   / __ \\__  ______  ____/ /__  _____   /  |/  (_) __/ __/ (_)___ |\n");
	printf("|  / / / / / / / __ \\/ __  / _ \\/ ___/  / /|_/ / / /_/ /_/ / / __ \\|\n");
	printf("| / /_/ / /_/ / / / / /_/ /  __/ /     / /  / / / __/ __/ / / / / /|\n");
	printf("|/_____/\\____/_/ /_/\\__,_/\\___/_/   __/_/  /_/_/_/ /_/ /_/_/_/ /_/ |\n");
	printf(BLU"|        / /_  __  __   _________ _/ /_  ________                  |\n");
	printf("|       / __ \\/ / / /  / ___/ __ `/ __ \\/ ___/ _ \\                 |\n");
	printf("|      / /_/ / /_/ /  (__  ) /_/ / /_/ / /  /  __/                 |\n");
	printf("|     /_.___/\\__, /  /____/\\__,_/_.___/_/   \\___/                  |\n");
	printf("|          /____/                                                  |\n");
	printf("|__________________________________________________________________|\n\n\n"RESET);
}