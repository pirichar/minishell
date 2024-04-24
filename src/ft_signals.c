#include "../include/minishell.h"

// This function handles the Ctrl-C (SIGINT) event
// Move to a new line
void	handle_sigint(int sig)
{
	(void)sig;
	char* prompt;

    ex->interrupted = 1;
    write (1, "\n", 1);
	prompt = set_prompt(ex->new_env);
	write(1, prompt, ft_strlen(prompt));
	free(prompt);
}

// This function handles the Ctrl-\ (SIGINT) event
// Move to a new line
void handle_sigquit(int sig)
 {
    (void)sig;
	if (ex->foreground_job_active)
		write(1, "\nQuit signal (SIGQUIT) received by job.\n", 40);
}

void setup_signal_handlers()
{
    struct sigaction sa_int;
	struct sigaction sa_quit;

    // Setup for SIGINT
	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART; // Auto-restart functions if interrupted
	sigaction(SIGINT, &sa_int, NULL);

   // SIGQUIT handler setup
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_handler = handle_sigquit; 
    sa_quit.sa_flags = 0;  // No flags
    sigaction(SIGQUIT, &sa_quit, NULL);
}

void update_sigquit_handling()
 {
    if (ex->foreground_job_active)
	{
        // Set to custom handler when a job is active
        signal(SIGQUIT, handle_sigquit);
    } else {
        // Ignore SIGQUIT when no job is active
        signal(SIGQUIT, SIG_IGN);
    }
}
